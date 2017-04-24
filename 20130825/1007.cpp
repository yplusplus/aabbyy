#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 555;
const int M = 5555;
int dp[N][M];
int n, m;

struct Item {
    int p, q, v;
    void read() {
        scanf("%d%d%d", &p, &q, &v);
    }
    bool operator<(const Item &x) const {
        return p - q < x.p - x.q;
    }
} item[N];

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            item[i].read();
        }
        sort(item + 1, item + 1 + n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                if (item[i + 1].q > j || item[i + 1].p > j) continue;
                dp[i + 1][j - item[i + 1].p] = max(dp[i + 1][j - item[i + 1].p], dp[i][j] + item[i + 1].v);
            }
        }
        int ans = 0;
        for (int j = 0; j <= m; j++) {
            ans = max(ans, dp[n][j]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
