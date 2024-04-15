/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2017 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_THREAD_LOCAL_DATA_HPP
#define INSTRUMENT_OMPT_THREAD_LOCAL_DATA_HPP


#include <InstrumentInstrumentationContext.hpp>

#include "ompt.h"

namespace Instrument {
	struct InstrumentationContext;

	struct ThreadLocalData {
	    InstrumentationContext _context;
        ompt_data_t data;
	};
}


#endif // INSTRUMENT_OMPT_THREAD_LOCAL_DATA_HPP
