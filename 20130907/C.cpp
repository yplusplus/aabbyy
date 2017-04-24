#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1.0);
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
template <class T> T sqr(T x) { return x * x;}
typedef pair<double, double> Point;
#define x first
#define y second
typedef pair<Point, int> Node;
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}

double cosx, sinx;
inline Point rotate(Point a) { return Point(a.x * cosx - a.y * sinx, a.x * sinx + a.y * cosx);}
inline Point rotate(Point a, double p) { return Point(a.x * cos(p) - a.y * sin(p), a.x * sin(p) + a.y * cos(p));}
inline bool cmpx(Node a, Node b) { return sgn(a.x.x - b.x.x) < 0 || sgn(a.x.x - b.x.x) == 0 && a.x.y < b.x.y;}
inline bool cmpy(Node a, Node b) { return sgn(a.x.y - b.x.y) < 0 || sgn(a.x.y - b.x.y) == 0 && a.x.x < b.x.x;}
inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double veclen(Point a) { return sqrt(dot(a, a));}
inline double dist(Point a, Point b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));}
inline double angle(Point a) { return atan2(a.y, a.x);}
inline double angle(Point a, Point b) { return angle(b - a);}
inline double fix(double x) { return x < 0 ? x + PI : x;}

const int N = 111111;
Node isl[N];
int X[N], Y[N];

int main() {
    //freopen("in", "r", stdin);
    ios::sync_with_stdio(0);
    cout << setiosflags(ios::fixed) << setprecision(10);
    int n, kx, ky;
    while (cin >> n >> kx >> ky) {
        double len = veclen(Point(kx, ky));
        cosx = ky / len, sinx = kx / len;
        for (int i = 0; i < n; i++) {
            cin >> X[i] >> Y[i];
            Point tmp = rotate(Point(X[i], Y[i]));
            isl[i] = Node(tmp, i + 1);
        }
        if (kx == 0 && ky == 0) {
            cout << "1 2" << endl;
            continue;
        }
        sort(isl, isl + n);
        double mx = 0;
        int ansx, ansy;
        for (int i = 1; i < n; i++) {
            double ang = angle(isl[i - 1].x, isl[i].x);
            if (min(fix(mx), PI - fix(mx)) < min(fix(ang), PI - fix(ang))) {
                mx = ang, ansx = isl[i - 1].y, ansy = isl[i].y;
                if (ang < 0) swap(ansx, ansy);
            }
        }
        for (int i = 0; i < n; i++) isl[i].x = rotate(isl[i].x, -fabs(mx));
        sort(isl, isl + n, cmpy);
        int l, r;
        l = r = 0;
        while (l < n) {
            int a = isl[r++].y, b = N, m = N;
            while (r < n && sgn(isl[l].x.y - isl[r].x.y) == 0) {
                if (m < a) a = m, b = isl[r].y;
                else b = min(b, isl[r].y);
                m = min(m, isl[r].y);
                r++;
            }
            l = r;
            if (b == N) continue;
            if (ansx > a) ansx = a, ansy = b;
            else if (ansx == a) ansy = min(ansy, b);
        }
        cout << ansx << ' ' << ansy << endl;
    }
    return 0;
}