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

int a, b, c;

ll solve(int a, int b, int c, int n, int ai, int bi, int ci) {
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        int tmp = 0;
        if (a) tmp = ai, a--;
        else if (b) tmp = bi, b--;
        else tmp = ci, c--;
        res += ((i - 1) * 2 + 1) * tmp;
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        int n = a + b + c;
        cout << solve(a, b, c, n, 300, 100, 50) << " " << solve(c, b, a, n, 50, 100, 300) << endl;
    }
    return 0;
}
