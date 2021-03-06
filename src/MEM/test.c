#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 4

unsigned getbits (unsigned x, int p, int n) {
	return (x >> (p+1-n) & ~(~0 << n));
}

char *tobinary(unsigned int x) {
	static char res[] = "";
	return res;
}

int
main (void) {
	char * ptr = NULL;
	ptr = (char *) malloc (BUF);
	if (ptr == NULL) {
		exit(1);
	}
	memset(ptr, 0X00, BUF);
	printf("now ptr is [%s] and sizeof it is [%lu] and strlen of it is [%lu]\n", ptr, sizeof ptr, strlen(ptr));
	memcpy(ptr, "speedmax", strlen("speedmax"));
	printf("now ptr is [%s] and sizeof it is [%lu] and strlen of it is [%lu]\n", ptr, sizeof ptr, strlen(ptr));
	memset(ptr, 0X00, BUF);
	memcpy(ptr, "speedmax", sizeof("speedmax"));
	printf("now ptr is [%s and sizeof it is [%lu] and strlen of it is [%lu] and sizeof \"speedmax\" is [%lu] and strlen \"speedmax\" is [%lu]\n", ptr, sizeof ptr, strlen(ptr), sizeof("speedmax"), strlen("speedmax"));
	char * ptr1 = "hello";
	int i = 1;
	long j = 1;
	int * I = &i;
	long * J = &j;
	char k = 'k';
	float f = 0.00;
	long l = 0;
	printf("now ptr is [%s] and sizeof it is [%lu] and strlen of it is [%lu]\n", ptr1, sizeof ptr1, strlen(ptr1));
	printf("now int is [%lu]\n", sizeof i);
	printf("now long is [%lu]\n", sizeof j);
	printf("now pointer to int is [%lu]\n", sizeof I);
	printf("now pointer to long is [%lu]\n", sizeof J);
	printf("now char is [%lu]\n", sizeof k);
	printf("float is [%lu]\n", sizeof(f));
	printf("long is [%lu]\n", sizeof(l));
	free(ptr);
	ptr = NULL;
	int ii = i++;
	printf("after \"ii=i++\", ii is now [%d]\n", ii);
	i = 1;
	ii = ++i;
	printf("after \"ii=++i\", ii is now [%d]\n", ii);//this means left ++ has a higher priority than =, right ++ oppsites
	ii = 13;
	printf("ii is now %x\n", ii);
	ii = getbits(ii, 2, 3);
	printf("now ii should be 5 and ii is %d actually\n", ii);
	int * index = calloc(3, sizeof(index));
	ii = 1;
	for(; ii <= 3; index[ii] = ii, printf("index[%d] = %d\n", ii, index[ii]), ii++);
	free(index);
	index = NULL;
	return 0;
}
	
