#ifndef __QUEUE_TYPE_H__
#define __QUEUE_TYPE_H__

#include "../object.h"

#include "queue_conf.h"

/*========================================================
	configuration micro
========================================================*/
#define QUEUE_NULL				OBJ_NULL

#define QUEUE_EOK				OBJ_EOK
#define QUEUE_ERROR				OBJ_ERROR
#define QUEUE_PARAM				OBJ_PARAM

#define QUEUE_NONE				(0)
#define QUEUE_NORMAL			(1)
#define QUEUE_FULL				(2)
#define QUEUE_EMPTY				(3)

#define QUEUE_UNIT_TYPE_LEN				(8)
#define QUEUE_UNIT_TYPE_NULL			""
#define QUEUE_UNIT_TYPE_8BIT			"char"
#define QUEUE_UNIT_TYPE_16BIT			"short"
#define QUEUE_UNIT_TYPE_32BIT			"int"

/*========================================================
	base typedef
========================================================*/
typedef obj_base_t			queue_base_t;
typedef queue_base_t		queue_flag_t;
typedef queue_base_t		queue_size_t;
typedef queue_flag_t		queue_err_t;

typedef obj_int8_t			queue_int8_t;
typedef obj_int16_t			queue_int16_t;
typedef obj_int32_t			queue_int32_t;
typedef obj_int64_t			queue_int64_t;
typedef obj_uint8_t			queue_uint8_t;
typedef obj_uint16_t		queue_uint16_t;
typedef obj_uint32_t		queue_uint32_t;
typedef obj_uint64_t		queue_uint64_t;

typedef obj_sflag_t			queue_sflag_t;

/*========================================================
	base object
========================================================*/
struct queue {
	struct object parent;

	void* queue;
	char type[QUEUE_UNIT_TYPE_LEN];
	queue_size_t queue_size;
	queue_base_t front;
	queue_base_t rear;

	queue_sflag_t buff_state;

	queue_err_t		(*build)				(struct queue* q, const char* type, queue_size_t size);
	queue_err_t		(*destroy)				(struct queue* q);
	queue_err_t		(*state)				(struct queue* q);
	queue_err_t		(*clear)				(struct queue* q);
	queue_err_t		(*length)				(struct queue* q);
	queue_err_t		(*enter)				(struct queue* q, void* src, queue_size_t size);
	queue_err_t		(*out)					(struct queue* q, void* dst, queue_size_t size);
	queue_err_t		(*read)					(struct queue* q, void* dst);
	queue_err_t		(*traverse)				(struct queue* q, void(*visit)(void* data));
};
typedef struct queue* queue_t;

#endif // !__QUEUE_TYPE_H__
