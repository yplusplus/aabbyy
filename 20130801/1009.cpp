#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 20;
int maz[N][N];
int f[1 << 16];
int dp[16][1 << 16];
bool visit[16];
int n, m;
int getint(){
    char c = getchar();
    int t = 0;
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        t = t * 10 + c - '0';
        c = getchar();
    }
    return t;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int sister = 0;
        scanf("%d%d", &n, &m);
        memset(maz, -1, sizeof(maz));
        for (int i = 0; i < m; i++) {
            int a, b, c;
            a = getint();
            b = getint();
            c = getint();
            a--, b--;
            if (maz[a][b] == -1) maz[a][b] = c;
            else maz[a][b] = min(maz[a][b], c);
            maz[b][a] = maz[a][b];
        }
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int x;
            x = getint();
            sister |= 1 << (x - 2);
        }
        for (int i = 1; i < n; i++) {
            if (maz[0][i] == -1) continue;
            for (int j = i + 1; j < n; j++) {
                if (maz[0][j] == -1) continue;
                if (maz[i][j] == -1) maz[i][j] = maz[0][i] + maz[0][j];
                else maz[i][j] = min(maz[i][j], maz[0][i] + maz[0][j]);
                maz[j][i] = maz[i][j];
            }
        }
        queue<int> que;
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i < n; i++) {
            dp[i - 1][1 << (i - 1)] = maz[0][i];
        }
        n--;
        int all = 1 << n;
        for (int mask = 0; mask < all; mask++) {
            memset(visit, false, sizeof(visit));
            for (int i = 0; i < n; i++) {
                if (dp[i][mask] != -1) {
                    que.push(i);
                    visit[i] = true;
                }
            }
            while (!que.empty()) {
                int u = que.front(); que.pop();
                visit[u] = false;
                for (int v = 0; v < n; v++) {
                    if (u != v && maz[u + 1][v + 1] != -1) {
                        int tmp = dp[u][mask] + maz[u + 1][v + 1];
                        int nm = mask | (1 << v);
                        if (dp[v][nm] == -1 || dp[v][nm] > tmp) {
                            dp[v][nm] = tmp;
                            if (nm == mask && !visit[v]) {
                                visit[v] = true;
                                que.push(v);
                            }
                        }
                    }
                }
            }
        }
        memset(f, -1, sizeof(f));
        for (int mask = 1; mask < all; mask++) {
            for (int i = 0; i < n; i++) {
                if (dp[i][mask] == -1) continue;
                if (f[mask] == -1) f[mask] = dp[i][mask];
                else f[mask] = min(f[mask], dp[i][mask]);
            }
        }
        int ans = 1 << 25;
        for (int m1 = 0; m1 < all; m1++) {
            if (f[m1] == -1 || f[m1] >= ans) continue;
            int s1 = ~m1 & (all - 1);
            if ((m1 & sister) == sister) ans = min(ans, f[m1]);
            for (int m2 = s1; m2; m2 = (m2 - 1) & s1) {
                if (f[m2] == -1 || f[m2] >= ans) continue;
                if (((m1 | m2) & sister) == sister) ans = min(ans, max(f[m1], f[m2]));
                int s2 = ~m2 & ~m1 & (all -1);
                for (int m3 = s2; m3; m3 = (m3 - 1) & s2) {
                    if (f[m3] == -1 || f[m3] >= ans) continue;
                    if (((m1 | m2 | m3) & sister) == sister) ans = min(ans, max(f[m1], max(f[m2], f[m3])));
                }
            }
        }
        if (ans == 1 << 25) ans = -1;
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}

