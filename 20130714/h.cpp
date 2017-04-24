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
const int N = 55;
const int M = 1111;
pii problem[N];

struct Node {
    int atr, solve, penality;
    bool operator<(const Node &x) {
        if (atr != x.atr) return atr < x.atr;
        if (solve != x.solve) return solve < x.solve;
        return penality > x.penality;
    }
} dp[N][M];

int t, n;
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> t >> n;
        for (int i = 1; i <= n; i++) cin >> problem[i].fi;
        for (int i = 1; i <= n; i++) cin >> problem[i].se;
        sort(problem + 1, problem + n + 1);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= t; j++) {
                if (dp[i + 1][j] < dp[i][j]) dp[i + 1][j] = dp[i][j];
                int tmp = problem[i + 1].fi + j;
                if (tmp <= t) {
                    Node a = dp[i][j];
                    a.solve++, a.penality += tmp, a.atr += problem[i + 1].se;
                    if (dp[i + 1][tmp] < a) dp[i + 1][tmp] = a;
                }
            }
        }
        Node ans;
        memset(&ans, 0, sizeof(ans));
        for (int i = 0; i <= t; i++) {
            if (ans < dp[n][i]) ans = dp[n][i];
        }
        cout << ans.atr << " " << ans.solve << " " << ans.penality << endl;
    }
    return 0;
}
