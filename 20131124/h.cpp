#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB PI = acos(-1.0);

int main() {
	DB R, r, H, S;
	int F;
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> R >> r >> H >> F >> S) {
		DB ans = 0;
		for (int i = 0; i < F; i++) {
			DB cr = (R - r) * i / F + r;
			int n = floor(PI / atan(S * F / (2 * cr * H)));
			ans += 2 * H * cr * n * tan(PI / n) / F;
		}
		cout << ans << endl;
	}
	return 0;
}
