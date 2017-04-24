#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int N = 10;
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
struct Point {
    DB x, y, z;
    Point() {}
    Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
    void get() { cin >> x >> y >> z; }
    Point operator + (const Point &a) const { return Point(x + a.x, y + a.y, z + a.z); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y, z - a.z); }
    Point operator * (const DB &p) const { return Point(x * p, y * p, z * p); }
    Point operator / (const DB &p) const { return Point(x / p, y / p, z / p); }
} ;
ostream &operator << (ostream &out, const Point &p) { return out << p.x << ' ' << p.y << ' ' << p.z; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline DB dot(const Point &o, const Point &a, const Point &b) { return dot(a - o, b - o); }
inline Point cross(const Point &a, const Point &b) { return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
inline Point cross(const Point &o, const Point &a, const Point &b) { return cross(a - o, b - o); }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB area(const Point &o, const Point &a, const Point &b) { return veclen(cross(o, a, b)) / 2; }
inline DB volume(const Point &o, const Point &a, const Point &b, const Point &c) { return dot(cross(o, a, b), c - o) / 6.0; }
inline Point vecunit(const Point &a) { return a / veclen(a); }

bool inTri(const Point &p, const Point &a, const Point &b, const Point &c) {
    DB a1 = area(p, a, b);
    DB a2 = area(p, b, c);
    DB a3 = area(p, c, a);
    DB sa = area(a, b, c);
    return sgn(sa - a1 - a2 - a3) == 0;
}

struct Plane {
    Point p, n;
    Plane() {}
    Plane(Point p, Point n) : p(p), n(n) {}
    Plane(Point a, Point b, Point c) { p = a; n = cross(b - a, c - a); }
} ;

inline DB pt2plane(const Point &p, const Point &p0, const Point &n) { return dot(p - p0, n) / veclen(n); }
inline DB pt2plane(const Point &p, const Plane &P) { return pt2plane(p, P.p, P.n); }
inline Point inPlane(const Point &p, const Point &p0, const Point &n) { return p - vecunit(n) * pt2plane(p, p0, n); }
inline Point inPlane(const Point &p, const Plane &P) { return inPlane(p, P.p, P.n); }

const int C = 5;
Point F, pt[C];

bool input() {
    for (int i = 0; i < C; ++i) {
        pt[i].get();
        if (cin.fail()) return 0;
    }
    F.get();
    return 1;
}

DB pt2line(const Point &p, const Point &a, const Point &b) {
    Point v1 = b - a;
    Point v2 = p - a;
    return veclen(cross(v1, v2)) / veclen(v1);
}

bool check(const Point &p, const Point &a, const Point &b) {
    DB dist = fabs(pt2line(p, a, b));
    return sgn(dist - 0.2) >= 0;
}

const int id[6][3] = { { 0, 1, 3 }, { 0, 3, 2 }, { 1, 2, 3 }, { 0, 4, 1 }, { 0, 2, 4 }, { 1, 4, 2 } };
Point getGravity() {
    Point result(0, 0, 0);
    Point O(0, 0, 0);
    DB vol = 0;
    for (int i = 0; i < 6; ++i) {
        DB temp = volume(O, pt[id[i][0]], pt[id[i][1]], pt[id[i][2]]);
        result = result + (pt[id[i][0]] + pt[id[i][1]] + pt[id[i][2]]) / 4 * temp;
        vol += temp;
    }
    return result / vol;
}

bool check(int a, int b, int c) {
    for (int i = 0; i < C; ++i) {
        if (sgn(volume(pt[i], pt[a], pt[b], pt[c])) < 0) return 0;
    }
    return 1;
}

int run() {
    int cas = 0;
    while (input()) {
        DB answerMin = DBL_MAX;
        DB answerMax = DBL_MIN;
        Point gravity = getGravity();
        //cout << "gravity " << gravity << endl;
        for (int i = 0; i < C; ++i) {
            for (int j = 0; j < C; ++j) {
                if (j == i) continue;
                for (int k = 0; k < C; ++k) {
                    if (k == i || k == j) continue;
                    if (check(i, j, k)) {
                        Plane p(pt[i], pt[j], pt[k]);
                        Point ip = inPlane(gravity, p);
                        //cout << i << ' ' << j << ' ' << k << ' ' << ip << endl;
                        if (inTri(ip, pt[i], pt[j], pt[k])) {
                            //cout << "in triangle" << endl;
                            if (check(ip, pt[i], pt[j]) && check(ip, pt[j], pt[k]) && check(ip, pt[k], pt[i])) {
                                //cout << pt2plane(F, p) << endl;
                                answerMax = max(answerMax, fabs(pt2plane(F, p)));
                                answerMin = min(answerMin, fabs(pt2plane(F, p)));
                            }
                        }
                    }
                    for (int l = 0; l < C; ++l) {
                        if (l == i || l == j || l == k) continue;
                        if (sgn(volume(pt[i], pt[j], pt[k], pt[l]))) continue;
                        Plane p(pt[i], pt[j], pt[k]);
                        int t[4] = { i, j, k, l };
                        bool ok = 1;
                        for (int d = 0; d < 4; ++d) {
                            int w = t[d & 3];
                            int x = t[d + 1 & 3];
                            int y = t[d + 2 & 3];
                            int z = t[d + 3 & 3];
                            if (inTri(pt[w], pt[x], pt[y], pt[z])) {
                                Plane p(pt[x], pt[y], pt[z]);
                                Point ip = inPlane(gravity, p);
                                //cout << i << ' ' << j << ' ' << k << ' ' << ip << endl;
                                if (inTri(ip, pt[x], pt[y], pt[z])) {
                                    //cout << "in triangle" << endl;
                                    if (check(ip, pt[x], pt[y]) && check(ip, pt[y], pt[z]) && check(ip, pt[z], pt[x])) {
                                        //cout << pt2plane(F, p) << endl;
                                        answerMax = max(answerMax, fabs(pt2plane(F, p)));
                                        answerMin = min(answerMin, fabs(pt2plane(F, p)));
                                    }
                                }
                                ok = 0;
                                break;
                            }
                        }
                        if (ok) {
                            int ok1 = 0;
                            for (int i = 0; i < 4 && !ok1; ++i) {
                                for (int j = 0; j < 4 && !ok1; ++j) {
                                    if (i == j) continue;
                                    for (int k = 0; k < 4 && !ok1; ++k) {
                                        if (k == i || k == j) continue;
                                        Point &a = pt[t[i]];
                                        Point &b = pt[t[j]];
                                        Point &c = pt[t[k]];
                                        Point ip = inPlane(gravity, Plane(a, b, c));
                                        if (inTri(ip, a, b, c)) {
                                            ok1 = 1;
                                        }
                                    }
                                }
                            }
                            if (ok1) {
                                for (int i = 0; i < 4 && ok; ++i) {
                                    for (int j = 0; j < 4 && ok; ++j) {
                                        if (i == j) continue;
                                        Point &a = pt[t[i]];
                                        Point &b = pt[t[j]];
                                        bool ok2 = 1;
                                        for (int k = 0; k < 4; ++k) {
                                            if (sgn(volume(pt[t[k]], a, b, gravity)) < 0) {
                                                ok2 = 0;
                                                break;
                                            }
                                        }
                                        if (ok2) {
                                            Point ip = inPlane(gravity, p);
                                            if (!check(ip, a, b)) {
                                                ok = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (ok) {
                            answerMax = max(answerMax, fabs(pt2plane(F, p)));
                            answerMin = min(answerMin, fabs(pt2plane(F, p)));
                        }
                    }
                }
            }
        }
        cout << "Case " << ++cas << ": " << answerMin << ' ' << answerMax << endl;
    }
    return 0;
}

int main() {
    //freopen("in_k", "r", stdin);
    cout << setiosflags(ios::fixed) << setprecision(5);
    ios::sync_with_stdio(0);
    return run();
}
