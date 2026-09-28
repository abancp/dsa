#include <stdio.h>

#define MAX 100

typedef struct {
    int token;
    int forms;
} Customer;

Customer q[MAX];
int front = 0, size = 0, nextToken = 1;

void enqueue(Customer c) {
    if (size == MAX) {
        printf("Queue full\n");
        return;
    }
    q[(front + size) % MAX] = c;
    size++;
}

Customer dequeue(void) {
    Customer c = q[front];
    front = (front + 1) % MAX;
    size--;
    return c;
}

void issueToken(void) {
    Customer c;
    printf("Number of tickets to book: ");
    scanf("%d", &c.forms);
    if (c.forms <= 0) {
        printf("Invalid number of tickets\n");
        return;
    }
    if (size == MAX) {
        printf("Queue full\n");
        return;
    }
    c.token = nextToken++;
    enqueue(c);
    printf("Token %d issued for %d ticket(s)\n", c.token, c.forms);
}

void serveOne(void) {
    if (size == 0) {
        printf("No customers in queue\n");
        return;
    }
    Customer c = dequeue();
    c.forms--;
    printf("Token %d: one form accepted\n", c.token);
    if (c.forms > 0) {
        enqueue(c);
        printf("Token %d goes to the tail with %d form(s) left\n", c.token, c.forms);
    } else {
        printf("Token %d is done\n", c.token);
    }
}

void currentCustomer(void) {
    if (size == 0)
        printf("No customer being served\n");
    else
        printf("Now serving token %d (%d form(s) left)\n", q[front].token, q[front].forms);
}

void waitingCount(void) {
    printf("Customers waiting: %d\n", size > 0 ? size - 1 : 0);
}

void listAll(void) {
    if (size == 0) {
        printf("Queue is empty\n");
        return;
    }
    printf("%-8s %-8s\n", "Token", "Forms");
    for (int i = 0; i < size; i++) {
        Customer c = q[(front + i) % MAX];
        printf("%-8d %-8d\n", c.token, c.forms);
    }
}

int main(void) {
    int choice;
    do {
        printf("\n1. Issue token\n");
        printf("2. Serve one form\n");
        printf("3. Current customer being served\n");
        printf("4. Number of customers waiting\n");
        printf("5. List all customers in queue\n");
        printf("6. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1)
            break;
        switch (choice) {
            case 1: issueToken(); break;
            case 2: serveOne(); break;
            case 3: currentCustomer(); break;
            case 4: waitingCount(); break;
            case 5: listAll(); break;
            case 6: break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 6);
    return 0;
}
