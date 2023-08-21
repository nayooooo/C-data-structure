#ifndef __STACK_TYPE_H__
#define __STACK_TYPE_H__

#include "object.h"

/*========================================================
	configuration micro
========================================================*/
#define STACK_OBJECT_NAME_LEN	(20)

#define STACK_NULL				OBJ_NULL

#define STACK_EOK				OBJ_EOK
#define STACK_ERROR				OBJ_ERROR
#define STACK_PARAM				OBJ_PARAM

#define STACK_NORMAL			(0)
#define STACK_FULL				(1)
#define STACK_EMPTY				(2)

/*========================================================
	base typedef
========================================================*/
typedef obj_base_t			stack_base_t;
typedef stack_base_t		stack_flag_t;
typedef stack_base_t		stack_size_t;
typedef stack_flag_t		stack_err_t;

typedef obj_int8_t			stack_int8_t;
typedef obj_int16_t			stack_int16_t;
typedef obj_int32_t			stack_int32_t;
typedef obj_int64_t			stack_int64_t;
typedef obj_uint8_t			stack_uint8_t;
typedef obj_uint16_t		stack_uint16_t;
typedef obj_uint32_t		stack_uint32_t;
typedef obj_uint64_t		stack_uint64_t;

/*========================================================
	base object
========================================================*/
struct stack {
	struct object parent;

	void *stack;
	stack_size_t stack_size;
	stack_base_t top;
	stack_base_t bottom;

	stack_err_t		(*build)				(struct stack* s, stack_size_t size);
	stack_err_t		(*destroy)				(struct stack* s);
	stack_err_t		(*state)				(struct stack* s);
	stack_err_t		(*push)					(struct stack* s, void* src, stack_size_t size);
	stack_err_t		(*pop)					(struct stack* s, void* dst, stack_size_t size);
	stack_err_t		(*read)					(struct stack* s, void *dst);
};
typedef struct stack* stack_t;

#endif // !__STACK_TYPE_H__
