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

const int N = 111;
int cnt[N];
int main() {
    int n, m;
    while (cin >> n >> m) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0, a, b; i < m; i++) {
            cin >> a >> b;
            for (int j = a; j <= b; j++) cnt[j]++;
        }
        pii ans = mp(-1, -1);
        for (int i = 1; i <= n; i++) {
            if (cnt[i] != 1) {
                ans = mp(i, cnt[i]);
                break;
            }
        }
        if (ans.fi == -1) puts("OK");
        else cout << ans.fi << " " << ans.se << endl;
    }
    return 0;
}
