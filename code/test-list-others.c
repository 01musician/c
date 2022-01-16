#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
typedef struct _Cat {
	LIST_ENTRY(_Cat) pointers;
	char name[255];
	int color;
	char can_climb;
} Cat;
typedef struct _Dog {
	LIST_ENTRY(_Dog) pointers;
	char name[255];
	int color;
	char can_swim;
} Dog;

Cat *create_cat(char *name, int color, char can_climb);
Dog *create_dog(char *name, int color, char can_swim);
LIST_HEAD(cat_list, _Cat) cats;
LIST_HEAD(dog_list, _Dog) dogs;
int main()
{
	printf("\n--------------EXAMPLE------------------\n");
	Cat *cat1 = create_cat("Cat1", 2, 0);
	Cat *cat2 = create_cat("Cat2", 3, 1);
	Cat *cat3 = create_cat("Cat3", 4, 0);
	Cat *cat4 = create_cat("Cat4", 2, 0);
	LIST_INIT(&cats);
	LIST_INSERT_HEAD(&cats, cat1, pointers);
	LIST_INSERT_HEAD(&cats, cat2, pointers);
	LIST_INSERT_AFTER(cat2, cat3, pointers);
	LIST_INSERT_AFTER(cat3, cat4, pointers);
	LIST_REMOVE(cat4, pointers);
	Cat *cat;
	LIST_FOREACH(cat, &cats, pointers) {
		printf("\n%s", cat->name);
	}
	printf("\n");
	Dog *dog1 = create_dog("Dog1", 2, 0);
	Dog *dog2 = create_dog("Dog2", 3, 1);
	Dog *dog3 = create_dog("Dog3", 4, 0);
	Dog *dog4 = create_dog("Dog4", 2, 0);
	LIST_INIT(&dogs);
	LIST_INSERT_HEAD(&dogs, dog1, pointers);
	LIST_INSERT_HEAD(&dogs, dog2, pointers);
	LIST_INSERT_AFTER(dog2, dog3, pointers);
	LIST_INSERT_AFTER(dog3, dog4, pointers);
	LIST_REMOVE(dog4, pointers);
	Dog *dog;
	LIST_FOREACH(dog, &dogs, pointers) {
		printf("\n%s", dog->name);
	}
	printf("\n");
}
Cat *create_cat(char *name, int color, char can_climb) {
	Cat *cat = (Cat *)malloc(sizeof(Cat));
	strcpy(cat->name, name);
	cat->color = color;
	cat->can_climb = can_climb;
}
Dog *create_dog(char *name, int color, char can_swim) {
	Dog *dog = (Dog *)malloc(sizeof(Dog));
	strcpy(dog->name, name);
	dog->color = color;
	dog->can_swim = can_swim;
}
