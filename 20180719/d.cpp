#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
    int n, m1, m2;
    while (scanf("%d%d%d", &n, &m1, &m2) != EOF) {
        int a[8], b[8];
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        while (m1--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--, y--;
            a[x] |= (1 << y);
            a[y] |= (1 << x);
        }

        while (m2--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--, y--;
            b[x] |= (1 << y);
            b[y] |= (1 << x);
        }

        int c[8];
        for (int i = 0; i < n; i++) c[i] = i;

        int d[8], ans = 0;
        do {
            memset(d, 0, sizeof(d));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (b[i] & (1 << j)) d[c[i]] |= (1 << c[j]);

            bool flag = true;
            for (int i = 0; i < n; i++)
                if ((d[i] & a[i]) != a[i]) {
                    flag = false;
                }

            if (flag) ans++;
        } while (next_permutation(c, c + n));

        for (int i = 0; i < n; i++) c[i] = i;
        int rep = 0;
        do {
            memset(d, 0, sizeof(d));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (a[i] & (1 << j)) d[c[i]] |= (1 << c[j]);

            bool flag = true;
            for (int i = 0; i < n; i++)
                if (a[i] != d[i]) {
                    flag = false;
                }

            if (flag) rep++;
        } while (next_permutation(c, c + n));

        printf("%d\n", ans / rep);
    }
    return 0;
}
