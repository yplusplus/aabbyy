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

const int N = 30;
int a[N], b[N];
int suma[N], sumb[N];
int dp[N][N][N][N];
int n;
int dfs(int l1, int r1, int l2, int r2) {
    if (l1 > r1 && l2 > r2) return 0;
    int &res = dp[l1][r1][l2][r2];
    if (res > 0) return res;
    int sum = suma[r1] - suma[l1 - 1] + sumb[r2] - sumb[l2 - 1];
    if (l1 <= r1) {
        res = max(res, sum - dfs(l1 + 1, r1, l2, r2));
        res = max(res, sum - dfs(l1, r1 - 1, l2, r2));
    }
    if (l2 <= r2) {
        res = max(res, sum - dfs(l1, r1, l2 + 1, r2));
        res = max(res, sum - dfs(l1, r1, l2, r2 - 1));
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        suma[0] = sumb[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            suma[i] = a[i] + suma[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            sumb[i] = b[i] + sumb[i - 1];
        }
        memset(dp, 0, sizeof(dp));
        cout << dfs(1, n, 1, n) << endl;
    }
    return 0;
}
