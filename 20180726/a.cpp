#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int N = 37;
int pre[N][N][N][N];
long long state[N][N][N][N];
int p[N], a[N], c[N], m[N], g[N];

void update(int &x, long long &y, int xx, long long yy) {
    if (x < xx) {
        x = xx;
        y = yy;
    }
}

void output(int ans, long long state) {
    if (ans == 0) {
        printf("0\n\n");
        return;
    }

    int tot = 0;
    for (int i = 0; i < 36; i++)
        if (state & (1LL << i)) tot++;

    printf("%d\n", tot);
    for (int i = 0; i < 36; i++) {
        if (state & (1LL << i)) {
            printf("%d", i);
            tot--;
            if (tot) printf(" ");
            else printf("\n");
        }
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) scanf("%d%d%d%d%d", &p[i], &a[i], &c[i], &m[i], &g[i]);
        int P, A, C, M;
        scanf("%d%d%d%d", &P, &A, &C, &M);

        for (int i = 0; i <= P; i++)
            for (int j = 0; j <= A; j++)
                for (int k = 0; k <= C; k++)
                    for (int r = 0; r <= M; r++)
                        pre[i][j][k][r] = 0, state[i][j][k][r] = 0;
        int ans = 0;
        long long mask = 0;

        for (int i = 0; i < (1LL << min(n, 18)); i++) {
            int pp = 0, aa = 0, cc = 0, mm = 0, gg = 0;
            for (int j = 0; j < min(n, 18); j++) {
                if (!(i & (1 << j))) continue;
                pp += p[j];
                aa += a[j];
                cc += c[j];
                mm += m[j];
                gg += g[j];
                if (!(pp <= P && aa <= A && cc <= C && mm <= M)) continue;
                if (gg > pre[pp][aa][cc][mm]) {
                    pre[pp][aa][cc][mm] = gg;
                    state[pp][aa][cc][mm] = i;
                }

                if (gg > ans) ans = gg, mask = i;
            }
        }

        if (n <= 16) {
            output(ans, mask);
            continue;
        }

        for (int i = 0; i <= P; i++)
            for (int j = 0; j <= A; j++)
                for (int k = 0; k <= C; k++)
                    for (int r = 0; r <= M; r++) {
                        if (!pre[i][j][k][r]) continue;
                        if (i + 1 <= P) update(pre[i + 1][j][k][r], state[i + 1][j][k][r], pre[i][j][k][r], state[i][j][k][r]);
                        if (j + 1 <= A) update(pre[i][j + 1][k][r], state[i][j + 1][k][r], pre[i][j][k][r], state[i][j][k][r]);
                        if (k + 1 <= C) update(pre[i][j][k + 1][r], state[i][j][k + 1][r], pre[i][j][k][r], state[i][j][k][r]);
                        if (r + 1 <= M) update(pre[i][j][k][r + 1], state[i][j][k][r + 1], pre[i][j][k][r], state[i][j][k][r]);
                    }
        for (int i = 0; i < (1 << (n - 18)); i++) {
            int pp = 0, aa = 0, cc = 0, mm = 0, gg = 0;
            for (int j = 0; j < n - 18; j++) {
                if (!(i & (1 << j))) continue;
                pp += p[j + 18];
                aa += a[j + 18];
                cc += c[j + 18];
                mm += m[j + 18];
                gg += g[j + 18];
                if (!(pp <= P && aa <= A && cc <= C && mm <= M)) continue;

                if (ans < gg + pre[P - pp][A - aa][C - cc][M - mm]) {
                    ans = gg + pre[P - pp][A - aa][C - cc][M - mm];
                    mask = ((1LL * i) << 18) | state[P - pp][A - aa][C - cc][M - mm];
                }
            }
        }

        output(ans, mask);

    }
    return 0;
}
