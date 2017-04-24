#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>
using namespace std;

const int N = 1111;
const int M = 111111;
const int INF = 1 << 29;
int dp[M];
int f[N][N];
int A, B, n;

struct Good {
    int a, b;
    void read() { 
        scanf("%d%d", &a, &b); 
        assert(a > 0 && a < M && b > 0 && b < M);
    }
    bool operator <(const Good &x) const {
        if (b != x.b) return b < x.b;
        return a < x.a;
    }
} good[N];

bool cmp(const Good &a,const Good &b) {
    return a.a < b.a;
}

int main() {
    while (~scanf("%d%d%d", &A, &B, &n)) {
        for (int i = 1; i <= n; i++) {
            good[i].read();
        }
        sort(good + 1, good + n + 1);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                f[i][j] = INF;
            }
        }
        f[n + 1][0] = 0;
        for (int i = n; i >= 1; i--) {
            f[i][0] = 0;
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i + 1][j],f[i + 1][j - 1] + good[i].a);
            }
        }
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = A; j >= good[i].a; j--) {
                if (dp[j] < dp[j - good[i].a] + good[i].b) {
                    dp[j] = dp[j - good[i].a] + good[i].b;
                }
            }
            int p = i + 1;
            int q = 0;
            for (int j = A; j >= 0; j--) {
                int leaveB = B - dp[j];
                while (p <= n && good[p].b <= leaveB) p++;
                while (q <= n && f[p][q] <= A - j) q++;
                while(q > 0 && f[p][q] > A - j) q --;
                if (f[p][q] <= A - j && q > ans) {
                    ans = q;
                }
            }
        }
        sort(good + 1,good + n + 1,cmp);
        int tot = 0,left = A;
        for(int i = 1; i <= n; i ++)
            if(good[i].b > B && left >= good[i].a) tot ++,left -= good[i].a;
        ans = max(ans,tot);
        printf("%d\n", ans);
    }
    return 0;
}
