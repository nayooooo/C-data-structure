#include "main.h"

struct bitree b;
struct bitreeData bd;

int main()
{
	printf("\r\n********** init ***********\r\n");
	bitree_init(&b, "test");
	for (int i = 0; i < 5; i++) {
		bd._8data = i;
		b.add(&b, &bd);
	}

	return 0;
}
