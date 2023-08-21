#ifndef __STACK_H__
#define __STACK_H__

#include "stack_type.h"

void* stack_memcpy(void* dst, void* src, stack_size_t size);

stack_err_t stack_init(struct stack* s, const char* name);

#endif // !__STACK_H__
