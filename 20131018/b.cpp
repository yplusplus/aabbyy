#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111111;
char s[N];
int len;

void con() {
	len = strlen(s);
	for (int i = 0; i < len; i++) s[i] = (s[i] - '1') % 3;
}

int work(int l, int r, int nx) {
	int ans = 0;
	for (int i = 2; i < len; i++) {
		//cout << (int) s[i] << endl;
		if (nx == 0) {
			l = s[i];
			if (l > r) {
				ans++;
				swap(l, r);
			} else nx ^= 1;
		} else {
			r = s[i];
			if (l > r) {
				ans++;
				swap(l, r);
			} else nx ^= 1;
		}
	}
	return ans;
}

int work() {
	if (len <= 2) return 0;
	if (s[0] < s[1]) return work(s[0], s[1], 0);
	if (s[0] > s[1]) return work(s[1], s[0], 1);
	return min(work(s[0], s[0], 0), work(s[0], s[0], 1));
}

int main() {
	int L, R;
	while (cin >> s && s[0] != '#') {
		con();
		cout << work() << endl;
	}
	return 0;
}


