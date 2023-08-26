#include "binaryTree.h"

#include "queue/queue.h"

#include <stdlib.h>
#include <math.h>

static void* bitree_malloc_bitreeCore(void)
{
	return obj_malloc(sizeof(struct bitreeCore));
}

static void bitree_free_bitreeCore(bitreeCore_t bc)
{
	if (bc == BINARYTREE_NULL) return;
	obj_free(bc);
}

static bitree_size_t _bitree_count_subTree_num(bitreeCore_t bc)
{
	bitree_size_t num = 0;

	if (bc == BINARYTREE_NULL) {
		num = -1;
		return num;
	}

	if (bc->lc != BINARYTREE_NULL) num++;
	if (bc->rc != BINARYTREE_NULL) num++;

	return num;
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
	if (*bch == BINARYTREE_NULL) {  // 未挂载树
		*bch = bitree_malloc_bitreeCore();
		if (*bch == BINARYTREE_NULL) return -BINARYTREE_ERROR;
		obj_memcpy(&((*bch)->data), data, sizeof((*bch)->data));
		(*bch)->lc = BINARYTREE_NULL;
		(*bch)->rc = BINARYTREE_NULL;
		goto bitree_add_ok;
	}
	else {  // 已挂载树
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

static bitreeCore_t _bitree_find(bitreeCore_t bc, bitreeData_t data)
{
	bitreeCore_t target = BINARYTREE_NULL;

	if (bc == BINARYTREE_NULL) return BINARYTREE_NULL;

	int ret = obj_memcmp(&bc->data, data, sizeof(bc->data));
	if (ret == 0) {
		target = bc;
		return target;
	}

	target = _bitree_find(bc->lc, data);
	if (target != BINARYTREE_NULL) return target;
	target = _bitree_find(bc->rc, data);
	if (target != BINARYTREE_NULL) return target;

	return BINARYTREE_NULL;
}

static bitreeCore_t _bitree_find_parent_node(bitreeCore_t bc, bitreeData_t data)
{
	bitreeCore_t target = BINARYTREE_NULL;

	if (bc == BINARYTREE_NULL) return BINARYTREE_NULL;
	if ((bc->lc == BINARYTREE_NULL) && (bc->rc == BINARYTREE_NULL)) return BINARYTREE_NULL;

	int ret;
	if (bc->lc != BINARYTREE_NULL) {
		ret = obj_memcmp(&bc->lc->data, data, sizeof(bc->lc->data));
		if (ret == 0) goto _bitree_find_parent_node_find_it;
	}
	if (bc->rc != BINARYTREE_NULL) {
		ret = obj_memcmp(&bc->rc->data, data, sizeof(bc->rc->data));
		if (ret == 0) goto _bitree_find_parent_node_find_it;
	}
	if (0) {
	_bitree_find_parent_node_find_it:
		target = bc;
		return target;
	}

	target = _bitree_find_parent_node(bc->lc, data);
	if (target != BINARYTREE_NULL) return target;
	target = _bitree_find_parent_node(bc->rc, data);
	if (target != BINARYTREE_NULL) return target;

	return BINARYTREE_NULL;
}

static bitreeCore_t _bitree_find_not_full_node(bitreeCore_t bc)
{
	bitreeCore_t target = BINARYTREE_NULL;

	while (bc != BINARYTREE_NULL) {
		if (bc->lc == BINARYTREE_NULL) goto _bitree_find_not_full_node_ok;
		if (bc->rc == BINARYTREE_NULL) goto _bitree_find_not_full_node_ok;
		bc = bc->lc;
	}

	if (0) {
	_bitree_find_not_full_node_ok:
		target = bc;
		return target;
	}

	return BINARYTREE_NULL;
}

bitree_err_t _bitree_remove(struct bitree* b, bitreeData_t data)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	if (data == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	bitreeCore_t* bch;
	bch = &b->head;

	if (*bch == BINARYTREE_NULL) return -BINARYTREE_ERROR;

	// 查找
	// 目标结点
	bitreeCore_t target = _bitree_find(*bch, data);
	if (target == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	// 父结点
	bitreeCore_t parent = _bitree_find_parent_node(*bch, data);
	// 计算目标结点的子树数目
	bitree_size_t subTree_num = _bitree_count_subTree_num(target);
	if (subTree_num == (bitree_size_t)(-1)) return -BINARYTREE_PARAM;
	if (parent == BINARYTREE_NULL) {
		// 目标结点存在，但没有父结点，因此目标结点为根结点
		if (subTree_num == 0) {
			*bch = BINARYTREE_NULL;
		}
		else if (subTree_num == 1) {
			if (target->lc != BINARYTREE_NULL) *bch = target->lc;
			else *bch = target->rc;
		}
		else if (subTree_num == 2) {
			bitreeCore_t not_full_tree = _bitree_find_not_full_node(target->lc);
			if (not_full_tree == BINARYTREE_NULL) return -BINARYTREE_ERROR;
			*bch = target->lc;
			if (not_full_tree->lc == BINARYTREE_NULL) not_full_tree->lc = target->rc;
			else not_full_tree->rc = target->rc;
		}
	}
	else {
		if (subTree_num == 0) {
			if (parent->lc == target) parent->lc = BINARYTREE_NULL;
			else parent->rc = BINARYTREE_NULL;
		}
		else if (subTree_num == 1) {
			if (parent->lc == target) {
				if (target->lc != BINARYTREE_NULL) parent->lc = target->lc;
				else parent->lc = target->rc;
			}
			else {
				if (target->lc != BINARYTREE_NULL) parent->rc = target->lc;
				else parent->rc = target->rc;
			}
		}
		else if (subTree_num == 2) {
			bitreeCore_t not_full_tree = _bitree_find_not_full_node(target->lc);
			if (not_full_tree == BINARYTREE_NULL) return -BINARYTREE_ERROR;
			if (parent->lc == target) parent->lc = target->lc;
			else parent->rc = target->lc;
			if (not_full_tree->lc == BINARYTREE_NULL) not_full_tree->lc = target->rc;
			else not_full_tree->rc = target->rc;
		}
	}

	// 删除
	bitree_free_bitreeCore(target);

	return BINARYTREE_EOK;
}

static bitree_size_t _bitree_get_length(bitreeCore_t bc)
{
	if (bc == BINARYTREE_NULL) return 0;
	return _bitree_get_length(bc->lc) + _bitree_get_length(bc->rc) + 1;
}

bitree_err_t _bitree_length(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return _bitree_get_length(b->head);
}

static bitree_size_t _bitree_get_leafNum(bitreeCore_t bc)
{
	if (bc == BINARYTREE_NULL) return 0;
	if ((bc->lc == BINARYTREE_NULL) && (bc->rc == BINARYTREE_NULL)) return 1;
	return _bitree_get_leafNum(bc->lc) + _bitree_get_leafNum(bc->rc);
}

bitree_err_t _bitree_leafNum(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return _bitree_get_leafNum(b->head);
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

bitree_err_t _bitree_traverse(struct bitree* b, void(*visit)(void* data))
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
