#include "binaryTree.h"

/*
* search order: first left then right, level traversal
* insertion rule: insert nearby, that is, insert when empty is found
*/
bitree_err_t _bitree_add(struct bitree* b, bitreeData_t data)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	if (data == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	bitreeCore_t bch, bc;
	bch = &b->core;

	return 0;
}

bitree_err_t _bitree_remove(struct bitree* b, bitreeData_t data)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;
	if (data == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return 0;
}

bitree_err_t _bitree_length(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return 0;
}

bitree_err_t _bitree_leafNum(struct bitree* b)
{
	if (b == BINARYTREE_NULL) return -BINARYTREE_PARAM;

	return 0;
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

	b->core.data._8data = 0;
	b->core.lc = BINARYTREE_NULL;
	b->core.rc = BINARYTREE_NULL;

	b->add = _bitree_add;
	b->remove = _bitree_remove;
	b->length = _bitree_length;
	b->leafNum = _bitree_leafNum;
	b->traverse = _bitree_traverse;

	return BINARYTREE_EOK;
}
