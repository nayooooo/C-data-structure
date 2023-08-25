#ifndef __QUEUE_CONF_H__
#define __QUEUE_CONF_H__

#if !WIN32
#error the queue need use win32!
#error the queue need win32 at queue_unit_handle where use stdarg.h
#error if no win32, pointer will be error!
#endif

#define QUEUE_UNIT_USE_8BIT			(1)
#define QUEUE_UNIT_USE_16BIT		(1)
#define QUEUE_UNIT_USE_32BIT		(1)
#define QUEUE_UNIT_USE_64BIT		(0)

#endif // !__QUEUE_CONF_H__
