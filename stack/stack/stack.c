#include "stack.h"

#include <stdlib.h>
#include <string.h>

#if stack_size_t != size_t
#error "stack_size_t is not equal to size_t"
#endif

void* stack_malloc(stack_size_t size)
{
	return malloc(size);
}

void stack_free(void* block)
{
	if (block == STACK_NULL) return;
	free(block);
}

void* stack_memcpy(void *dst, void *src, stack_size_t size)
{
	return memcpy(dst, src, size);
}

stack_err_t _stack_build(struct stack* s, stack_size_t size)
{
	if (s == STACK_NULL) return -STACK_PARAM;

	if (size == 0) return -STACK_PARAM;
	if (s->stack != STACK_NULL) {
		stack_err_t err;
		err = s->destroy(s);
		if (err != STACK_EOK) {
			return err;
		}
	}

	s->stack = stack_malloc(size);
	s->stack_size = size;

	return STACK_EOK;
}

stack_err_t _stack_destroy(struct stack* s)
{
	if (s == STACK_NULL) return -STACK_PARAM;
	if (s->stack == STACK_NULL) return -STACK_PARAM;

	stack_free(s->stack);
	s->stack = STACK_NULL;
	s->stack_size = 0;

	return STACK_EOK;
}

stack_err_t _stack_state(struct stack* s)
{
	if (s == STACK_NULL) return -STACK_PARAM;

	if (s->top == s->stack_size) return STACK_FULL;
	else if (s->top == 0) return STACK_EMPTY;
	else return STACK_NORMAL;
}

stack_err_t _stack_push(struct stack* s, void* src, stack_size_t size)
{
	if (s == STACK_NULL) return -STACK_PARAM;
	if (src == STACK_NULL) return -STACK_PARAM;

	stack_err_t err;

	if (s->state == STACK_NULL) return -STACK_ERROR;
	err = s->state(s);
	if ((err != STACK_EMPTY) && (err != STACK_NORMAL)) return -STACK_ERROR;
	if (s->top + size > s->stack_size) return -STACK_PARAM;

	stack_memcpy(&(((stack_uint8_t*)(s->stack))[s->top]), src, size);
	s->top += size;

	return STACK_EOK;
}

stack_err_t _stack_pop(struct stack* s, void* dst, stack_size_t size)
{
	if (s == STACK_NULL) return -STACK_PARAM;
	if (dst == STACK_NULL) return -STACK_PARAM;

	stack_err_t err;

	if (s->state == STACK_NULL) return -STACK_ERROR;
	err = s->state(s);
	if ((err != STACK_FULL) && (err != STACK_NORMAL)) return -STACK_ERROR;
	if (s->top < size) return -STACK_PARAM;

	stack_memcpy(dst, &(((stack_uint8_t*)(s->stack))[s->top - size]), size);
	for (stack_size_t i = 0; i < size; i++) {
		stack_memcpy(&(((stack_uint8_t*)dst)[i]), &(((stack_uint8_t*)(s->stack))[s->top - i - 1]), size);
	}
	s->top -= size;

	return STACK_EOK;
}

stack_err_t _stack_read(struct stack* s, void* dst)
{
	if (s == STACK_NULL) return -STACK_PARAM;
	if (dst == STACK_NULL) return -STACK_PARAM;

	stack_err_t err;

	if (s->state == STACK_NULL) return -STACK_ERROR;
	err = s->state(s);
	if ((err != STACK_FULL) && (err != STACK_NORMAL)) return -STACK_ERROR;

	stack_memcpy(dst, &(((stack_uint8_t*)(s->stack))[s->top - 1]), 1);

	return STACK_EOK;
}

stack_err_t stack_init(struct stack* s, const char *name)
{
	if (s == STACK_NULL) {
		return -STACK_PARAM;
	}

	stack_memcpy(s->parent.name, name, STACK_OBJECT_NAME_LEN);
	s->parent.flag = 0;

	s->stack = STACK_NULL;
	s->stack_size = 0;
	s->top = 0;
	s->bottom = 0;

	s->build = _stack_build;
	s->destroy = _stack_destroy;
	s->state = _stack_state;
	s->push = _stack_push;
	s->pop = _stack_pop;
	s->read = _stack_read;

	return STACK_EOK;
}
