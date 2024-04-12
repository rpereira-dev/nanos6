# include <stdlib.h>
# include <string.h>

# include "nanos6_ompt.h"

ompt_data_t nanos6_tool_data = {0};

typedef struct  ompt_func_t
{
    const char * name;
    void (*f)();
}               ompt_func_t;

static ompt_set_result_t
nanos6_ompt_set_callback(ompt_callbacks_t event, ompt_callback_t callback)
{
    (void) event;
    (void) callback;
    return ompt_set_never;
}

static ompt_func_t ompt_funcs[] = {
    {"ompt_set_callback", (ompt_interface_fn_t) nanos6_ompt_set_callback},
    {"ompt_get_thread_data", NULL},
};

ompt_interface_fn_t
nanos6_ompt_lookup(const char * interface_function_name)
{
    for (unsigned int i = 0 ; i < sizeof(ompt_funcs) / sizeof(ompt_func_t) ; ++i)
        if (strcmp(ompt_funcs[i].name, interface_function_name) == 0)
            return (ompt_interface_fn_t) ompt_funcs[i].f;
    return NULL;
}
