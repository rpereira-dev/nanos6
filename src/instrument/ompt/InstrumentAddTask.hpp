/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2022 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_ADD_TASK_HPP
#define INSTRUMENT_OMPT_ADD_TASK_HPP


#include "instrument/api/InstrumentAddTask.hpp"


namespace Instrument {
	task_id_t enterCreateTask(
		__attribute__((unused)) nanos6_task_info_t *taskInfo,
		__attribute__((unused)) nanos6_task_invocation_info_t *taskInvokationInfo,
		__attribute__((unused)) size_t flags,
		__attribute__((unused)) bool taskRuntimeTransition,
		__attribute__((unused)) InstrumentationContext const &context
	);

	void exitCreateTask(
		__attribute__((unused)) bool taskRuntimeTransition
	);

	void createdArgsBlock(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) void *argsBlockPointer,
		__attribute__((unused)) size_t originalArgsBlockSize,
		__attribute__((unused)) size_t argsBlockSize,
		__attribute__((unused)) InstrumentationContext const &context
    );

	void createdTask(
		__attribute__((unused)) void *task,
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) InstrumentationContext const &context
	);

	void enterSubmitTask(
		__attribute__((unused)) bool taskRuntimeTransition
	);

	void exitSubmitTask(
		__attribute__((unused)) task_id_t taskId,
		__attribute__((unused)) bool taskRuntimeTransition,
		__attribute__((unused)) InstrumentationContext const &context
	);

	void registeredNewSpawnedTaskType(
		__attribute__((unused)) nanos6_task_info_t *taskInfo
	);

	void enterSpawnFunction(
		__attribute__((unused)) bool taskRuntimeTransition
	);

	void exitSpawnFunction(
		__attribute__((unused)) bool taskRuntimeTransition
	);
}


#endif // INSTRUMENT_OMPT_ADD_TASK_HPP
