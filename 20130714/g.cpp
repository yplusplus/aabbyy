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

ll f[N];
ll g[N];
int main() {
    g[0] = 1;
    f[0] = 0, f[1] = 1;
    for (int i = 2; i < N; i++) f[i] = f[i - 1] + f[i - 2];
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        ll gi;
        cin >> a >> gi >> b;
        ll tmp = gi - f[a - 1];
        if (tmp < f[a] || tmp % f[a] > 0) {
            cout << -1 << endl;
            continue;
        }
        g[1] = tmp / f[a];
        for (int i = 2; i <= b; i++) {
            g[i] = g[i - 1] + g[i - 2];
        }
        cout << g[b] << endl;
    }
    return 0;
}
