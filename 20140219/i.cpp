#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-10;
const DB PI = acos(-1.0);
const int T = 333;
DB x[2][3];

bool input() {
	DB sum = 0;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 3; j++) {
		cin >> x[i][j];
		sum += x[i][j];
	}
	return fabs(sum) > EPS;
}

template<class T> inline T sqr(T x) { return x * x; }
template<class T> inline T cub(T x) { return x * x * x; }
DB cal(const DB &a, const DB &b, const DB &c) { return sqrt(sqr(c) / cub(a) * cub(b)); }

DB cal(const DB &p) {
	DB &a = x[1][0], &b = x[1][1], f = sqrt(fabs(sqr(a) - sqr(b)));
	DB y = sqrt(fabs(1 - sqr(p / a))) * b;
	DB yp = sqrt(fabs(sqr(a) - sqr(p)));
	DB area = atan2(yp, p) / 2 * a * b;
	return area - y * sqrt(fabs(sqr(a) - sqr(b))) / 2;
	/*
	DB t = asin(max(min(p / a, 1.0), -1.0));
	return (PI / 4 - (sin(2 * t) / 4 + t / 2)) * a * b - (f - p) * y / 2;
	return - b / a * (p * sqrt(sqr(a) - sqr(p)) / 2 + sqr(a) * asin(p / a) / 2) + PI * a * b / 4 - (f - p) * y / 2;
	*/
}

Point bs(const DB &k) {
	DB &a = x[1][0], &b = x[1][1];
	DB area = PI * a * b * k;
	DB l = -a, r = a, m;
	for (int i = 0; i < T; i++) {
		m = (l + r) / 2;
		if (cal(m) > area) l = m;
		else r = m;
	}
	return Point(l, sqrt(fabs(1 - sqr(l / a))) * b);
}

Point work() {
	DB t = cal(x[0][0], x[1][0], x[0][2]);
	//x[1][2] = x[1][2] - (int) (x[1][2] / t) * t;
	x[1][2] = fmod(x[1][2], t);
	Point ans;
	if (x[1][2] * 2 >= t) {
		ans = bs((t - x[1][2]) / t);
		ans.y = -ans.y;
	} else ans = bs(x[1][2] / t);
	return ans;
}

inline DB fix(const DB &a) { return fabs(a) < 1e-3 ? 0 : a; }

int main() {
	cout << setiosflags(ios::fixed) << setprecision(3);
	int cas = 0;
	while (input()) {
		for (int i = 0; i < 2; i++) if (x[i][0] < x[i][1]) swap(x[i][0], x[i][1]);
		Point ans = work();
		cout << "Solar System " << ++cas << ": " << fix(ans.x) << ' ' << fix(ans.y) << endl;
	}
	return 0;
}
