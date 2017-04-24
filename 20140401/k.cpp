#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VII;
typedef vector<int> VI;
VII answer;

bool check(int a, int b, int c, int d, int n, int m) {
	answer.clear();
	if (n <= a || m <= d || n < c || m < b) return 0;
	if (n * a & 1) return 0;
	if (m * d & 1) return 0;
	if (a & 1) {
		int hn = n >> 1;
		for (int i = 0; i < hn; ++i) answer.push_back(PII(i + 1, i + hn + 1));
	}
	a >>= 1;
	for (int dt = 1; dt <= a; ++dt) {
		for (int i = 0; i < n; ++i) {
			answer.push_back(PII(i + 1, (i + dt) % n + 1));
		}
	}
	if (d & 1) {
		int hm = m >> 1;
		for (int i = 0; i < hm; ++i) answer.push_back(PII(i + n + 1, i + n + hm + 1));
	}
	d >>= 1;
	for (int dt = 1; dt <= d; ++dt) {
		for (int i = 0; i < m; ++i) {
			answer.push_back(PII(i + n + 1, (i + dt) % m + n + 1));
		}
	}
	int cur = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < b; ++j) {
			answer.push_back(PII(i + 1, cur + n + 1));
			++cur;
			if (cur >= m) cur -= m;
		}
	}
	return 1;
}

int run() {
	int a, b, c, d;
	while (cin >> a >> b >> c >> d) {
		int LCM = b * c / __gcd(b, c);
		int base_n = LCM / b, base_m = LCM / c, k = 1;
		//cout << base_n << ' ' << base_m << endl;
		while (1) {
			if (check(a, b, c, d, k * base_n, k * base_m)) break;
			++k;
		}
		cout << (k * base_n) << ' ' << (k * base_m) << endl;
		for (int i = 0, size = answer.size(); i < size; ++i) if (answer[i].first > answer[i].second) swap(answer[i].first, answer[i].second);
		sort(answer.begin(), answer.end());
		for (int i = 0, size = answer.size(); i < size; ++i) cout << answer[i].first << ' ' << answer[i].second << endl;
	}
	return 0;
}

int main() {
	freopen("kids.in", "r", stdin);
	freopen("kids.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
