#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int N, M;
const long double EPS = 1e-10;
const long double PART = 1e-2;
const long double PI = acos(-1.0);
long double A, B, o, a, b;

inline long double gety(long double x) {
	long double ret = b * (sqrt(1.0 - x * x) * cos(B) - x * sin(B)) - sqrt(1.0 - x * x);
	long double C = PI - 2 * A;
	ret = min(ret, min((cos(C) - x) / cos(C) * sin(C), (sin(C) - x) / sin(C) * cos(C)));
	return ret;
}
inline long double simpson(long double l, long double m, long double r) { return (gety(l) + gety(m) * 4.0 + gety(r)) * (r - l) / 6.0;}
inline long double simpson(long double l, long double r) {
	long double m = (l + r) / 2.0;
	long double m1 = (l + m) / 2.0, m2 = (m + r) / 2.0;
	long double s = simpson(l, m, r);
	long double s1 = simpson(l, m1, m), s2 = simpson(m, m2, r);
	if (r - l < PART && fabs(s - s1 - s2) < EPS) return s;
	return simpson(l, m) + simpson(m, r);
}

long double work() {
	if (N <= 4) return 0;
	A = PI * (N - 2.0) / (2.0 * N);
	B = PI / 2.0 - A;
	b = 2.0 * sin(A);
	long double L = 0, R = sin(A - B);
	return simpson(L, R) * 4.0;
}

long double ans[10];

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(6);
	for (N = 0, M = 1; N < 9; N++) ans[N] = work();
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> N >> M;
		cout << "Case #" << cas << ": " << (double) (ans[N] * M * M) << endl;
	}
	return 0;
}

