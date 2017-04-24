#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 15;

struct Poly {
    double c[N];
    Poly() { memset(c, 0, sizeof(c)); }
    void clear() { memset(c, 0, sizeof(c)); }
    double valueOf(double x) {
        double res = 0;
        for (int i = N - 1; i >= 0; i--) {
            res = res * x + c[i];
        }
        return res;
    }
    Poly operator*(const Poly &x) {
        Poly res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                res.c[i] += c[j] * x.c[i - j];
            }
        }
        return res;
    }
    double integral(double l, double r) {
        Poly t;
        for (int i = N - 1; i > 0; i--) {
            t.c[i] = c[i - 1] / i;
        }
        return t.valueOf(r) - t.valueOf(l);
    }
};

int main() {
    int Case = 1, n;
    while (~scanf("%d", &n), n) {
        Poly p, q;
        for (int i = n; i >= 0; i--) {
            scanf("%lf", &p.c[i]);
        }
        double c;
        scanf("%lf", &c);
        q.c[1] = 1; q.c[0] = -c;
        double A = p.integral(-1, c), B = q.integral(-1, c), C = (p * q).integral(-1, c), D = (q * q).integral(-1, c),
               E = p.integral(c, 1), F = q.integral(c, 1), G = (p * q).integral(c, 1), H = (q * q).integral(c, 1);
        double y = 2 * (A + E - B * C / D - F * G / H);
        double a1 = (C - B * y) / D, a0 = y - a1 * c;
        double b1 = (G - F * y) / H, b0 = y - b1 * c;
        printf("Case %d: %.3f %.3f %.3f %.3f\n", Case++, a1, a0, b1, b0);
    }
    return 0;
}
