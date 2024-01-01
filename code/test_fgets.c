#include <stdio.h>
#include <string.h>

int main() {
    char buf[8]="5/90/45";
    char buf1[8]="5/90/45";
    //char buf1[14] = "//5//90//45//";
    char *token;
    char *lasts;

    printf("tokenizing \"%s\" with strtok():\n", buf);
    if ((token = strtok(buf, "/")) != NULL) {
        printf("token = \"%s\"\n", token);
        while ((token = strtok(NULL, "/")) != NULL) {
            printf("token = \"%s\"\n", token);
        }
    }

    printf("\ntokenizing \"%s\" with strtok_r():\n", buf1);
    if ((token = strtok_r(buf1, "/", &lasts)) != NULL) {
        printf("token = \"%s\"\n", token);
        while ((token = strtok_r(NULL, "/", &lasts)) != NULL) {
            printf("token = \"%s\"\n", token);
        }
    }
}
