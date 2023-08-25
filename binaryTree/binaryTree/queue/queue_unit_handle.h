#ifndef __QUEUE_UNIT_HANDLE_H__
#define __QUEUE_UNIT_HANDLE_H__

#include "queue.h"

#define QUEUE_UNIT_HANDLE_MALLOC		1
#define QUEUE_UNIT_HANDLE_FREE			2
#define QUEUE_UNIT_HANDLE_MEMCPY		3

struct queue_unit_handle {
	const char* type;
	queue_err_t		(*qu_malloc)			(void** queue_buff, queue_size_t size);
	queue_err_t		(*qu_free)				(void* block);
	queue_err_t		(*qu_memcpy)			(void* dst_base, void* src_base,
											 queue_size_t dst_offset, queue_size_t src_offset,
											 queue_size_t size);
};
typedef struct queue_unit_handle* queue_unit_handle_t;

queue_err_t queue_unit_handler(const char* type, queue_base_t handle, ...);

#endif // !__QUEUE_UNIT_HANDLE_H__
