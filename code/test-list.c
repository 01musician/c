#include<sys/queue.h>
#include<stdio.h>
#include<string.h>

typedef struct packet
{
	LIST_ENTRY(packet) next;
	char content[1024];
} st_packet;


int main()
{
	LIST_HEAD(packet_list, packet) y5;
	LIST_INIT(&y5);
	st_packet p1, p2, *p;
	
	strcpy(p1.content, "p1");
	strcpy(p2.content, "p2");

	LIST_INSERT_HEAD(&y5, &p1, next);
	LIST_INSERT_HEAD(&y5, &p2, next);

	for (p=y5.lh_first; p!=NULL; p = p->next.le_next)
		printf("%s-> ", p->content);

	printf("\n");

	return 0;
}

