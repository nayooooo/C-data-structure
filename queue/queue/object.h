#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdint.h>

/*========================================================
	configuration micro
========================================================*/
#ifdef NULL
#	define OBJ_NULL				NULL
#else
#	define OBJ_NULL				(void*)0)
#endif // NULL

#define OBJ_NAME_LEN			(20)

#define OBJ_EOK					(0)
#define OBJ_ERROR				(1)
#define OBJ_PARAM				(2)

/*========================================================
	base typedef
========================================================*/
typedef unsigned int	obj_base_t;
typedef obj_base_t		obj_flag_t;
typedef obj_base_t		obj_size_t;
typedef obj_flag_t		obj_err_t;

typedef int8_t			obj_int8_t;
typedef int16_t			obj_int16_t;
typedef int32_t			obj_int32_t;
typedef int64_t			obj_int64_t;
typedef uint8_t			obj_uint8_t;
typedef uint16_t		obj_uint16_t;
typedef uint32_t		obj_uint32_t;
typedef uint64_t		obj_uint64_t;

typedef obj_uint8_t		obj_sflag_t;

/*========================================================
	base object
========================================================*/
struct object {
	char name[OBJ_NAME_LEN];

	obj_flag_t flag;
};
typedef struct object* object_t;

/*========================================================
	base function
========================================================*/
void* obj_malloc(obj_size_t size);
void obj_free(void* block);

void* obj_memcpy(void* dst, void* src, obj_size_t size);
int obj_memcmp(const void* buf1, const void* buf2, obj_size_t size);

#endif // !__OBJECT_H__
