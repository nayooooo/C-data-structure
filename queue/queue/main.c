#include "main.h"

struct queue q;

int main()
{
	queue_init(&q, "test");
	q.build(&q, 100);
	printf("\r\n********** init ***********\r\n");
	printf("q_name:    %s\r\n", q.parent.name);
	printf("queue_p:   %p\r\n", q.queue);
	printf("queue_len: %d\r\n", (int)q.queue_size);

	return 0;
}
