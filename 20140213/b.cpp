#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const unsigned N = 3;
ULL rem[N];

int test(ULL x, ULL y, ULL z, bool op) {
	if (x == 0 && y == 0 && z) return -1;
	int r, cur = 1;
	if (op) {
		if (x == 0) return -1;
		r = 1, x--;
	} else {
		if (y == 0) return -1;
		r = 2, y--;
	}
	cur ^= z & 1;
	if (x > y) x -= y, y = 0;
	else y -= x, x = 0;
	while (x || y) {
		if (y) y--, r++;
		else x--;
		r++, r %= 3;
		if (r == 0) return (cur << 1) - 1;
		cur ^= 1;
	}
	return 0;
}

string work() {
	if (rem[1] == 0 && rem[2] == 0) return rem[0] ? "J" : "Draw";
	int ans = max(test(rem[1], rem[2], rem[0], 1), test(rem[1], rem[2], rem[0], 0));
	//cout << test1(rem[1], rem[2], rem[0]) << ' ' << test2(rem[1], rem[2], rem[0]) << endl;
	if (ans == 1) return "M";
	if (ans == 0) return "Draw";
	return "J";
}

int main() {
	//cout << ULLONG_MAX << endl;
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int _, n;
	ULL x, y;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> n;
		memset(rem, 0, sizeof rem);
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			int r = y % N;
			x--, y--;
			if (r == 2) {
				rem[1] += (x >> 1) * y;
				rem[2] += (x - (x >> 1)) * y;
			} else rem[r] += x * y;
		}
		//for (int i = 0; i < 3; i++) cout << i << ' ' << rem[i] << endl;
		cout << "Case " << cas << ": " << work() << endl;
	}
	return 0;
}
