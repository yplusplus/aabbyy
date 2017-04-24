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

const int N = 444;
int sum[N];
int n, m;
int a[N];
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[n + i] = a[i];
        }
        for (int i = 1; i <= 2 * n; i++) {
            sum[i] = sum[i - 1] + a[i];
        }
        int ans = 0;
        for (int i = 1; i <= 2 * n; i++) {
            if (i >= m) ans = max(ans, sum[i] - sum[i - m]);
        }
        cout << ans << endl;
    }
    return 0;
}
