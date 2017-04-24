#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

double H, W, X, Y, R;
const double EPS = 1e-9;

double geth(double x) { return H - fabs(x) * H / (W / 2);}
double geta(double x) { return fabs(x) * 2;}

double getarea(double x) {
    double a = geta(x), h = geth(x);
    double d = fabs(X - x);
    if (d >= R) return (a + W) * h / 2;
    else {
        double sum = 0;
        double l = -a / 2, r = a / 2;
        d = sqrt(R * R - d * d);
        double p = Y - d, q = Y + d;
        if (-W / 2 < p && p < l) sum += (p + W / 2) * geth(p) / 2;
        else if (l < p && p < r) sum += (l + W / 2) * h / 2 + (p - l) * h;
        else if (r < p) {
            p = min(W / 2, p);
            sum += (a + W) * h / 2 - (W / 2 - p) * geth(p) / 2;
        }
        if (r < q && q < W / 2) sum += (W / 2 - q) * geth(q) / 2;
        else if (l < q && q < r) sum += (W / 2 - r) * h / 2 + (r - q) * h;
        else if (q < l) {
            q = max(q, -W / 2);
            sum += (a + W) * h / 2 - (q + W / 2) * geth(q) / 2;
        }
        return sum;
    }
    return 0;
}

double simpson(double l, double m, double r) {
    return (getarea(l) + 4 * getarea(m) + getarea(r)) * (r - l) / 6;
}

double simpson(double l, double r) {
    double m = (l + r) / 2;
    double m1 = (l + m) / 2, m2 = (m + r) / 2;
    double s = simpson(l, m, r);
    double s1 = simpson(l, m1, m), s2 = simpson(m, m2, r);
    if (r - l < 0.01 && fabs(s - s1 - s2) < EPS) return s;
    else return simpson(l, m) + simpson(m, r);
}

double work() { 
    //cout << getarea(-1.0) << endl;
    return simpson(-W / 2, W / 2);
}

int main() {
    //freopen("in", "r", stdin);
    cout << setiosflags(ios::fixed) << setprecision(5);
    while (cin >> H >> W >> X >> Y >> R) cout << work() << endl;
    return 0;
}

