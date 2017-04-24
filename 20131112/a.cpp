#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
bool check(LL a) {
	if (a % 7 == 0) return 1;
	while (a) {
		if (a % 10 == 7) return 1;
		a /= 10;
	}
	return 0;
}

/*
const int N = 288888888;
int ans[N];
void PRE() {
	int cur = 0;
	memset(ans, 0x77, sizeof(ans));
	for (int i = 1; i < N; i++) {
		if (check(i)) cur++;
		else cur = 0;
		if (cur) ans[cur] = min(i - cur + 1, ans[cur]);
	}
	for (int i = 1; i < N; i++) if (ans[i] != ans[i - 1]) cout << i << ' ' << ans[i] << endl;
	cout << "end" << endl;
}
*/

LL find(LL a, LL ep) {
	for (int i = 0; i < 10; i++) {
		LL l, r;
		if (i == 7) l = 7 * ep * 10, r = 8 * ep * 10 - 1;
		else l = (i * 10 + 7) * ep, r = (i * 10 + 8) * ep - 1;
		//cout << l << ' ' << r << endl;
		while (check(l - 1)) l--;
		while (check(r + 1)) r++;
		if (r - l + 1 >= a) return l;
	}
	return -1;
}

LL work(LL a) {
	LL ep = 1;
	while (1) {
		if (ep * 10 >= a) {
			LL t = find(a, ep);
			if (t > 0) return t;
		}
		ep *= 10;
	}
	return 0;
}

int main() {
	int _;
	LL n;
	//PRE();
	//for (int i = 1; i <= 1234567; i++) if (ans[i] != work(i)) cout << i << ' ' << ans[i] << ' ' << work(i) << endl;
	cin >> _;
	while (_--) {
		cin >> n;
		cout << work(n) << endl;
	}
	return 0;
}
