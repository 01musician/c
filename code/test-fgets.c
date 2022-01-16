#include<stdio.h>
#include<string.h>




int main()
{
    char line[256];

    fgets(line, sizeof(line), stdin);


	printf("%s. \n", line);

	return 0;
}

