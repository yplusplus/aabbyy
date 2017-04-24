#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
template<class T> T sqr(T x) { return x * x;}
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double veclen(Point a) { return sqrt(dot(a, a));}
inline void scan(Point &a) { cin >> a.x >> a.y;}
inline Point normal(Point a) { return Point(-a.y, a.x) / veclen(a);}

const int N = 333;
const int M = N * N;
Point p[N], v[N];
double A[M], B[M], C[M];
int tt;

double cal(double x) {
    double mn = 0;
    for (int i = 0; i < tt; i++) mn = max(mn, A[i] * sqr(x) + B[i] * x + C[i]);
    return sqrt(mn);
}

double dc3(double l, double r) {
    double m1, m2;
    for (int i = 0; i < 222; i++) {
        double d = (r - l) / 3;
        m1 = l + d, m2 = r - d;
        if (cal(m1) < cal(m2)) r = m2;
        else l = m1;
    }
    return (l + r) / 2;
}

int main() {
    //freopen("in", "r", stdin);
    int T, n;
    ios::sync_with_stdio(0);
    cout << setiosflags(ios::fixed) << setprecision(2);
    cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        cin >> n;
        for (int i = 0; i < n; i++) scan(p[i]), scan(v[i]);
        tt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Point d = v[j] - v[i], e = p[j] - p[i];
                A[tt] = sqr(d.x) + sqr(d.y);
                B[tt] = (e.x * d.x + e.y * d.y) * 2;
                C[tt] = sqr(e.x) + sqr(e.y);
                tt++;
            }
        }
        double ans = dc3(0, 1e20);
        cout << "Case #" << cas << ": " << ans << ' ' << cal(ans) << endl;
    }
    return 0;
}


