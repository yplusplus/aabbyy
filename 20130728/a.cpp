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

int digit[20];

bool check(ll x, int cnt) {
    vector<int> vec;
    for (int i = 0; i < cnt; i++) vec.pb(-1);
    while (x) {
        vec.pb(x % 10);
        x /= 10;
    }
    int l = 0, r = vec.size() - 1;
    while (l < r) {
        if (vec[l] == vec[r]) return false;
        l++, r--;
    }
    return true;
}

ll dfs(int i, int cnt, ll x, bool e) {
    if (i == -1) {
        return (ll)check(x, 0);
    }
    if (!e) {
        int t = cnt + i + 1;
        int m = t / 2;
        if (cnt == 0) {
            ll res = 0;
            for (int k = 1; k <= t; k++) {
                int mm = k / 2;
                ll tmp = 1;
                for (int j = 0; j <= mm; j++) tmp *= 9;
                for (int j = 0; j < k - mm - 1; j++) tmp *= 10;
                res += tmp;
            }
            return res + 1;
        }
        if (i + 1 < m) {
            if (!check(x, i + 1)) return 0;
            ll res = 1;
            for (int j = 0; j < i + 1; j++) res *= 9;
            return res;
        } else {
            ll res = 1;
            for (int j = 0; j < m; j++) res *= 9;
            for (int j = 0; j < (i + 1) - m; j++) res *= 10;
            return res;
        }
    } else {
        ll res = 0;
        for (int d = 0; d <= digit[i]; d++) {
            res += dfs(i - 1, cnt + (d || cnt), x * 10 + d, e && d == digit[i]);
        }
        return res;
    }
}

ll calc(ll x) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 0, 1);
}

int main() {
    ll l, r;
    while (cin >> l >> r) {
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}
