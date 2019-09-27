/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2015-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "SchedulerInterface.hpp"

class Scheduler {
	static SchedulerInterface *_instance;
	
public:
	static void initialize();
	static void shutdown();
	
	static inline void addReadyTask(Task *task, ComputePlace *computePlace, ReadyTaskHint hint = NO_HINT)
	{
		_instance->addReadyTask(task, computePlace, hint);
	}
	
	static inline Task *getReadyTask(ComputePlace *computePlace, ComputePlace *deviceComputePlace = nullptr)
	{
		return _instance->getReadyTask(computePlace, deviceComputePlace);
	}
	
	//! \brief Get the amount of ready tasks in the queue
	//!
	//! \param[in] computePlace The host compute place
	//! \param[in] deviceComputePlace The target device compute place if it exists
	//!
	//! \returns The current amount of tasks in the ready queue
	static inline size_t getNumReadyTasks(ComputePlace *computePlace, ComputePlace *deviceComputePlace = nullptr)
	{
		return _instance->getNumReadyTasks(computePlace, deviceComputePlace);
	}
	
};

#endif // SCHEDULER_HPP
