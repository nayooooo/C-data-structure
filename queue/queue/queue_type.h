#ifndef __QUEUE_TYPE_H__
#define __QUEUE_TYPE_H__

#include "object.h"

/*========================================================
	configuration micro
========================================================*/
#define QUEUE_NULL				OBJ_NULL

#define QUEUE_EOK				OBJ_EOK
#define QUEUE_ERROR				OBJ_ERROR
#define QUEUE_PARAM				OBJ_PARAM

#define QUEUE_NORMAL			(0)
#define QUEUE_FULL				(1)
#define QUEUE_EMPTY				(2)

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

/*========================================================
	base object
========================================================*/
struct queue {
	struct object parent;

	void *queue;
	queue_size_t queue_size;
	queue_base_t front;
	queue_base_t rear;

	queue_err_t		(*build)				(struct queue* q, queue_size_t size);
	queue_err_t		(*destroy)				(struct queue* q);
	queue_err_t		(*state)				(struct queue* q);
	queue_err_t		(*clear)				(struct queue* q);
	queue_err_t		(*length)				(struct queue* q);
	queue_err_t		(*enter)				(struct queue* q, void* src, queue_size_t size);
	queue_err_t		(*out)					(struct queue* q, void* dst, queue_size_t size);
	queue_err_t		(*read)					(struct queue* q, void* dst);
	queue_err_t		(*traverse)				(struct queue* q, void(*visit)(void));
};
typedef struct queue* queue_t;

#endif // !__QUEUE_TYPE_H__