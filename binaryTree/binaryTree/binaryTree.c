#include "binaryTree.h"

#include "queue/queue.h"

#include <stdlib.h>
#include <math.h>

static void* bitree_malloc_bitreeCore(void)
{
	return obj_malloc(sizeof(struct bitreeCore));
}

/*
* search order: first left then right, level traversal
* insertion rule: insert nearby, that is, insert when empty is found
*/
bitree_err_t _bitree_add(struct bitree* b, bitreeData_t data)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	if (data == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	bitreeCore_t* bch;
	bch = &b->head;

	// level traversal
	if (*bch == BINARYTREE_NULL) {  // Î´¹ÒÔØÊ÷
		*bch = bitree_malloc_bitreeCore();
		if (*bch == BINARYTREE_NULL) return -BINARYTREE_ERROR;
		obj_memcpy(&((*bch)->data), data, sizeof((*bch)->data));
		(*bch)->lc = BINARYTREE_NULL;
		(*bch)->rc = BINARYTREE_NULL;
		goto bitree_add_ok;
	}
	else {  // ÒÑ¹ÒÔØÊ÷
		// build queue
		struct queue q;
		queue_size_t q_size;
		queue_init(&q, "bitree_add");
		q_size = b->depth(b);
		if (q_size <= 0) return -BINARYTREE_ERROR;
		q_size = (queue_size_t)pow(2, q_size - 1);
		q.build(&q, QUEUE_UNIT_TYPE_32BIT, q_size);
		if (q.queue == QUEUE_NULL) return -BINARYTREE_ERROR;

		bitreeCore_t bc = *bch;
		q.enter(&q, &bc, 1);
		while (q.state(&q) != QUEUE_EMPTY) {
			q.out(&q, &bc, 1);
			if (bc->lc != BINARYTREE_NULL) q.enter(&q, &(bc->lc), 1);
			else break;
			if (bc->rc != BINARYTREE_NULL) q.enter(&q, &(bc->rc), 1);
			else break;
		}
		if ((bc->lc == BINARYTREE_NULL) || (bc->rc == BINARYTREE_NULL)) {
			bitreeCore_t temp = bitree_malloc_bitreeCore();
			if (temp == BINARYTREE_NULL) goto bitree_add_error;
			obj_memcpy(&temp->data, data, sizeof(temp->data));
			temp->lc = BINARYTREE_NULL;
			temp->rc = BINARYTREE_NULL;
			if (bc->lc == BINARYTREE_NULL) bc->lc = temp;
			else bc->rc = temp;
		}
		else goto bitree_add_error;

		// destroy queue
		q.destroy(&q);
		if (0) {
		bitree_add_error:
			q.destroy(&q);
			return -BINARYTREE_ERROR;
		}
	}

bitree_add_ok:
	return BINARYTREE_EOK;
}

bitree_err_t _bitree_remove(struct bitree* b, bitreeData_t data)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	if (data == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return BINARYTREE_EOK;
}

bitree_err_t _bitree_length(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return BINARYTREE_EOK;
}

bitree_err_t _bitree_leafNum(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return BINARYTREE_EOK;
}

static bitree_size_t _bitree_get_depth(bitreeCore_t bc)
{
	if (bc == BINARYTREE_NULL)
		return 0;
	return max(_bitree_get_depth(bc->lc), _bitree_get_depth(bc->rc)) + 1;
}

bitree_err_t _bitree_depth(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return (bitree_err_t)_bitree_get_depth(b->head);
}

bitree_err_t _bitree_traverse(struct bitree* b, void(*visit)(bitreeData_t data))
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	if (visit == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return BINARYTREE_EOK;
}

bitree_err_t bitree_init(struct bitree* b, const char* name)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	obj_memcpy(b->parent.name, name, OBJ_NAME_LEN);
	b->parent.flag = 0;

	b->head = BINARYTREE_NULL;

	b->add = _bitree_add;
	b->remove = _bitree_remove;
	b->length = _bitree_length;
	b->leafNum = _bitree_leafNum;
	b->depth = _bitree_depth;
	b->traverse = _bitree_traverse;

	return BINARYTREE_EOK;
}
