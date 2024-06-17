/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2017 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_THREAD_LOCAL_DATA_HPP
#define INSTRUMENT_OMPT_THREAD_LOCAL_DATA_HPP


#include <InstrumentInstrumentationContext.hpp>
#include "InstrumentTaskId.hpp"
#include "ompt.h"

namespace Instrument {
	struct InstrumentationContext;

	struct ThreadLocalData {
	    InstrumentationContext _context;
        ompt_data_t data;
        ompt_data_t implicit_task_data;
        ompt_data_t prev_task;
        ompt_data_t current_task;


        ThreadLocalData() : _context() {
            this->data.value = 0;
            this->implicit_task_data.value = 0;
            this->prev_task.value = 0;
            this->current_task.value = 0;
        }
	};
}


#endif // INSTRUMENT_OMPT_THREAD_LOCAL_DATA_HPP
