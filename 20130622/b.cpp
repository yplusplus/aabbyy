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

int main() {
    int n, a, b, c;
    while (cin >> n >> a >> b >> c) {
        int ans = 0;
        for (int i = 0; i <= a; i += 2) {
            int tmp = i / 2;
            if (tmp > n) break;
            for (int j = 0; j <= b && tmp + j <= n; j++) {
                int tmp1 = n - tmp - j;
                if (tmp1 % 2 == 0 && tmp1 / 2 <= c) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
