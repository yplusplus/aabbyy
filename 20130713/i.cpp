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
//double l, h, H;
//double v, x, a;
ll l, h, H, v, x, a;
int main() {
    while (cin >> l >> h >> H >> v >> x >> a) {
        //double t1 = (H - h) * 1.0 / x;
        //double s1 = v * t1;
        //double t2 = v / a;
        //double s2 = v * t2 - 0.5 * a * t2 * t2 + l;
        ll s1 = 2LL * a * v * (H - h);
        ll s2 = (v * v + 2 * a * l) * x;
        if (s2 >= s1) puts("Crash");
        else puts("Safe");
    }
    return 0;
}


