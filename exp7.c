#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 100

struct Stack {
    char data[MAX][LEN];
    int top;
};

struct Stack backSt;
struct Stack fwdSt;
char current[LEN];

void init(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int push(struct Stack *s, char url[]) {
    if (s->top == MAX - 1)
        return 0;
    s->top++;
    strcpy(s->data[s->top], url);
    return 1;
}

void pop(struct Stack *s, char out[]) {
    strcpy(out, s->data[s->top]);
    s->top--;
}

void visit(char url[]) {
    if (!push(&backSt, current)) {
        printf("History full\n");
        return;
    }
    strcpy(current, url);
    init(&fwdSt);
}

void back(void) {
    if (isEmpty(&backSt)) {
        printf("No page to go back to\n");
        return;
    }
    push(&fwdSt, current);
    pop(&backSt, current);
}

void forward(void) {
    if (isEmpty(&fwdSt)) {
        printf("No page to go forward to\n");
        return;
    }
    push(&backSt, current);
    pop(&fwdSt, current);
}

int main(void) {
    int choice;
    char url[LEN];

    init(&backSt);
    init(&fwdSt);
    strcpy(current, "https://ktu.edu.in/");

    do {
        printf("\n1. Visit URL\n2. Back\n3. Forward\n4. Current page\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visit(url);
                break;
            case 2:
                back();
                break;
            case 3:
                forward();
                break;
            case 4:
                printf("Current: %s\n", current);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);
    return 0;
}
