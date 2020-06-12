/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2020 Barcelona Supercomputing Center (BSC)
*/

#ifndef MEMORY_ALLOCATOR_HPP
#define MEMORY_ALLOCATOR_HPP

#include <jemalloc/jemalloc.h>

#include <cstdint>

#include "lowlevel/FatalErrorHandler.hpp"

class MemoryAllocator {
private:
	static const int MALLOCX_NONE = ((int) 0);

public:
	static void initialize()
	{
	}

	static void shutdown()
	{
	}

	static constexpr bool hasUsageStatistics()
	{
		return true;
	}

	static inline size_t getMemoryUsage()
	{
		size_t allocated, size, epsize;
		size = sizeof(allocated);
		uint64_t epoch = 1;
		epsize = sizeof(epoch);

		// Expensive: force a flush of the tcache and an epoch change to refresh the statistics.
		nanos6_je_mallctl("thread.tcache.flush", nullptr, nullptr, nullptr, 0);
		nanos6_je_mallctl("epoch", &epoch, &epsize, &epoch, epsize);

		nanos6_je_mallctl("stats.active", &allocated, &size, nullptr, 0);

		return allocated;
	}

	static inline void *alloc(size_t size)
	{
		assert(size > 0);
		void *ptr = nanos6_je_mallocx(size, MALLOCX_NONE);
		FatalErrorHandler::failIf(ptr == nullptr, " when trying to allocate memory");
		return ptr;
	}

	static inline void free(void *chunk, size_t size)
	{
		assert(size > 0);
		// Failing this assert means the size passed to free does not correspond to the allocated size
		assert(nanos6_je_sallocx(chunk, MALLOCX_NONE) == nanos6_je_nallocx(size, MALLOCX_NONE));
		nanos6_je_sdallocx(chunk, size, MALLOCX_NONE);
	}

	// Simplifications for using "new" and "delete" with the allocator
	template <typename T, typename... Args>
	static T *newObject(Args &&... args)
	{
		void *ptr = MemoryAllocator::alloc(sizeof(T));
		new (ptr) T(std::forward<Args>(args)...);
		return (T*)ptr;
	}

	template <typename T>
	static void deleteObject(T *ptr)
	{
		ptr->~T();
		MemoryAllocator::free(ptr, sizeof(T));
	}
};

#endif // MEMORY_ALLOCATOR_HPP
