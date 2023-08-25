#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "queue_type.h"

char* queue_state_code_to_string(queue_sflag_t code);

queue_err_t queue_init(struct queue* q, const char* name);

#endif // !__QUEUE_H__
