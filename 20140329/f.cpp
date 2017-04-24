#include <bits/stdc++.h>
using namespace std;

const int dx[4] = { 0, -1, 0, 1 };
const int dy[4] = { 1, 0, -1, 0 };
const char ch[] = "ESWN";
int id[300];

void init() { for (int i = 0; i < 4; ++i) id[ch[i]] = i; }

int run() {
	int _, n;
	init();
	cin >> _;
	string str, tmp;
	while (_--) {
		cin >> n;
		cin >> str;
		int l = str.length();
		int x, y, ans = n >> 1;
		for (int i = 0; i < 4; ++i) {
			tmp = str;
			for (int j = 0; j < l; ++j) if (tmp[j] == '?') tmp[j] = ch[i];
			x = y = (n >> 1) + 1;
			for (int j = 0; j < l; ++j) {
				int t = id[tmp[j]];
				x += dx[t];
				y += dy[t];
				ans = min(ans, min(abs(n - x), abs(x - 1)));
				ans = min(ans, min(abs(n - y), abs(y - 1)));
			}
		}
		cout << ans << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
