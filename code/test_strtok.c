#include <stdio.h>
#include <string.h>

int main() {
    char buf[8]="5/90/45";
    char buf1[8]="5/90/45";
    //char buf1[14] = "//5//90//45//";
    char *token;
    char *lasts;
    int i=0;

    printf("tokenizing \"%s\" with \"/\" using strtok():\n", buf);
    if ((token = strtok(buf, "/")) != NULL) {
        i++;
        printf("token = \"%s\"\n", token);
        while ((token = strtok(NULL, "/")) != NULL) {
            printf("token = \"%s\"\n", token);
            i++;
        }
    }
    printf("iteration num is:%d.\n", i);

    i=0;
    printf("\ntokenizing \"%s\" with \"/\" using strtok_r():\n", buf1);
    if ((token = strtok_r(buf1, "/", &lasts)) != NULL) {
        i++;
        printf("token = \"%s\"\n", token);
        while ((token = strtok_r(NULL, "/", &lasts)) != NULL) {
            printf("token = \"%s\"\n", token);
            i++;
        }
    }

    printf("iteration num is:%d.\n", i);

    return 0;
}
