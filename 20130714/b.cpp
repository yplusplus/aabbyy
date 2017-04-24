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
const ll MOD = 1000000007LL;
char line[3][N * 2];
int n;
int digit[10] = {430, 384, 188, 440, 402, 314, 318, 392, 446, 442};
int a[N];
ll dp[N][10];

ll add(ll &a, ll b) {
    a = (a + b) % MOD;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        getchar();
        for (int i = 0; i < 3; i++) gets(line[i]);
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++) {
            int col = i * 2 - 2;
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (line[k][col + j] == '_' || line[k][col + j] == '|') a[i] |= (1 << (j * 3 + k));
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < 10; i++) {
            if ((digit[i] & 63) == (a[1] & 63)) {
                if ((digit[i] | a[1]) == a[1]) dp[1][i] = 1;
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                if (!dp[i][j]) continue;
                for (int k = 0; k < 10; k++) {
                    if ((digit[k] & 56) == (a[i + 1] & 56)) {
                        int b = (digit[k] | a[i + 1]) & 448;
                        int c = a[i + 1] & 448;
                        if (b == c) {
                            int tmp = ((digit[j] >> 6) | digit[k]) & 7;
                            if (tmp == (a[i + 1] & 7)) {
                                add(dp[i + 1][k], dp[i][j]);
                            }
                        }
                    }
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i < 10; i++) {
            if ((digit[i] & 448) == (a[n] & 448)) add(ans, dp[n][i]);
        }
        cout << ans << endl;
    }
    return 0;
}
