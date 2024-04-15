#ifndef __NANOS6_OMPT_H__
# define __NANOS6_OMPT_H__

# include "ompt.h"

// MANAGEMENT
extern ompt_data_t nanos6_tool_data;
extern ompt_callback_t callbacks[ompt_max_callback];

ompt_interface_fn_t nanos6_ompt_lookup(const char * interface_function_name);

// CALLBACKS
# define NANOS6_OMPT_CALLBACK(EVENT, ...)                   \
    do {                                                    \
        if (callbacks[EVENT])                               \
            ((EVENT ## _t) callbacks[EVENT])(__VA_ARGS__);  \
    } while (0)

#endif /* __NANOS6_OMPT_H__ */
