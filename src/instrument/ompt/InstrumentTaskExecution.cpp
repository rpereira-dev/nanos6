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

#include <cassert>

void Instrument::startTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context)
{
    Instrument::ThreadLocalData & tld = Instrument::getThreadLocalData();

    ompt_data_t * prior_task_data = &(tld.current_task);
    ompt_task_status_t prior_task_status = ompt_task_switch;
    ompt_data_t * next_task_data = &(taskId.data);

    if (prior_task_data->value == tld.implicit_task_data.value && next_task_data->value == 0)
        return ;

    NANOS6_OMPT_CALLBACK(ompt_callback_task_schedule, prior_task_data, prior_task_status, next_task_data);

    tld.prev_task = *prior_task_data;
    tld.current_task = *next_task_data;
}

void Instrument::endTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context)
{
    Instrument::ThreadLocalData & tld = Instrument::getThreadLocalData();

    assert(taskId.data.value == tld.current_task.value);

    ompt_data_t * prior_task_data = &(tld.current_task);
    ompt_task_status_t prior_task_status = ompt_task_complete;
    ompt_data_t * next_task_data = &(tld.prev_task);

    if (next_task_data->value == 0 && prior_task_data->value == tld.implicit_task_data.value)
        return ;

    NANOS6_OMPT_CALLBACK(ompt_callback_task_schedule, prior_task_data, prior_task_status, next_task_data);

    ompt_data_t cpy = tld.prev_task;
    tld.prev_task = *prior_task_data;
    tld.current_task = cpy;
}

void Instrument::destroyTask(__attribute__((unused)) task_id_t taskId, __attribute__((unused)) InstrumentationContext const &context)
{
}
