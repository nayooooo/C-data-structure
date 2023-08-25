#include "queue_unit_handle.h"

#include <stdarg.h>

#if QUEUE_UNIT_USE_8BIT

queue_err_t _qu_malloc_8bit(void** queue_buff, queue_size_t size)
{
	*queue_buff = obj_malloc(size * sizeof(queue_uint8_t));

	return QUEUE_EOK;
}

queue_err_t _qu_free_8bit(void* block)
{
	if (block == QUEUE_NULL) return -QUEUE_PARAM;
	obj_free(block);

	return QUEUE_EOK;
}

queue_err_t _qu_memcpy_8bit(
	void* dst_base, void* src_base,
	queue_size_t dst_offset, queue_size_t src_offset,
	queue_size_t size
)
{
	void* dst_addr;
	void* src_addr;
	queue_size_t true_size;

	dst_addr = &(((queue_uint8_t*)dst_base)[dst_offset]);
	src_addr = &(((queue_uint8_t*)src_base)[src_offset]);
	true_size = size * sizeof(queue_uint8_t);
	obj_memcpy(dst_addr, src_addr, true_size);

	return QUEUE_EOK;
}

#endif

#if QUEUE_UNIT_USE_32BIT

queue_err_t _qu_malloc_32bit(void** queue_buff, queue_size_t size)
{
	*queue_buff = obj_malloc(size * sizeof(queue_uint32_t));

	return QUEUE_EOK;
}

queue_err_t _qu_free_32bit(void* block)
{
	if (block == QUEUE_NULL) return -QUEUE_PARAM;
	obj_free(block);

	return QUEUE_EOK;
}

queue_err_t _qu_memcpy_32bit(
	void* dst_base, void* src_base,
	queue_size_t dst_offset, queue_size_t src_offset,
	queue_size_t size
)
{
	void* dst_addr;
	void* src_addr;
	queue_size_t true_size;

	dst_addr = &(((queue_uint32_t*)dst_base)[dst_offset]);
	src_addr = &(((queue_uint32_t*)src_base)[src_offset]);
	true_size = size * sizeof(queue_uint32_t);
	obj_memcpy(dst_addr, src_addr, true_size);

	return QUEUE_EOK;
}

#endif

static const struct queue_unit_handle _queue_unit_handles[] = {
#if QUEUE_UNIT_USE_8BIT
	{ QUEUE_UNIT_TYPE_8BIT, _qu_malloc_8bit, _qu_free_8bit, _qu_memcpy_8bit },
#endif
#if QUEUE_UNIT_USE_32BIT
	{ QUEUE_UNIT_TYPE_32BIT, _qu_malloc_32bit, _qu_free_32bit, _qu_memcpy_32bit },
#endif
	{ QUEUE_NULL, QUEUE_NULL, QUEUE_NULL, QUEUE_NULL },
};

queue_err_t queue_unit_handler(const char* type, queue_base_t handle, ...)
{
	queue_unit_handle_t quh = _queue_unit_handles;

	while (quh->type != QUEUE_NULL) {
		int ret = obj_memcmp(type, quh->type, obj_strlen(quh->type));
		if (ret == 0) {
			va_list ap;
			va_start(ap, handle);
			if (handle == QUEUE_UNIT_HANDLE_MALLOC) {
				void** queue_buff = va_arg(ap, int);
				queue_size_t size = va_arg(ap, queue_size_t);
				if (queue_buff == QUEUE_NULL) return -QUEUE_PARAM;
				if (size <= 0) return -QUEUE_PARAM;
				quh->qu_malloc(queue_buff, size);
			}
			else if (handle == QUEUE_UNIT_HANDLE_FREE) {
				void* block = va_arg(ap, int);
				if (block == QUEUE_NULL) return -QUEUE_PARAM;
				quh->qu_free(block);
			}
			else if (handle == QUEUE_UNIT_HANDLE_MEMCPY) {
				void* dst_base = va_arg(ap, int);
				void* src_base = va_arg(ap, int);
				queue_size_t dst_offset = va_arg(ap, queue_size_t);
				queue_size_t src_offset = va_arg(ap, queue_size_t);
				queue_size_t size = va_arg(ap, queue_size_t);
				if (dst_base == QUEUE_NULL) return -QUEUE_PARAM;
				if (src_base == QUEUE_NULL) return -QUEUE_PARAM;
				if (dst_offset < 0) return -QUEUE_PARAM;
				if (src_offset < 0) return -QUEUE_PARAM;
				if (size <= 0) return -QUEUE_PARAM;
				quh->qu_memcpy(dst_base, src_base, dst_offset, src_offset, size);
			}
			else return -QUEUE_PARAM;
			va_end(ap);
			return QUEUE_EOK;
		}
		quh++;
	}

	return -QUEUE_ERROR;
}
