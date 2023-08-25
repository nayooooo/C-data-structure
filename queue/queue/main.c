#include "main.h"

struct queue q;
queue_uint8_t tx_buff[50] = { 0 };
queue_uint8_t rx_buff[50] = { 0 };

void my_queue_visit(queue_uint8_t data)
{
	printf("%d\r\n", (int)data);
}

int main()
{
	for (int i = 0; i < 50; i++) {
		tx_buff[i] = i;
	}

	printf("\r\n********** init ***********\r\n");
	queue_init(&q, "test");
	q.build(&q, QUEUE_UNIT_TYPE_8BIT, 100);
	printf("q_name:    %s\r\n", q.parent.name);
	printf("queue_p:   %p\r\n", q.queue);
	printf("queue_len: %d\r\n", (int)q.queue_size);

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
