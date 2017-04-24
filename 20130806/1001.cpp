#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator + (Point a) { return Point(x + a.x, y + a.y);}
    Point operator - (Point a) { return Point(x - a.x, y - a.y);}
    Point operator / (double p) { return Point(x / p, y / p);}
} ;

inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double veclen(Point x) { return dot(x, x);}

const int N = 55;
int nct, nbs;
Point ct[N], bs[N];
int id(Point x) {
    int ret = 0;
    double d = veclen(x - bs[0]), tmp;
    for (int i = 1; i < nbs; i++) {
        tmp = veclen(x - bs[i]);
        if (d > tmp) d = tmp, ret = i;
    }
    return ret;
}

int dc2(Point a, Point b) {
    //cout << id(a) << ' ' << id(b) << ' ' << veclen(a - b)endl;
    if (id(a) == id(b)) return 0;
    if (sgn(veclen(a - b))) {
        Point mid = (a + b) / 2;
        return dc2(a, mid) + dc2(mid, b);
    }
    return 1;
}

int main() {
    //freopen("in", "r", stdin);
    while (~scanf("%d%d", &nct, &nbs)) {
        for (int i = 0; i < nct; i++) scanf("%lf%lf", &ct[i].x, &ct[i].y);
        for (int i = 0; i < nbs; i++) scanf("%lf%lf", &bs[i].x, &bs[i].y);
        int m, x, y;
        scanf("%d", &m);
        while (m--) {
            scanf("%d%d", &x, &y);
            printf("%d\n", dc2(ct[x - 1], ct[y - 1]));
        }
    }
    return 0;
}