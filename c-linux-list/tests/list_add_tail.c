#include <stdio.h>
#include <assert.h>
#include "list.h"

#include "common.h"

int main(void)
{
    struct list_head testlist;
    struct listitem item1;
    struct listitem item2;
    struct listitem item3;
    struct listitem item4;
    struct listitem *item = NULL;
    size_t i;

    item1.i = 1;
    item2.i = 2;
    item3.i = 3;
    item4.i = 4;

    INIT_LIST_HEAD(&testlist);
    assert(list_empty(&testlist));
/*
    list_add(&item4.list, &testlist);
    list_add_tail(&item2.list, &item4.list);
    list_add_tail(&item1.list, &item2.list);
    list_add_tail(&item3.list, &item4.list);
    */

    list_add_tail(&item1.list, &testlist);
    list_add_tail(&item2.list, &testlist);
    list_add_tail(&item3.list, &testlist);
    list_add_tail(&item4.list, &testlist);

    i = 1;
    list_for_each_entry (item, &testlist, list) {
	printf("position %zu is %d \n", i, item->i);
        //assert(item->i == i);
        i++;
    }
    assert(i == 5);

    return 0;
}
