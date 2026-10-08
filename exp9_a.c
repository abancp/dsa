#include <stdio.h>
#define M 2005
long long r[M];
int main() {
    int n, m, i, j, e;
    long long a[M], b[M];
    int x[M], y[M];
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%lld %d", &a[i], &x[i]);
    scanf("%d", &m);
    for (j = 0; j < m; j++) scanf("%lld %d", &b[j], &y[j]);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            r[x[i] + y[j]] += a[i] * b[j];
    for (e = M - 1; e >= 0; e--)
        if (r[e]) printf("%lld %d\n", r[e], e);
    return 0;
}
