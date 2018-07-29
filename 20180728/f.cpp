#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int N = 2010;

char s[N][N];
int a[N], b[N];
int d[N], c[N];

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }

    for (int i = 0; i < n; i++) {
        int x = m >> 1;
        a[i] = 0;
        for (int j = 0; j < x; j++)
            if (s[i][j] != s[i][m - 1 - j]) break;
            else a[i]++;
    }

    for (int i = 0; i < m; i++) {
        int x = n >> 1;
        b[i] = 0;
        for (int j = 0; j < x; j++)
            if (s[j][i] != s[n - 1 - j][i]) break;
            else b[i]++;
    }

    int ans = 0;
    for (int q = 1; q < (m >> 1); q++) {
        int tot = 0;
        for (int i = 1; i <= (m >> 1); i++) {
            if (b[i - 1] != (n >> 1)) break;
            if (b[m - i] != (n >> 1)) break;
            tot++;
        }
        if (tot < (m >> 1) - q) continue;
        int flag = true;
        for (int i = 0; i < n; i++) {
            if (a[i] < (m >> 1) - q) {
                flag = false;
                break;
            }
        }

        if (!flag) continue;

        tot = 0;
        for (int i = 0; i < (n >> 1); i++) {
            if (a[i] != (m >> 1)) break;
            if (a[n - i - 1] != (m >> 1)) break;
            tot++;
        }

        c[q] = 0x7fff;
        for (int i = 1; i <= q; i++) {
            c[q] = min(c[q], min(b[(m >> 1) - i], b[(m >> 1) + i - 1]));

        }

        tot = min(tot, c[q]);
        if (tot == (n >> 1)) tot--;
        ans += tot;
    }


    printf("%d\n", ans);

}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
