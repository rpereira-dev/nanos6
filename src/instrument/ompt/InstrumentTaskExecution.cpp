/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2022 Barcelona Supercomputing Center (BSC)
*/

#include <InstrumentInstrumentationContext.hpp>

#include "instrument/api/InstrumentTaskExecution.hpp"
#include "instrument/ompt/InstrumentTaskId.hpp"
#include "instrument/support/InstrumentThreadLocalDataSupport.hpp"

#include "nanos6_ompt.h"
#include "ompt.h"

void Instrument::startTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context)
{
    // TODO
    ompt_data_t * prior_task_data = NULL;
    ompt_task_status_t prior_task_status = ompt_task_switch;
    ompt_data_t * next_task_data = NULL;

    NANOS6_OMPT_CALLBACK(ompt_callback_task_schedule, prior_task_data, prior_task_status, next_task_data);
}

void Instrument::endTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context)
{
    // TODO
    ompt_data_t * prior_task_data = NULL;
    ompt_task_status_t prior_task_status = ompt_task_switch;
    ompt_data_t * next_task_data = NULL;

    NANOS6_OMPT_CALLBACK(ompt_callback_task_schedule, prior_task_data, prior_task_status, next_task_data);
}

void Instrument::destroyTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context)
{
}
