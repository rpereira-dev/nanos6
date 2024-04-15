/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2022 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_TASK_EXECUTION_HPP
#define INSTRUMENT_OMPT_TASK_EXECUTION_HPP


#include <InstrumentInstrumentationContext.hpp>

#include "instrument/api/InstrumentTaskExecution.hpp"


namespace Instrument {
	void startTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context);
	void endTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context);
	void destroyTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context);
}


#endif // INSTRUMENT_OMPT_TASK_EXECUTION_HPP
