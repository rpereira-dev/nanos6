#ifndef __NANOS6_OMPT_H__
# define __NANOS6_OMPT_H__

# include "ompt.h"

ompt_interface_fn_t nanos6_ompt_lookup(const char * interface_function_name);

extern ompt_data_t nanos6_tool_data;

#endif /* __NANOS6_OMPT_H__ */
