#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline bool check(int *a) { return a[0] + a[2] == a[1] + a[3]; }
int cnt(int *a) {
	int c = 0;
	for (int i = 0; i < 4; i++) if (a[i]) c++;
	return c;
}

int mk;
int get(int *a) {
	mk = -1;
	for (int i = 0; i < 4; i++) if (a[i] == 0) mk = i;
	return a[mk + 1 & 3] + a[mk - 1 & 3] - a[mk ^ 2];
}

int main() {
	int _;
	cout << setiosflags(ios::fixed) << setprecision(5);
	cin >> _;
	int w, a[4];
	while (_--) {
		cin >> w;
		for (int i = 0; i < 4; i++) cin >> a[i];
		int c = cnt(a);
		if (c == 0) cout << 0 << endl;
		else if (c == 1) cout << "ambiguous" << endl;
		else if (c == 2) {
			if (a[0] && a[2] || a[1] && a[3]) cout << "error" << endl;
			else cout << "ambiguous" << endl;
		} else if (c == 3) {
			int low = get(a);
			if (low > 0) cout << "error" << endl;
			else {
				int l = a[mk - 1 & 3], r = a[mk + 1 & 3];
				double a1 = w * 1.0 * low / (l - low);
				double a2 = w * 1.0 * low / (r - low);
				double s = 0;
				for (int i = 0; i < 4; i++) s += a[i];
				s += low;
				s *= (double) w * w / 4, s -= a1 * a2 * low / 6;
				cout << s << endl;
			}
		} else {
			if (check(a)) cout << (double) (a[0] + a[1] + a[2] + a[3]) * w * w / 4 << endl;
			else cout << "error" << endl;
		}
	}
	return 0;
}




