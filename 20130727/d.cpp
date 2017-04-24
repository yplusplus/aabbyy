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
int cnt[15];
bool check(int x) {
    memset(cnt, 0, sizeof(cnt));
    while (x) {
        cnt[x % 10]++;
        x /= 10;
    }
    for (int i = 0; i < 10; i++) {
        if (cnt[i] > 1) return false;
    }
    return true;
}

int main() {
    int l, r;
    while (cin >> l >> r) {
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += check(i);
        }
        cout << ans << endl;
    }
    return 0;
}
