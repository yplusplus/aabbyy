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

const int N = 5555;
int n;
struct Point {
    int x, y, z;
    void read() {
        cin >> x >> y >> z;
    }
} p[N];

double getDist(const Point &a, const Point &b) {
    return sqrt((1.0 * a.x - b.x) * (a.x - b.x)
            + (1.0 * a.y - b.y) * (a.y - b.y)
            + (1.0 * a.z - b.z) * (a.z - b.z));
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) p[i].read();
        double ans = dinf;
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double tmp = getDist(p[0], p[i]) + getDist(p[0], p[j]) + getDist(p[i], p[j]);
                ans = min(ans, tmp / 2.0);
            }
        }
        printf("%.10f\n", ans);
    }
    return 0;
}
