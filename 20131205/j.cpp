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

int main() {
    ll a, b, c;
    while (cin >> a >> b >> c) {
        ll sum = 0, cnt = 0;
        cnt += a >= 2 ? 2 : a;
        cnt += b >= 2 ? 2 : b;
        cnt += c >= 2 ? 2 : c;
        sum += min(a, 2LL);
        sum += min(b, 2LL);
        sum += min(c, 2LL);
        ll ans = 0;
        if (a > 2) ans += (a - 2) * cnt;
        if (b > 2) ans += (b - 2) * cnt;
        if (c > 2) ans += (c - 2) * cnt;
        for (int i = 2; i <= sum; i++) ans += i - 1;
        cout << ans << endl;
    }
    return 0;
}
