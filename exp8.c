#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 50

int replaceAll(char doc[][LEN], int n, char key[], char rep[]) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (strcmp(doc[i], key) == 0) {
            strcpy(doc[i], rep);
            count++;
        }
    }
    return count;
}

int main(void) {
    char doc[MAX][LEN];
    char key[LEN], rep[LEN];
    int n, i, count;

    printf("Number of words in the document: ");
    scanf("%d", &n);

    printf("Enter the words:\n");
    for (i = 0; i < n; i++)
        scanf("%s", doc[i]);

    printf("Enter the term to find: ");
    scanf("%s", key);
    printf("Enter the replacement word: ");
    scanf("%s", rep);

    count = replaceAll(doc, n, key, rep);

    printf("\nNumber of replacements made: %d\n", count);
    printf("Updated document:\n");
    for (i = 0; i < n; i++)
        printf("%s ", doc[i]);
    printf("\n");

    return 0;
}
