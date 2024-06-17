#ifndef __OMPT_H__
# define __OMPT_H__

# include <stdint.h>

typedef union   ompt_data_t
{
    union {
        uint64_t value;
        struct {
             uint32_t value_lower;
             uint32_t value_upper;
        };
    };

    void * ptr;
}               ompt_data_t;

typedef void (*ompt_interface_fn_t) (void);

typedef ompt_interface_fn_t (*ompt_function_lookup_t) (
    const char * interface_function_name
);

typedef int (*ompt_initialize_t)(
    ompt_function_lookup_t lookup,
    int initial_device_num,
    ompt_data_t * tool_data
);

typedef void (*ompt_finalize_t)(ompt_data_t * tool_data);

typedef struct  ompt_start_tool_result_t
{
    ompt_initialize_t initialize;
    ompt_finalize_t finalize;
    ompt_data_t tool_data;
}               ompt_start_tool_result_t;

typedef ompt_start_tool_result_t * (*ompt_start_tool_t)(unsigned int , const char *);

typedef enum    ompt_callbacks_t
{
    ompt_callback_thread_begin = 1,
    ompt_callback_thread_end = 2,
    ompt_callback_parallel_begin = 3,
    ompt_callback_parallel_end = 4,
    ompt_callback_task_create = 5,
    ompt_callback_task_schedule = 6,
    ompt_callback_implicit_task = 7,
    ompt_callback_target = 8,
    ompt_callback_target_data_op = 9,
    ompt_callback_target_submit = 10,
    ompt_callback_control_tool = 11,
    ompt_callback_device_initialize = 12,
    ompt_callback_device_finalize = 13,
    ompt_callback_device_load = 14,
    ompt_callback_device_unload = 15,
    ompt_callback_sync_region_wait = 16,
    ompt_callback_mutex_released = 17,
    ompt_callback_dependences = 18,
    ompt_callback_task_dependence = 19,
    ompt_callback_work = 20,
    ompt_callback_masked = 21,
    ompt_callback_master /*(deprecated)*/ = ompt_callback_masked,
    ompt_callback_target_map = 22,
    ompt_callback_sync_region = 23,
    ompt_callback_lock_init = 24,
    ompt_callback_lock_destroy = 25,
    ompt_callback_mutex_acquire = 26,
    ompt_callback_mutex_acquired = 27,
    ompt_callback_nest_lock = 28,
    ompt_callback_flush = 29,
    ompt_callback_cancel = 30,
    ompt_callback_reduction = 31,
    ompt_callback_dispatch = 32,
    ompt_callback_target_emi = 33,
    ompt_callback_target_data_op_emi = 34,
    ompt_callback_target_submit_emi = 35,
    ompt_callback_target_map_emi = 36,
    ompt_callback_error = 37,
    ompt_max_callback
}               ompt_callbacks_t;

typedef void (*ompt_callback_t) (void);
typedef void (*ompt_callback_generic_t) ();

typedef enum    ompt_set_result_t {
    ompt_set_error = 0,
    ompt_set_never = 1,
    ompt_set_impossible = 2,
    ompt_set_sometimes = 3,
    ompt_set_sometimes_paired = 4,
    ompt_set_always = 5
}               ompt_set_result_t;

typedef ompt_set_result_t (*ompt_set_callback_t) (
    ompt_callbacks_t event,
    ompt_callback_t callback
);

typedef enum    ompt_thread_t
{
    ompt_thread_initial = 1,
    ompt_thread_worker = 2,
    ompt_thread_other = 3,
    ompt_thread_unknown = 4
}               ompt_thread_t;

typedef void (*ompt_callback_thread_begin_t) (
    ompt_thread_t thread_type,
    ompt_data_t * thread_data
);

typedef void (*ompt_callback_thread_end_t) (
    ompt_data_t * thread_data
);

typedef struct  ompt_frame_t
{
    ompt_data_t exit_frame;
    ompt_data_t enter_frame;
    int exit_frame_flags;
    int enter_frame_flags;
}               ompt_frame_t;

typedef void (*ompt_callback_task_create_t) (
    ompt_data_t * encountering_task_data,
    const ompt_frame_t * encountering_task_frame,
    ompt_data_t * new_task_data,
    int flags,
    int has_dependences,
    const void * codeptr_ra
);

typedef enum    ompt_task_status_t
{
    ompt_task_complete = 1,
    ompt_task_yield = 2,
    ompt_task_cancel = 3,
    ompt_task_detach = 4,
    ompt_task_early_fulfill = 5,
    ompt_task_late_fulfill = 6,
    ompt_task_switch = 7,
    ompt_taskwait_complete = 8
}               ompt_task_status_t;

typedef void (*ompt_callback_task_schedule_t) (
    ompt_data_t * prior_task_data,
    ompt_task_status_t prior_task_status,
    ompt_data_t * next_task_data
);

typedef enum    ompt_dependence_type_t {
    ompt_dependence_type_in = 1,
    ompt_dependence_type_out = 2,
    ompt_dependence_type_inout = 3,
    ompt_dependence_type_mutexinoutset = 4,
    ompt_dependence_type_source = 5,
    ompt_dependence_type_sink = 6,
    ompt_dependence_type_inoutset = 7
}               ompt_dependence_type_t;

typedef struct  ompt_dependence_t
{
    ompt_data_t variable;
    ompt_dependence_type_t dependence_type;
}               ompt_dependence_t;

typedef void (*ompt_callback_dependences_t) (
    ompt_data_t * task_data,
    const ompt_dependence_t * deps,
    int ndeps
);

typedef enum    ompt_scope_endpoint_t
{
    ompt_scope_begin = 1,
    ompt_scope_end = 2,
    ompt_scope_beginend = 3
}               ompt_scope_endpoint_t;

typedef void (*ompt_callback_implicit_task_t) (
    ompt_scope_endpoint_t endpoint,
    ompt_data_t *parallel_data,
    ompt_data_t *task_data,
    unsigned int actual_parallelism,
    unsigned int index,
    int flags
);

#endif /* __OMPT_H__ */
