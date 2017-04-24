#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-6;
const double g = 9.8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
template<class T> T sqr(T x) { return x * x;}

double A, B, C;
inline double F(double x) { return A * sqr(x) + B * x + C;}
inline double f(double x) { return sqrt(1 + sqr(2 * A * x + B));}
double cal(double l, double r) {
	double m = (l + r) / 2;
	return (r - l) / 6 * (f(l) + f(m) * 4 + f(r));
}

double simpson(double l, double r) {
	double m = (l + r) / 2;
	if (sgn(cal(l, r) - cal(l, m) - cal(m, r))) return simpson(l, m) + simpson(m, r);
	return cal(l, r);
}

double work(double dx, double dy, double t) {
	if (sgn(t) <= 0) return -1;
	double vx = dx / t;
	double vy = dy / t + g * t / 2;
	B = vy / vx, A = - g / (2 * sqr(vx)), C = 0;;
	return simpson(0, t * vx);
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(3);
	int T;
	double ax, ay, bx, by, t;
	cin >> T;
	while (T-- && cin >> ax >> ay >> bx >> by >> t) {
		double ans;
		if (ax > bx) { ans = work(ax - bx, ay - by, t);
		} else ans = work(bx - ax, by - ay, t);
			if (ans < 0) cout << "Impossible." << endl;
			else cout << ans << endl;
	}
	return 0;
}