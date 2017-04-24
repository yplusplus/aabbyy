#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

typedef pair<int, int> Point;
const int N = 33;
const double eps = 1e-6;
int x[N], y[N];
int n;

double sq(double x) { return x * x; }
bool between(double a, double b, double c) { return (a > c) ^ (b > c); }

bool is_valid(double cx, double cy, double r) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] > cx && between(y[i], y[i + 1], cy)) cnt++;
    }
    if (cnt % 2 == 0) return false;
    for (int i = 0; i < n; i++) {
        if (r * r > sq(cx - x[i]) + sq(cy - y[i]) + eps) return false; 
        if (x[i] == x[i + 1] && between(y[i], y[i + 1], cy) && r > fabs(cx - x[i]) + eps) return false;
        if (y[i] == y[i + 1] && between(x[i], x[i + 1], cx) && r > fabs(cy - y[i]) + eps) return false;
    }
    return true;
}

bool check(double r) {
    //PP
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double mx = (x[i] + x[j]) / 2.0;
            double my = (y[i] + y[j]) / 2.0;
            double t = sqrt(sq(x[i] - mx) + sq(y[i] - my));
            if (t < r) {
                double tt = sqrt(sq(r) - sq(t));
                double dx = (my - y[i]) / t * tt;
                double dy = (x[i] - mx) / t * tt;
                if (is_valid(mx + dx, my + dy, r)) return true;
                if (is_valid(mx - dx, my - dy, r)) return true;
            }
        }
    }
    //PH
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (y[i] == y[i + 1]) {
                double cy, t;
                cy = y[i] + r;
                t = fabs(cy - y[j]);
                if (t < r) {
                    double tt = sqrt(sq(r) - sq(t));
                    if (is_valid(x[j] + tt, cy, r)) return true;
                    if (is_valid(x[j] - tt, cy, r)) return true;
                }
                cy = y[i] - r;
                t = fabs(cy - y[j]);
                if (t < r) {
                    double tt = sqrt(sq(r) - sq(t));
                    if (is_valid(x[j] + tt, cy, r)) return true;
                    if (is_valid(x[j] - tt, cy, r)) return true;
                }
            }
        }
    }
    //PV
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (x[i] == x[i + 1]) {
                double cx, t;
                cx = x[i] + r;
                t = fabs(cx - x[j]);
                if (t < r) {
                    double tt = sqrt(sq(r) - sq(t));
                    if (is_valid(cx, y[j] + tt, r)) return true;
                    if (is_valid(cx, y[j] - tt, r)) return true;
                }
                cx = x[i] - r;
                t = fabs(cx - x[j]);
                if (t < r) {
                    double tt = sqrt(sq(r) - sq(t));
                    if (is_valid(cx, y[j] + tt, r)) return true;
                    if (is_valid(cx, y[j] - tt, r)) return true;
                }
            }
        }
    }
    //HV
    for (int i = 0; i < n; i++) {
        if (x[i] == x[i + 1]) {
            for (int j = 0; j < n; j++) {
                if (y[j] == y[j + 1]) {
                    if (is_valid(x[i] + r, y[j] + r, r)) return true;
                    if (is_valid(x[i] + r, y[j] - r, r)) return true;
                    if (is_valid(x[i] - r, y[j] + r, r)) return true;
                    if (is_valid(x[i] - r, y[j] - r, r)) return true;
                }
            }
        }
    }
    return false;
}

void solve(int Case) {
    double l = 0, r = 1e4;
    for (int i = 0; i < 50; i++) {
        double mid = (l + r) / 2.0;
        if (check(mid)) l = mid;
        else r = mid;
    }
    printf("Case Number %d radius is: %.2f\n", Case, (l + r) / 2.0);
}

int main() {
    int Case = 0;
    while (~scanf("%d", &n), n) {
        if (Case) puts("");
        int nowx = 0, nowy = 0;
        x[0] = y[0] = 0;
        for (int i = 1; i <= n; i++) {
            int len;
            char dir[5];
            scanf("%d%s", &len, dir);
            switch (dir[0]) {
                case 'R': nowx += len; break;
                case 'L': nowx -= len; break;
                case 'U': nowy += len; break;
                case 'D': nowy -= len; break;
            }
            x[i] = nowx, y[i] = nowy;
        }
        solve(++Case);
    }
    return 0;
}
