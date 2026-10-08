#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[50];
    struct Node *next;
};

struct Node *head = NULL;

int exists(char name[]) {
    struct Node *p = head;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

void installApp(char name[]) {
    struct Node *n;
    if (exists(name)) {
        printf("App already installed\n");
        return;
    }
    n = (struct Node *)malloc(sizeof(struct Node));
    strcpy(n->name, name);
    n->next = head;
    head = n;
    printf("%s installed\n", name);
}

void openApp(char name[]) {
    struct Node *p = head, *prev = NULL;
    while (p != NULL && strcmp(p->name, name) != 0) {
        prev = p;
        p = p->next;
    }
    if (p == NULL) {
        printf("App not found\n");
        return;
    }
    if (prev != NULL) {
        prev->next = p->next;
        p->next = head;
        head = p;
    }
    printf("%s opened\n", name);
}

void removeLast(void) {
    struct Node *p;
    if (head == NULL) {
        printf("No apps to remove\n");
        return;
    }
    if (head->next == NULL) {
        printf("Uninstalled %s\n", head->name);
        free(head);
        head = NULL;
        return;
    }
    p = head;
    while (p->next->next != NULL)
        p = p->next;
    printf("Uninstalled %s\n", p->next->name);
    free(p->next);
    p->next = NULL;
}

void cleanApps(int k) {
    int i;
    for (i = 0; i < k && head != NULL; i++)
        removeLast();
}

void display(void) {
    struct Node *p = head;
    if (p == NULL) {
        printf("No apps installed\n");
        return;
    }
    printf("Most used -> Least used:\n");
    while (p != NULL) {
        printf("%s", p->name);
        if (p->next != NULL)
            printf(" -> ");
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    int choice, k;
    char name[50];

    do {
        printf("\n1. Install app\n2. Open app\n3. Clean least used apps\n4. Display apps\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("App name: ");
                scanf("%s", name);
                installApp(name);
                break;
            case 2:
                printf("App name: ");
                scanf("%s", name);
                openApp(name);
                break;
            case 3:
                printf("Number of apps to remove: ");
                scanf("%d", &k);
                cleanApps(k);
                break;
            case 4:
                display();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);
    return 0;
}
