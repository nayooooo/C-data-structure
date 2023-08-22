#include "queue.h"

queue_err_t _queue_build(struct queue* q, queue_size_t size)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	if (size == 0) return -QUEUE_PARAM;
	if (q->queue != QUEUE_NULL) {
		queue_err_t err;
		if (q->destroy == QUEUE_NULL) return -QUEUE_PARAM;
		err = q->destroy(q);
		if (err != QUEUE_EOK) {
			return err;
		}
	}

	q->queue = obj_malloc(size);
	q->queue_size = size;

	return QUEUE_EOK;
}

queue_err_t _queue_destroy(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->queue == QUEUE_NULL) return -QUEUE_PARAM;

	obj_free(q->queue);
	q->queue = QUEUE_NULL;
	q->queue_size = 0;

	return QUEUE_EOK;
}

queue_err_t _queue_state(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t _queue_clear(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t _queue_length(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t _queue_enter(struct queue* q, void* src, queue_size_t size)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t _queue_out(struct queue* q, void* dst, queue_size_t size)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t _queue_read(struct queue* q, void* dst)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t _queue_traverse(struct queue* q, void(*visit)(void))
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return QUEUE_EOK;
}

queue_err_t queue_init(struct queue* q, const char* name)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	obj_memcpy(q->parent.name, name, OBJ_NAME_LEN);
	q->parent.flag = 0;

	q->queue = QUEUE_NULL;
	q->front = 0;
	q->rear = 0;

	q->build = _queue_build;
	q->destroy = _queue_destroy;
	q->state = _queue_state;
	q->clear = _queue_clear;
	q->length = _queue_length;
	q->enter = _queue_enter;
	q->out = _queue_out;
	q->read = _queue_read;
	q->traverse = _queue_traverse;

	return QUEUE_EOK;
}
