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
const double eps = 1e-8;
double w, d, a;
int k;
double q[2][10], p[2][10];
double limit;
double f(double x) {
    double y[2];
    for (int i = 0; i < 2; i++) {
        double a = 0, b = 0;
        for (int j = k; j >= 0; j--) {
            a = a * x + p[i][j];
            b = b * x + q[i][j];
        }
        y[i] = max(a / b, -limit);
    }
    return y[0] - y[1];
}

double simpson(double l, double r) {
    double mid = (l + r) / 2.0;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6.0;
}

double adaptive_simpson(double l, double r) {
    double mid = (l + r) / 2.0;
    double s0 = simpson(l, r);
    double s1 = simpson(l, mid) + simpson(mid, r);
    if (fabs(s0 - s1) < eps) return s0;
    return adaptive_simpson(l, mid) + adaptive_simpson(mid, r);
}

int main() {
    while (~scanf("%lf%lf%lf%d", &w, &d, &a, &k)) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= k; j++) scanf("%lf", &p[i][j]);
            for (int j = 0; j <= k; j++) scanf("%lf", &q[i][j]);
        }
        double l = 0.0;
        for (int i = 0; i < 50; i++) {
            double mid = (l + d) / 2.0;
            limit = mid;
            double area = adaptive_simpson(0, w);
            if (area > a) d = mid;
            else l = mid;
        }
        printf("%.5f\n", (l + d) / 2.0);
    }
    return 0;
}
