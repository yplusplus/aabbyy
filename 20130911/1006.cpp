#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 555;
int suma[N][N], sumb[N][N];
int a[N][N], b[N][N];
int n, m, r, q;
const int eps = 1001111;

int query(int l1, int r1, int l2, int r2, int sum[][555]) {
    l1 = max(l1, 1);
    l2 = min(l2, n);
    r1 = max(r1, 1);
    r2 = min(r2, m);
    return sum[l2][r2] + sum[l1 - 1][r1 - 1] - sum[l1 - 1][r2] - sum[l2][r1 - 1];
}

int remb[eps * 2], rema[eps * 2];

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &n, &m, &r, &q);
        memset(suma, 0, sizeof(suma));
        memset(sumb, 0, sizeof(sumb));
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &b[i][j]);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                suma[i][j] = suma[i - 1][j] + suma[i][j - 1] - suma[i - 1][j - 1] + a[i][j];
                sumb[i][j] = sumb[i - 1][j] + sumb[i][j - 1] - sumb[i - 1][j - 1] + b[i][j];
            }
        }
        memset(rema, 128, sizeof(rema));
        memset(remb, 128, sizeof(remb));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int l1 = i - r, r1 = j - r, l2 = i + r, r2 = j + r;
                int ai = query(l1, r1, l2, r2, suma);
                int bi = query(l1, r1, l2, r2, sumb);
                int d = ai - bi;
                d += eps;
                rema[d] = max(rema[d], ai);
                remb[d] = max(remb[d], bi);
            }
        }
        for (int i = eps * 2 - 5; i >= 0; i--) remb[i] = max(remb[i + 1], remb[i]);
        for (int i = 1; i < eps * 2; i++) rema[i] = max(rema[i - 1], rema[i]);

        printf("Case #%d:\n", Case++);
        while (q--) {
            int ai, bi;
            scanf("%d%d", &ai, &bi);
            int ci = bi - ai + eps;
            printf("%d\n", max(rema[ci] + ai, remb[ci] + bi));
        }
        if (T) puts("");
    }
    return 0;
}

