/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2022 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_LEADER_THREAD_HPP
#define INSTRUMENT_OMPT_LEADER_THREAD_HPP

#include <dlfcn.h>

#include "instrument/api/InstrumentLeaderThread.hpp"

#include "ompt.h"
#include "nanos6_ompt.h"

namespace Instrument {
	inline void leaderThreadSpin()
	{
	}

	inline void leaderThreadBegin()
	{
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
	}

	inline void leaderThreadEnd()
	{
	}

}


#endif // INSTRUMENT_OMPT_LEADER_THREAD_HPP
