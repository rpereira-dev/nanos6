/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2015-2017 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_OMPT_TASK_ID_HPP
#define INSTRUMENT_OMPT_TASK_ID_HPP

#include "ompt.h"

#include <stdio.h>

namespace Instrument {
	struct task_id_t {
        public:
            ompt_data_t data;

            task_id_t() {
                data.value = 0;
            }

            task_id_t(const task_id_t & task_id) : data(task_id.data) {}

            ~task_id_t() {
            }
	};
}

#endif // INSTRUMENT_OMPT_TASK_ID_HPP
