#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const int month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int INF = 0x77777777;
bool isleap(int y) { return y % 4 == 0 && y % 100 != 0 || y % 400 == 0; }

char str[111];

int cal(char *s) {
	int y, m, d;
	sscanf(s, "%d.%d.%d", &d, &m, &y);
	int cy = 1800, cm = 1, sum = 0;
	while (cy < y) {
		sum += 365;
		sum += isleap(cy);
		cy++;
	}
	while (cm < m) {
		sum += month[cm];
		if (isleap(cy) && cm == 2) sum++;
		cm++;
	}
	return sum + d - 1;
}

int main() {
	int n;
	while (cin >> n) {
		int id = 1, mx = -INF, tm = INF;
		for (int i = 1; i <= n; i++) {
			cin >> str;
			int t1 = cal(str);
			cin >> str;
			cin >> str;
			int t2 = cal(str);
			//cout << t1 << ' ' << t2 << ' ' << t2 - t1 << endl;
			if (mx < t2 - t1) {
				tm = t1;
				mx = t2 - t1;
				id = i;
			} else if (mx == t2 - t1 && t1 < tm) {
				tm = t1;
				id = i;
			}
		}
		cout << id << endl;
	}
	return 0;
}