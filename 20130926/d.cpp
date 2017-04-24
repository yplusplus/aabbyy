#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

double x[3], v[3], a[3];
double dx[2], dvx[2], dvy[2];
const double g = 10.0;

const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}

int main() {
	//freopen("in", "r", stdin);
	int _;
	cout << setiosflags(ios::fixed) << setprecision(4);
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		for (int i = 0; i < 3; i++) cin >> x[i];
		for (int i = 0; i < 3; i++) cin >> v[i];
		for (int i = 0; i < 3; i++) cin >> a[i];
		for (int i = 0; i < 2; i++) dvx[i] = v[i + 1] * cos(a[i + 1]) - v[i] * cos(a[i]);
		for (int i = 0; i < 2; i++) dvy[i] = v[i + 1] * sin(a[i + 1]) - v[i] * sin(a[i]);
		for (int i = 0; i < 2; i++) dx[i] = x[i + 1] - x[i];
		double min_time = 1e100;
		for (int i = 0; i < 3; i++) min_time = min(min_time, v[i] * sin(a[i]) * 2 / g);
		double A = dvy[1] * dx[0] - dvy[0] * dx[1];
		double B = dvy[0] * dvx[1] - dvy[1] * dvx[0];
		cout << "Case #" << cas << ": ";
		if (sgn(B)) {
			double ans = A / B;
			//cout << ans << ' ' << min_time << endl;
			if (sgn(ans) <= 0 || sgn(ans - min_time) >= 0) cout << "-1" << endl;
			else cout << ans << endl;
		} else if (sgn(A) || sgn(min_time) == 0) cout << "-1" << endl;
		else cout << "Multiply answer" << endl;
	}
	return 0;
}




