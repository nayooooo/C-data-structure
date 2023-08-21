#include "main.h"

stack_uint8_t test_buff[50] = { 0 };
stack_uint8_t read_buff[50] = { 0 };

int main()
{
	stack_err_t err;
	struct stack s;
	stack_size_t s_len = 100;

	err = stack_init(&s, "test");
	s.build(&s, s_len);
	printf("\r\n********** init ***********\r\n");
	printf("s_name:    %s\r\n", s.parent.name);
	printf("stack_p:   %p\r\n", s.stack);
	printf("stack_len: %d\r\n", (int)s.stack_size);

	for (int i = 0; i < 50; i++) {
		test_buff[i] = i;
	}

	printf("\r\n********* handle **********\r\n");
	s.push(&s, test_buff, 50);
	s.read(&s, &read_buff[0]);
	printf("read byte: %d\r\n", read_buff[0]);
	s.pop(&s, read_buff, 50);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d\t", read_buff[i * 5 + j]);
		}
		printf("\r\n");
	}

	s.destroy(&s);
	printf("\r\n********* destory *********\r\n");
	printf("s_p:     %p\r\n", &s);
	printf("stack_p: %p\r\n", s.stack);

	return 0;
}
