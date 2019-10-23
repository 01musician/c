#include<stdlib.h>
#include<stdio.h>

void printchar(char **p)
{
	printf("**p is: %c.\n", **p);
	return ;
}


int main(int argc, char **argv)
{
	char c[16][256];
	int  i[16][256];
	int  a;
	char (*p)[16];

	printf("sizeof(c) is: %zu; sizeof(c[0]):%zu. \n", sizeof(c), sizeof(c[0]));
	printf("sizeof(i) is: %zu; sizeof(i[0]):%zu. \n", sizeof(i), sizeof(i[0]));

	for(a = 0; a < sizeof(c)/sizeof(c[0]); a++ )
	{
		snprintf(c[a], sizeof(c[a]), "%d's line.", a);
	}

	p = c;
	printf("c[0]:%s.\n", c[0]);
	printf("*p:%s.\n", *p);


	return 0;
}
