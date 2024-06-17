/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2020-2023 Barcelona Supercomputing Center (BSC)
*/

#include <atomic>
#include <dlfcn.h>
#include <string.h>

#include "instrument/api/InstrumentWorkerThread.hpp"
#include "instrument/support/InstrumentThreadLocalDataSupport.hpp"
#include "instrument/ompt/InstrumentWorkerThread.hpp"

#include "nanos6_ompt.h"
#include "ompt.h"

static volatile std::atomic<int> initializing(0);
static volatile int initialized(0);

void Instrument::workerThreadSpins() {}
void Instrument::workerThreadObtainedTask() {}
void Instrument::workerProgressing() {}
void Instrument::workerResting() {}
void Instrument::workerAbsorbing() {}
void Instrument::workerThreadBusyWaits() {}

void Instrument::workerThreadBegin() {

    int zero = 0;
    int one = 1;
    if (!atomic_compare_exchange_strong(&initializing, &zero, one))
        while (!initialized);

    if (!initialized)
    {
        // initialize the tool
        const char * tool = getenv("OMP_TOOL_LIBRARIES");
        if (tool == NULL)
            return ;

        void * hdl = dlopen(tool, RTLD_LAZY);
        if (hdl == NULL)
            return ;

        ompt_start_tool_t start = (ompt_start_tool_t) dlsym( hdl, "ompt_start_tool");
        if (start == NULL)
        {
            dlclose(hdl);
            return ;
        }

        unsigned int omp_version = 0;
        const char * runtime_version = "Nanos6";
        ompt_start_tool_result_t * r = start(omp_version, runtime_version);
        if (r == NULL)
        {
            dlclose(hdl);
            return ;
        }

        r->initialize(nanos6_ompt_lookup, 0, &nanos6_tool_data);
        initialized = 1;
    }

    Instrument::ThreadLocalData & tld = Instrument::getThreadLocalData();

    // thread begin
    NANOS6_OMPT_CALLBACK(ompt_callback_thread_begin, ompt_thread_worker, &(tld.data));

    // implicit task
    ompt_scope_endpoint_t endpoint = ompt_scope_begin;
    ompt_data_t * parallel_data = NULL;
    ompt_data_t * task_data = &(tld.implicit_task_data);
    unsigned int actual_parallelism = 0;
    unsigned int index = 0;
    int flags = 0;
    NANOS6_OMPT_CALLBACK(ompt_callback_implicit_task, endpoint, parallel_data, task_data, actual_parallelism, index, flags);

    memset(&tld.prev_task, 0, sizeof(ompt_data_t));
    tld.current_task = *task_data;
}

void Instrument::workerThreadEnd() {
    Instrument::ThreadLocalData & tld = Instrument::getThreadLocalData();

    // implicit task
    ompt_scope_endpoint_t endpoint = ompt_scope_end;
    ompt_data_t * parallel_data = NULL;
    ompt_data_t * task_data = &(tld.implicit_task_data);
    unsigned int actual_parallelism = 0;
    unsigned int index = 0;
    int flags = 0;
    NANOS6_OMPT_CALLBACK(ompt_callback_implicit_task, endpoint, parallel_data, task_data, actual_parallelism, index, flags);

    tld.prev_task = *task_data;
    memset(&tld.current_task, 0, sizeof(ompt_data_t));

    // thread end
    NANOS6_OMPT_CALLBACK(ompt_callback_thread_end, &(tld.data));

}

void Instrument::enterHandleTask() {}
void Instrument::exitHandleTask() {}
void Instrument::enterSwitchTo() {}
void Instrument::exitSwitchTo() {}
void Instrument::enterSuspend() {}
void Instrument::exitSuspend() {}
void Instrument::enterResume() {}
void Instrument::exitResume() {}
void Instrument::enterSpongeMode() {}
void Instrument::exitSpongeMode() {}
