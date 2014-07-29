#include<stdio.h>

int main() {
	int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10 ,11, 12}};

	printf("a = %p\n", a);
	printf("*a = %p\n", *a);
	printf("a[0] = %p\n", a[0]);
	printf("&a[0] = %p\n", &a[0]);
	printf("a[0][0] = %d\n", a[0][0]);
	printf("&a[0][0] = %p\n", &a[0][0]);
	
	printf("a + 1 = %p\n", a + 1);
	printf("*(a + 1) = %p\n", *(a + 1));
	printf("a[1] = %p\n", a[1]);
	printf("&a[1] = %p\n", &a[1]);
	printf("&a[1][0] = %p\n", &a[1][0]);
	printf("a[1][0] = %d\n", a[1][0]);

	printf("a[2] + 1 = %p\n", a[2] + 1);
	printf("(a + 2) + 1 = %p\n", (a + 2) + 1);
	printf("*(a + 2) = %p\n", *(a + 2));
	printf("*((a + 2) + 1) = %p\n", *((a + 2) + 1));
	printf("*(*(a + 2) + 1) = %d\n", *(*(a + 2) + 1));

	return 0;
}
