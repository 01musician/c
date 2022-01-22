#include<stdio.h>
#include<stdint.h>
#include<string.h>

struct byte4
{
   uint32_t i;
   uint32_t j;
};

struct byte8
{
   uint32_t i;
   uint64_t j;
};




int main()
{

	printf("sizeof(4byte) is %d;. \n", sizeof(struct byte4));
	printf("sizeof(8byte) is %d;. \n", sizeof(struct byte8));

	return 0;
}

