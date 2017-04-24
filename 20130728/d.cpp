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

const int N = 11111;
const int K = 55;
int n, k;
char col[N];
int dp[N][K], pre[N][K];

void update(int a, int b, int c, int w) {
    if (dp[a][b] > w) {
        dp[a][b] = w;
        pre[a][b] = c;
    }
}

int main() {
    while (cin >> n >> k) {
        scanf("%s", col);
        col[n] = '0';
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = inf;
                pre[i][j] = -1;
            }
        }
        dp[0][0] = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (dp[i][j] == inf) continue;
                for (int l = 0; l <= k - j; l++) {
                    int t = (i + j) % 10;
                    int cnt = 0;
                    if (l >= 10 - t) {
                        cnt = 1 + (l + t - 10) / 10;
                    }
                    update(i + 1, j + l, j, dp[i][j] + (col[i] == '1' && (t + l + 1) % 10 == 0) + cnt);
                }
            }
        }
        int x = -1;
        int ans = inf;
        for (int i = 0; i <= k; i++) {
            if (ans > dp[n + 1][i]) {
                ans = dp[n + 1][x = i];
            }
        }
        cout << ans << endl;
        vector<int> pos;
        for (int i = n + 1; i; i--) {
            if (pre[i][x] != x) {
                int cnt = x - pre[i][x];
                int t = i - 1 + pre[i][x];
                for (int j = 1; j <= cnt; j++) {
                    pos.pb(t + j);
                }
            }
            x = pre[i][x];
        }
        sort(pos.begin(), pos.end());
        cout << pos.size();
        for (int i = 0; i < pos.size(); i++) {
            cout << " " << pos[i];
        }
        cout << endl;
    }
    return 0;
}
