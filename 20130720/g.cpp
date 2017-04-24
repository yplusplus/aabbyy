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

const int M = 6;
const int N = 11;
char maz[M][N * N];
int n, m, num;
int dp[N * N][1 << 15];
int pre[N * N][1 << 15];
int mask[N * N];

void update(int a, int b, int c, int d) {
    if (dp[a][b] == -1 || dp[a][b] > d) {
        dp[a][b] = d;
        pre[a][b] = c;
    }
}

int main() {
    while (cin >> n >> m >> num) {
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < n; j++) scanf("%s", &maz[i][j * m]);
            //cout << maz[i] << endl;
        }
        memset(mask, 0, sizeof(mask));
        int all = n * m;
        int tot = 0;
        for (int i = 0; i < num; i++) {
            for (int j = i + 1; j < num; j++) {
                for (int k = 0; k < all; k++) {
                    if (maz[i][k] != maz[j][k]) mask[k + 1] |= (1 << tot);
                }
                tot++;
            }
        }
        memset(dp, -1, sizeof(dp));
        memset(pre, -1, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 0; i < all; i++) {
            for (int j = 0; j < (1 << tot); j++) {
                if (dp[i][j] == -1) continue;
                update(i + 1, j, j, dp[i][j]);
                update(i + 1, j | mask[i + 1], j, dp[i][j] + 1);
            }
        }
        int ans[N * N];
        memset(ans, 0, sizeof(ans));
        int x = (1 << tot) - 1;
        int cnt = 0;
        cout << dp[all][x] << endl;
        for (int i = all; i; i--) {
            int y = pre[i][x];
            if (x != y) ans[i] = 1;
            x = y;
        }
        for (int i = 1; i <= all; i++) {
            putchar('0' + ans[i]);
            if (i % m == 0) puts("");
        }
        
    }
    return 0;
}
