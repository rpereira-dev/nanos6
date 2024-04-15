/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2017 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_TASK_ID_HPP
#define INSTRUMENT_OMPT_TASK_ID_HPP

#include "ompt.h"

namespace Instrument {
	struct task_id_t {
        ompt_data_t data;
	};
}

#endif // INSTRUMENT_OMPT_TASK_ID_HPP
