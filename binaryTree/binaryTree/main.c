#include "main.h"

struct bitree b;
struct bitreeData bd;

int main()
{
	printf("\r\n********** init ***********\r\n");
	bitree_init(&b, "test");
	printf("b_depth:    %d\r\n", (int)b.depth(&b));
	printf("b_length:   %d\r\n", (int)b.length(&b));

	printf("\r\n********** add ************\r\n");
	printf("add 5 times...\r\n");
	for (int i = 0; i < 5; i++) {
		bd._8data = i;
		b.add(&b, &bd);
	}
	printf("add finish!\r\n");
	printf("b_depth:    %d\r\n", (int)b.depth(&b));
	printf("b_length:   %d\r\n", (int)b.length(&b));

	return 0;
}
