#include "main.h"

#include <math.h>

struct bitree b;
struct bitreeData bd;

static void visit(bitreeCore_t bc)
{
	if (bc == BINARYTREE_NULL) {
		printf("visit param error!\r\n");
		return;
	}

	printf("bc->data->_8data: %d\r\n", bc->data._8data);
	printf("bc->lc:           %p\r\n", bc->lc);
	printf("bc->rc:           %p\r\n", bc->rc);
}

int main()
{
	printf("\r\n********** init ***********\r\n");
	bitree_init(&b, "test");
	printf("b_depth:    %d\r\n", (int)b.depth(&b));
	printf("b_length:   %d\r\n", (int)b.length(&b));
	printf("b_leafNum:  %d\r\n", (int)b.leafNum(&b));

	printf("\r\n*********** add ***********\r\n");
	int times = (int)pow(2, 3) - 1;
	times -= 0;
	printf("add %d times...\r\n", times);
	for (int i = 0; i < times; i++) {
		bd._8data = i;
		b.add(&b, &bd);
	}
	printf("add finish!\r\n");
	printf("b_depth:    %d\r\n", (int)b.depth(&b));
	printf("b_length:   %d\r\n", (int)b.length(&b));
	printf("b_leafNum:  %d\r\n", (int)b.leafNum(&b));

	printf("\r\n******** traverse *********\r\n");
	b.traverse(&b, visit);

	printf("\r\n********* remove **********\r\n");
	bd._8data = 1;
	b.remove(&b, &bd);
	printf("remove finish!\r\n");
	printf("b_depth:    %d\r\n", (int)b.depth(&b));
	printf("b_length:   %d\r\n", (int)b.length(&b));
	printf("b_leafNum:  %d\r\n", (int)b.leafNum(&b));

	printf("\r\n******** traverse *********\r\n");
	b.traverse(&b, visit);

	return 0;
}
