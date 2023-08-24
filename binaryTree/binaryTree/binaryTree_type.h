#ifndef __BINARYTREE_TYPE_H__
#define __BINARYTREE_TYPE_H__

#include "object.h"

/*========================================================
	configuration micro
========================================================*/
#define BINARYTREE_NULL			OBJ_NULL

#define BINARYTREE_EOK			OBJ_EOK
#define BINARYTREE_ERROR		OBJ_ERROR
#define BINARYTREE_PARAM		OBJ_PARAM

/*========================================================
	base typedef
========================================================*/
typedef obj_base_t			bitree_base_t;
typedef bitree_base_t		bitree_flag_t;
typedef bitree_base_t		bitree_size_t;
typedef bitree_flag_t		bitree_err_t;

typedef obj_int8_t			bitree_int8_t;
typedef obj_int16_t			bitree_int16_t;
typedef obj_int32_t			bitree_int32_t;
typedef obj_int64_t			bitree_int64_t;
typedef obj_uint8_t			bitree_uint8_t;
typedef obj_uint16_t		bitree_uint16_t;
typedef obj_uint32_t		bitree_uint32_t;
typedef obj_uint64_t		bitree_uint64_t;

typedef obj_sflag_t			bitree_sflag_t;

/*========================================================
	base object
========================================================*/
struct bitreeData {
	bitree_uint8_t _8data;
};
typedef struct bitreeData* bitreeData_t;

struct bitreeCore {
	struct bitreeData data;
	struct bitreeCore* lc;
	struct bitreeCore* rc;
};
typedef struct bitreeCore* bitreeCore_t;

struct bitree {
	struct object parent;

	struct bitreeCore core;

	bitree_err_t		(*add)				(struct bitree* b, bitreeData_t data);
	bitree_err_t		(*remove)			(struct bitree* b, bitreeData_t data);
	bitree_err_t		(*length)			(struct bitree* b);
	bitree_err_t		(*leafNum)			(struct bitree* b);
	bitree_err_t		(*traverse)			(struct bitree* b, void(*visit)(bitreeData_t data));
};
typedef struct bitree* bitree_t;

#endif // !__BINARYTREE_TYPE_H__
