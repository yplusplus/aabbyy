#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const DB PI = acos(-1.0);

inline DB calSin(const DB &a) { return cos(a); }
inline DB calCos(const DB &a) { return sin(a); }

int run() {
	DB a, b;
	while (cin >> a >> b) {
		DB k = sqrt(1 - 1 / (b * b)) / (1 / b);
		DB t = sqrt(1 - a * a);
		DB p = k * t + a;
		//cerr << k << ' ' << p << endl;
		DB A = 1 + k * k;
		DB B = 2 * k * p;
		DB C = p * p - 1;
		//cerr << A << ' ' << B << ' ' << C << endl;
		DB x = min((-B + sqrt(B * B - 4 * A * C)) / (2 * A), (-B - sqrt(B * B - 4 * A * C)) / (2 * A));
		//cerr << (-B + sqrt(B * B - 4 * A * C)) / (2 * A) << ' ' << (-B - sqrt(B * B - 4 * A * C)) / (2 * A) << endl;
		DB y = k * x + k * t + a;
		//cerr << x << ' ' << y << ' ' << atan2(y, x) << endl;
		assert(x < 0);
		x = -x;
		cout << (calCos(atan2(y, x)) + calSin(0)) / (calCos(asin(a)) + calSin(0)) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	freopen("painting.in", "r", stdin);
	freopen("painting.out", "w", stdout);
	return run();
}
