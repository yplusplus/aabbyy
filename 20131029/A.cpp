#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const int T = 111;
typedef double DB;

DB h, H, L;

DB cal(DB x) {
	DB t = sqrt(h * h + x * x);
	//cout << x << ' ' << t << endl;
	return (H / 2 - t) * x / t;
}

DB dc3(DB l, DB r) {
	DB m1, m2, d;
	for (int i = 0; i < T; i++) {
		d = (r - l) / 3;
		m1 = l + d, m2 = r - d;
		if (cal(m1) > cal(m2)) r = m2;
		else l = m1;
	}
	return (l + r) / 2;
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> h >> H >> L) {
		DB ans = dc3(0, min(L, sqrt(H * H - h * h)));
		cout << cal(ans) << endl;
	}
	return 0;
}
