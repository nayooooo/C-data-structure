#include "queue.h"

#include "queue_unit_handle.h"

char* queue_state_code_to_string(queue_sflag_t code)
{
	if (code == QUEUE_NONE) return "QUEUE_NONE";
	else if (code == QUEUE_NORMAL) return "QUEUE_NORMAL";
	else if (code == QUEUE_FULL) return "QUEUE_FULL";
	else if (code == QUEUE_EMPTY) return "QUEUE_EMPTY";
	else return "QUEUE_ERROR_CODE";
}

queue_err_t _queue_build(struct queue* q, queue_size_t size, const char* type)
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
	//q->queue = obj_malloc(size);
	queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MALLOC,
						&q->queue, size);
	q->queue_size = size;
	q->buff_state = QUEUE_EMPTY;

	return QUEUE_EOK;
}

queue_err_t _queue_destroy(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->queue == QUEUE_NULL) return -QUEUE_PARAM;

	//obj_free(q->queue);
	queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_FREE, q->queue);
	q->queue = QUEUE_NULL;
	q->queue_size = 0;
	q->buff_state = QUEUE_NONE;

	return QUEUE_EOK;
}

queue_err_t _queue_state(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return q->buff_state;
}

queue_err_t _queue_clear(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	q->front = 0;
	q->rear = 0;
	q->buff_state = QUEUE_EMPTY;

	return QUEUE_EOK;
}

queue_err_t _queue_length(struct queue* q)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;

	return (q->rear - q->front + q->queue_size) % q->queue_size;
}

queue_err_t _queue_enter(struct queue* q, void* src, queue_size_t size)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;
	if (src == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->queue == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->state(q) == QUEUE_FULL) return -QUEUE_ERROR;
	if ((size == 0) || (size > q->queue_size - q->length(q))) return -QUEUE_PARAM;

	if (q->queue_size - q->rear >= size) {
		//obj_memcpy(&(((queue_uint8_t*)(q->queue))[q->rear]), src, size);
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							q->queue, src, q->rear, 0, size);
	}
	else {
		queue_size_t wrote_num;
		wrote_num = q->queue_size - q->rear;
		//obj_memcpy(&(((queue_uint8_t*)(q->queue))[q->rear]), src, wrote_num);
		//obj_memcpy(q->queue, &(((queue_uint8_t*)src)[wrote_num]), size - wrote_num);
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							q->queue, src, q->rear, 0, wrote_num);
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							q->queue, src, 0, wrote_num, size - wrote_num);
	}

	q->rear = (q->rear + size) % q->queue_size;

	queue_size_t now_length = q->length(q);
	if (now_length == 0) {
		q->buff_state = QUEUE_FULL;
	}
	else {
		q->buff_state = QUEUE_NORMAL;
	}

	return QUEUE_EOK;
}

queue_err_t _queue_out(struct queue* q, void* dst, queue_size_t size)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;
	if (dst == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->queue == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->state(q) == QUEUE_EMPTY) return -QUEUE_ERROR;
	if ((size == 0) || (size > q->length(q))) return -QUEUE_PARAM;

	if (q->queue_size - q->front >= size) {
		//obj_memcpy(dst, &(((queue_uint8_t*)(q->queue))[q->front]), size);
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							dst, q->queue, 0, q->front, size);
	}
	else {
		queue_size_t read_num;
		read_num = q->queue_size - q->front;
		//obj_memcpy(dst, &(((queue_uint8_t*)(q->queue))[q->front]), read_num);
		//obj_memcpy(&(((queue_uint8_t*)dst)[read_num]), q->queue, size - read_num);
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							dst, q->queue, 0, q->front, read_num);
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							dst, q->queue, read_num, 0, size - read_num);
	}

	q->front = (q->front + size) % q->queue_size;

	queue_size_t now_length = q->length(q);
	if (now_length == 0) {
		q->buff_state = QUEUE_EMPTY;
	}
	else {
		q->buff_state = QUEUE_NORMAL;
	}

	return QUEUE_EOK;
}

queue_err_t _queue_read(struct queue* q, void* dst)
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;
	if (dst == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->queue == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->state(q) == QUEUE_EMPTY) return -QUEUE_ERROR;
	if (q->length(q) == 0) return -QUEUE_ERROR;

	obj_memcpy(&(((queue_uint8_t*)(q->queue))[q->front]), dst, 1);
	queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
						q->queue, dst, q->front, 0, 1);

	return QUEUE_EOK;
}

queue_err_t _queue_traverse(struct queue* q, void(*visit)(queue_uint8_t data))
{
	if (q == QUEUE_NULL) return -QUEUE_PARAM;
	if (visit == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->queue == QUEUE_NULL) return -QUEUE_PARAM;
	if (q->state(q) == QUEUE_EMPTY) return -QUEUE_ERROR;

	for (queue_base_t i = 0; i < q->length(q); i++) {
		queue_base_t ind = (q->front + i) % q->queue_size;
		queue_uint8_t data;
		//data = ((queue_uint8_t*)(q->queue))[ind];
		queue_unit_handler(QUEUE_UNIT_TYPE_8BIT, QUEUE_UNIT_HANDLE_MEMCPY,
							&data, q->queue, 0, ind, 1);
		visit(data);
	}

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

	q->buff_state = QUEUE_NONE;

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
