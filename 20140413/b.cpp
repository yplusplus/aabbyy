#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<LL> VL;
VL a, b;

LL bruteForce(int n, int m) {
	LL sum = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) sum += max(a[i] - b[j], b[j] - a[i]) * (i - j);
	return sum;
}

const int N = 1 << 14;
VL x, y, z, c;

void init() {
	c.clear();
	c.resize(N + 1, 0);
	x.clear();
	x.resize(N + 1, 0);
	y.clear();
	y.resize(N + 1, 0);
	z.clear();
	z.resize(N + 1, 0);
}

LL work(int n, int m) {
	init();
	for (int i = 1; i <= n; ++i) {
		++c[a[i]];
		x[a[i]] += a[i] * i;
		y[a[i]] += a[i];
		z[a[i]] += i;
	}
	for (int i = 1; i <= N; ++i) x[i] += x[i - 1], y[i] += y[i - 1], z[i] += z[i - 1], c[i] += c[i - 1];
	LL sum = 0;
	for (int i = 1; i <= m; ++i) {
		sum += (x[N] - x[b[i]]) - (y[N] - y[b[i]]) * i - (z[N] - z[b[i]]) * b[i] + b[i] * i * (c[N] - c[b[i]]);
		sum += z[b[i] - 1] * b[i] - x[b[i] - 1] - b[i] * i * c[b[i] - 1] + y[b[i] - 1] * i;
	}
	return sum;
}

int run() {
	int n, m;
	while (cin >> n >> m) {
		a.resize(n + 1);
		b.resize(m + 1);
		for (int i = 1; i <= n; ++i) cin >> a[i];
		for (int i = 1; i <= m; ++i) cin >> b[i];
		//cout << bruteForce(n, m) << endl;
		cout << work(n, m) << endl;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
