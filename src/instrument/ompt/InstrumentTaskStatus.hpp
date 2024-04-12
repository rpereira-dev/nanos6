/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2022 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_TASK_STATUS_HPP
#define INSTRUMENT_OMPT_TASK_STATUS_HPP


#include "instrument/api/InstrumentTaskStatus.hpp"


namespace Instrument {
	inline void taskIsPending(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) InstrumentationContext const &context
	) {
	}

	inline void taskIsReady(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) InstrumentationContext const &context
	) {
	}

	inline void taskIsExecuting(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) bool wasBlocked,
		__attribute__((unused)) InstrumentationContext const &context
	) {
        // TODO : ompt_callback_task_schedule ?
        // TODO : ompt_callback_implicit_task ?
	}

	inline void taskIsBlocked(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) task_blocking_reason_t reason,
		__attribute__((unused)) InstrumentationContext const &context
	) {
	}

	inline void taskIsZombie(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) InstrumentationContext const &context
	) {
	}

	inline void taskIsBeingDeleted(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) InstrumentationContext const &context
	) {
	}

	inline void taskHasNewPriority(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) long priority,
		__attribute__((unused)) InstrumentationContext const &context
	) {
	}
}


#endif // INSTRUMENT_OMPT_TASK_STATUS_HPP
