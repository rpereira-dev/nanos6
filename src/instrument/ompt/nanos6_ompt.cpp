# include <stdlib.h>
# include <string.h>

# include "nanos6_ompt.h"

# include "instrument/support/InstrumentThreadLocalDataSupport.hpp"

// GENERAL MANAGEMENT
ompt_callback_t callbacks[ompt_max_callback] = { 0 };
ompt_data_t nanos6_tool_data = { 0 };

typedef struct  ompt_func_t
{
    const char * name;
    void (*f)();
}               ompt_func_t;

static ompt_data_t *
nanos6_ompt_get_thread_data(void)
{
    Instrument::ThreadLocalData & tld = Instrument::getThreadLocalData();
    return &(tld.data);
}

static ompt_set_result_t
nanos6_ompt_set_callback(ompt_callbacks_t event, ompt_callback_t callback)
{
    if (event < 0 || event >= ompt_max_callback)
        return ompt_set_error;

    callbacks[event] = callback;

    static ompt_set_result_t results[ompt_max_callback] = { ompt_set_never };
    results[ompt_callback_thread_begin] = ompt_set_always;
    results[ompt_callback_thread_end] = ompt_set_always;
    results[ompt_callback_task_create] = ompt_set_always;
    results[ompt_callback_task_schedule] = ompt_set_always;
    // [...] TODO
    return results[event];
}

static ompt_func_t ompt_funcs[] = {
    {"ompt_set_callback", (ompt_interface_fn_t) nanos6_ompt_set_callback},
    {"ompt_get_thread_data", (ompt_interface_fn_t) nanos6_ompt_get_thread_data},
};

ompt_interface_fn_t
nanos6_ompt_lookup(const char * interface_function_name)
{
    for (unsigned int i = 0 ; i < sizeof(ompt_funcs) / sizeof(ompt_func_t) ; ++i)
        if (strcmp(ompt_funcs[i].name, interface_function_name) == 0)
            return (ompt_interface_fn_t) ompt_funcs[i].f;
    return NULL;
}
