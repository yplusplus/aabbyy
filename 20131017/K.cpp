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

int low_digit[22], high_digit[22];
bool visit[22][222][1111];

struct Node {
    ll cnt, rem;
    Node() { cnt = rem = 0; }
    Node(int cnt, int rem) : cnt(cnt), rem(rem) {}
    Node operator + (const Node &x) {
        Node res;
        res.cnt = cnt + x.cnt;
        res.rem = x.rem;
        return res;
    }
} dp[22][222][1111];

int get_digit(ll x, int digit[]) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return tot - 1;
}

int k;
Node dfs(int i, int sum, int rem, bool le, bool he) {
    if (i == -1) {
        if (sum + rem >= k) return Node(1, 0);
        return Node(0, sum + rem);
    }
    if (!le && !he && visit[i][sum][rem]) return dp[i][sum][rem];
    int u = he ? high_digit[i] : 9;
    int d = le ? low_digit[i] : 0;
    Node res(0, rem);
    for (int j = d; j <= u; j++) {
        res = res + dfs(i - 1, sum + j, res.rem, le & j == d, he & j == u);
    }
    if (!le && !he) {
        visit[i][sum][rem] = true;
        dp[i][sum][rem] = res;
    }
    return res;
} 

ll l, r;
int main() {
    memset(visit, false, sizeof(visit));
    while (cin >> l >> r >> k) {
        memset(low_digit, 0, sizeof(low_digit));
        memset(high_digit, 0, sizeof(high_digit));
        get_digit(l, low_digit);
        int tot = get_digit(r, high_digit);
        cout << dfs(tot, 0, 0, 1, 1).cnt << endl;
    }
    return 0;
}
