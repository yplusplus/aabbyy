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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

int n, m, C, D;
const int N = 111;
const int M = 12;
const int MOD = 1000000007;
int dp[2][1 << 10][21];
int row[N];
char maz[N][M];
vector<int> vec[1 << 10][21];
vector<int> legal[N];

void dfs(int i, int mask, int pre, int nxt, int ones) {
    if (ones > D) return;
    if (i == m) {
        vec[mask][ones].push_back(nxt);
        return;
    }
    if (pre >> i & 1) dfs(i + 1, mask, pre, nxt, ones);
    else {
        dfs(i + 1, mask, pre | (1 << i), nxt, ones + 1);
        if (i + 1 < m && (~pre >> (i + 1) & 1)) dfs(i + 1, mask, pre | (1 << i) | (1 << (i + 1)), nxt, ones);
        if (~nxt >> i & 1) dfs(i + 1, mask, pre | (1 << i), nxt | (1 << i), ones);
    }
}

int main() {
    while (~scanf("%d%d%d%d", &n, &m, &C, &D)) {
        for (int i = 1; i <= n; i++) {
            scanf("%s", maz[i]);
            row[i] = 0;
            for (int j = 0; j < m; j++) {
                if (maz[i][j] == '0') row[i] |= 1 << j;
            }
        }
        row[n + 1] = 0;
        memset(dp, 0, sizeof(dp));
        dp[1][row[1]][0] = 1;
        for (int i = 1; i <= n; i++) {
            memset(dp[(i + 1) & 1], 0, sizeof(dp[(i + 1) & 1]));
            legal[i].clear();
            for (int j = 0; j < (1 << m); j++) {
                if ((j & row[i]) != row[i]) continue;
                for (int k = 0; k <= D; k++) vec[j][k].clear();
                legal[i].push_back(j);
                dfs(0, j, j, row[i + 1], 0);
            }
            for (int j = 0; j < legal[i].size(); j++) {
                for (int k = 0; k <= D; k++) {
                    if (dp[i & 1][legal[i][j]][k] == 0) continue;
                    for (int l = 0; l + k <= D; l++) {
                        for (int c = 0; c < vec[legal[i][j]][l].size(); c++) {
                            int nxt = vec[legal[i][j]][l][c];
                            dp[(i + 1) & 1][nxt][l + k] = (dp[(i + 1) & 1][nxt][l + k] + dp[i & 1][legal[i][j]][k]) % MOD;
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = C; i <= D; i++) {
            ans = (ans + dp[(n + 1) & 1][0][i]) % MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}
