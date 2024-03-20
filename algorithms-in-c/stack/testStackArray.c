#include<stdlib.h>
#include<stdio.h>
#include "Item.h"
#include "STACK.h"

int main(int argc, char **argv)
{
    STACKinit(100);
    STACKpush(1);
    STACKpush(2);
    STACKpush(3);
    
    printf("isempty: %d. \n", STACKempty());
    printf("first pop: %d. \n", STACKpop());

    return 0;
}


