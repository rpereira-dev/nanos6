/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2017 Barcelona Supercomputing Center (BSC)
*/


#include "instrument/api/InstrumentDependenciesByAccess.hpp"
#include "dependencies/DataAccessType.hpp"

#include "nanos6_ompt.h"
#include "ompt.h"

void Instrument::registerTaskAccess(
	__attribute__((unused)) task_id_t taskId,
	__attribute__((unused)) DataAccessType accessType,
	__attribute__((unused)) bool weak,
	__attribute__((unused)) void *start,
	__attribute__((unused)) size_t length,
	__attribute__((unused)) InstrumentationContext const &context
) {
    ompt_data_t * task_data = &(taskId.data);
    int ndeps = 1;
    ompt_dependence_t deps[1];
    deps[0].variable.ptr = start;
    switch (accessType)
    {
        case (READ_ACCESS_TYPE):
        {
            deps[0].dependence_type = ompt_dependence_type_in;
            break ;
        }

        case (WRITE_ACCESS_TYPE):
        case (READWRITE_ACCESS_TYPE):
        {
            deps[0].dependence_type = ompt_dependence_type_out;
            break ;
        }

        case (CONCURRENT_ACCESS_TYPE):
        {
            deps[0].dependence_type = ompt_dependence_type_inoutset;
            break ;
        }

        // fallback to 'out' as its the most restrictive one
        case (NO_ACCESS_TYPE):
        case (COMMUTATIVE_ACCESS_TYPE):
        case (REDUCTION_ACCESS_TYPE):
        {
            deps[0].dependence_type = ompt_dependence_type_out;
            break ;
        }
    }
    NANOS6_OMPT_CALLBACK(ompt_callback_dependences, task_data, deps, ndeps);
}
