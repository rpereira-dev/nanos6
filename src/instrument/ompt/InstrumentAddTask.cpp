/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2022 Barcelona Supercomputing Center (BSC)
*/

#include "instrument/api/InstrumentAddTask.hpp"
#include "instrument/ompt/InstrumentAddTask.hpp"
#include "instrument/ompt/InstrumentTaskId.hpp"
#include "instrument/support/InstrumentThreadLocalDataSupport.hpp"

#include "nanos6_ompt.h"
#include "ompt.h"


Instrument::task_id_t Instrument::enterCreateTask(
	__attribute__((unused)) nanos6_task_info_t *taskInfo,
	__attribute__((unused)) nanos6_task_invocation_info_t *taskInvokationInfo,
	__attribute__((unused)) size_t flags,
	__attribute__((unused)) bool taskRuntimeTransition,
	__attribute__((unused)) InstrumentationContext const &context
) {
    Instrument::ThreadLocalData & tld = Instrument::getThreadLocalData();
    ompt_data_t * parent_data = tld.current_task;

    task_id_t task_id;
    ompt_data_t * child_data = &(task_id.data);

    const ompt_frame_t * frame = NULL;
    int ompflags = 0;
    int has_dependences = 1;
    const void * codeptr_ra = NULL;
    NANOS6_OMPT_CALLBACK(ompt_callback_task_create, parent_data, frame, child_data, ompflags, has_dependences, codeptr_ra);

    // TODO : forward this to ompt
    // TaskInfoData *taskInfoData = (TaskInfoData *) taskInfo->task_type_data;
    // taskInfoData->getTaskTypeLabel().c_str()

	return task_id;
}

void Instrument::exitCreateTask(
	__attribute__((unused)) bool taskRuntimeTransition
) {
}

void Instrument::createdArgsBlock(
	__attribute__((unused)) task_id_t taskId,
	__attribute__((unused)) void *argsBlockPointer,
	__attribute__((unused)) size_t originalArgsBlockSize,
	__attribute__((unused)) size_t argsBlockSize,
	__attribute__((unused)) InstrumentationContext const &context)
{
}

void Instrument::createdTask(
	__attribute__((unused)) void *task,
	__attribute__((unused)) task_id_t taskId,
	__attribute__((unused)) InstrumentationContext const &context
) {
}

void Instrument::enterSubmitTask(
	__attribute__((unused)) bool taskRuntimeTransition
) {
}

void Instrument::exitSubmitTask(
	__attribute__((unused)) task_id_t taskId,
	__attribute__((unused)) bool taskRuntimeTransition,
	__attribute__((unused)) InstrumentationContext const &context
) {
}

void Instrument::registeredNewSpawnedTaskType(
	__attribute__((unused)) nanos6_task_info_t *taskInfo
) {
}

void Instrument::enterSpawnFunction(
	__attribute__((unused)) bool taskRuntimeTransition
) {
}

void Instrument::exitSpawnFunction(
	__attribute__((unused)) bool taskRuntimeTransition
) {
}
