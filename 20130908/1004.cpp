#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double area(Point a, Point b, Point c) { return fabs(cross(c - a, b - a)) / 2;}

const int N = 111;
const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
Point pt[N];
int main() {
    ios::sync_with_stdio(0);
    int n, T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> pt[i].x >> pt[i].y;
        double mn = 1e100;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (sgn(area(pt[i], pt[j], pt[k]))) mn = min(mn, area(pt[i], pt[j], pt[k]));
                }
            }
        }
        if (mn > 1e99) puts("Impossible");
        else printf("%.2f\n", mn);
    }
    return 0;
}
