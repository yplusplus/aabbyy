#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
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

struct Line {
    Point s, t;
    Line() {}
    Line(Point s, Point t) : s(s), t(t) {}
    Point vec() { return t - s;}
    Point point(double p) { return s + vec() * p;}
} ;
inline Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}

struct Circle {
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r) : c(c), r(r) {}
    bool in(Point a) { return sgn(r - veclen(a - c)) >= 0;}
} ;
Point pt[4];

Circle getcir(Point a, Point b, Point c) {
    if (sgn(dot(b - a, c - a)) < 0) return Circle(Point((b + c) / 2), veclen(c - b) / 2);
    if (sgn(dot(a - b, c - b)) < 0) return Circle(Point((a + c) / 2), veclen(c - a) / 2);
    if (sgn(dot(b - c, a - c)) < 0) return Circle(Point((b + a) / 2), veclen(a - b) / 2);
    Line l1 = Line((a + b) / 2, Point(a + b) / 2 + normal(b - a));
    Line l2 = Line((a + c) / 2, Point(a + c) / 2 + normal(c - a));
    Point ip = llint(l1, l2);
    return Circle(ip, veclen(ip - a));
}

int main() {
    int T;
    cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        for (int i = 0; i < 4; i++) scan(pt[i]);
        Circle c = getcir(pt[0], pt[1], pt[2]);
        if (c.in(pt[3])) cout << "Case #" << cas << ": Danger" << endl;
        else cout << "Case #" << cas << ": Safe" << endl;
    }
    return 0;
}

