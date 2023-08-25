#include "main.h"

#define MAIN_USE_8BIT		(0)
#define MAIN_USE_16BIT		(1)
#define MAIN_USE_32BIT		(0)
#if !(MAIN_USE_8BIT || MAIN_USE_16BIT || MAIN_USE_32BIT)
#error you must choose one kind!
#endif
#if MAIN_USE_8BIT + MAIN_USE_16BIT + MAIN_USE_32BIT != 1
#error you must choose only one kind!
#endif

struct queue q;
#if MAIN_USE_8BIT
queue_uint8_t tx_buff[50] = { 0 };
queue_uint8_t rx_buff[50] = { 0 };
#elif MAIN_USE_16BIT
queue_uint16_t tx_buff[50] = { 0 };
queue_uint16_t rx_buff[50] = { 0 };
#elif MAIN_USE_32BIT
queue_uint32_t tx_buff[50] = { 0 };
queue_uint32_t rx_buff[50] = { 0 };
#endif

void my_queue_visit(void* data)
{
#if MAIN_USE_8BIT
	printf("%d\r\n", (int)(*((queue_uint8_t*)data)));
#elif MAIN_USE_16BIT
	printf("%d\r\n", (int)(*((queue_uint16_t*)data)));
#elif MAIN_USE_32BIT
	printf("%d\r\n", (int)(*((queue_uint32_t*)data)));
#endif
}

int main()
{
	for (int i = 0; i < 50; i++) {
		tx_buff[i] = i;
	}

	printf("\r\n********** init ***********\r\n");
	queue_init(&q, "test");
#if MAIN_USE_8BIT
	q.build(&q, QUEUE_UNIT_TYPE_8BIT, 100);
#elif MAIN_USE_16BIT
	q.build(&q, QUEUE_UNIT_TYPE_16BIT, 100);
#elif MAIN_USE_32BIT
	q.build(&q, QUEUE_UNIT_TYPE_32BIT, 100);
#endif
	printf("q_name:    %s\r\n", q.parent.name);
	printf("queue_p:   %p\r\n", q.queue);
	printf("queue_len: %d\r\n", (int)q.queue_size);
	{
		int true_size;
		if (!obj_memcmp(q.type, QUEUE_UNIT_TYPE_8BIT, strlen(QUEUE_UNIT_TYPE_8BIT)))
			true_size = 1;
		else if (!obj_memcmp(q.type, QUEUE_UNIT_TYPE_16BIT, strlen(QUEUE_UNIT_TYPE_16BIT)))
			true_size = 2;
		else if (!obj_memcmp(q.type, QUEUE_UNIT_TYPE_32BIT, strlen(QUEUE_UNIT_TYPE_32BIT)))
			true_size = 4;
		else
			true_size = 0;
		printf("malloc true size: %d", (int)(q.queue_size * true_size));
	}

	for (int i = 0; i < 2; i++) {
		printf("\r\n********* handle **********\r\n");
		printf("q_length:  %d\r\n", q.length(&q));
		printf("q_state:   %s\r\n", queue_state_code_to_string(q.state(&q)));
		printf("\r\n****** handle enter *******\r\n");
		q.enter(&q, tx_buff, 50);
		printf("q_length:  %d\r\n", q.length(&q));
		printf("q_state:   %s\r\n", queue_state_code_to_string(q.state(&q)));
		printf("\r\n******* handle read *******\r\n");
		q.read(&q, rx_buff);
		printf("q_length:  %d\r\n", q.length(&q));
		printf("q_state:   %s\r\n", queue_state_code_to_string(q.state(&q)));
		printf("q_read:    %d\r\n", (int)rx_buff[0]);
		printf("\r\n***** handle traverse *****\r\n");
		q.traverse(&q, my_queue_visit);
		printf("\r\n******* handle out ********\r\n");
		q.out(&q, rx_buff, 50);
		printf("q_length:  %d\r\n", q.length(&q));
		printf("q_state:   %s\r\n", queue_state_code_to_string(q.state(&q)));
		printf("q_out:\r\n");
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 5; j++) {
				printf("%d\t", (int)rx_buff[i * 5 + j]);
			}
			printf("\r\n");
		}
	}

	return 0;
}
