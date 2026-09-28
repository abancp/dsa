#include <stdio.h>

#define MAX 50

struct Term {
    int coeff;
    int exp;
};

void readPoly(struct Term p[], int *n, char name) {
    int i;
    printf("Number of terms in %c: ", name);
    scanf("%d", n);
    printf("Enter coefficient and exponent for each term:\n");
    for (i = 0; i < *n; i++)
        scanf("%d %d", &p[i].coeff, &p[i].exp);
}

void printPoly(struct Term p[], int n) {
    int i, a;
    if (n == 0) {
        printf("0\n");
        return;
    }
    for (i = 0; i < n; i++) {
        a = p[i].coeff < 0 ? -p[i].coeff : p[i].coeff;
        if (i == 0) {
            if (p[i].coeff < 0)
                printf("-");
        } else {
            if (p[i].coeff < 0)
                printf(" - ");
            else
                printf(" + ");
        }
        if (p[i].exp == 0) {
            printf("%d", a);
        } else {
            if (a != 1)
                printf("%d", a);
            printf("x");
            if (p[i].exp != 1)
                printf("^%d", p[i].exp);
        }
    }
    printf("\n");
}

int multiply(struct Term p[], int n, struct Term q[], int m, struct Term r[]) {
    int i, j, k, cnt = 0, found, c, e;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            c = p[i].coeff * q[j].coeff;
            e = p[i].exp + q[j].exp;
            found = -1;
            for (k = 0; k < cnt; k++) {
                if (r[k].exp == e)
                    found = k;
            }
            if (found != -1) {
                r[found].coeff += c;
            } else {
                r[cnt].coeff = c;
                r[cnt].exp = e;
                cnt++;
            }
        }
    }
    return cnt;
}

int removeZeros(struct Term r[], int cnt) {
    int k, t = 0;
    for (k = 0; k < cnt; k++) {
        if (r[k].coeff != 0) {
            r[t] = r[k];
            t++;
        }
    }
    return t;
}

void sortDescending(struct Term r[], int cnt) {
    int i, j;
    struct Term temp;
    for (i = 0; i < cnt - 1; i++) {
        for (j = 0; j < cnt - i - 1; j++) {
            if (r[j].exp < r[j + 1].exp) {
                temp = r[j];
                r[j] = r[j + 1];
                r[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    struct Term p[MAX], q[MAX], r[MAX * MAX];
    int n, m, cnt;

    readPoly(p, &n, 'P');
    readPoly(q, &m, 'Q');

    cnt = multiply(p, n, q, m, r);
    cnt = removeZeros(r, cnt);
    sortDescending(r, cnt);

    printf("\nP(x) = ");
    printPoly(p, n);
    printf("Q(x) = ");
    printPoly(q, m);
    printf("P(x) * Q(x) = ");
    printPoly(r, cnt);

    return 0;
}
