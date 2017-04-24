#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111111;
const int MOD = 1e9 + 7;
int nx[N], x[N], y[N];

int getnx(int n) {
	int i = 0, j = -1;
	nx[i] = j;
	while (i < n) {
		while (j >= 0 && (x[i] != x[j] || y[i] != y[j])) j = nx[j];
		i++, j++;
		nx[i] = j;
	}
	//for (int i = 0; i < n; i++) {
		//nx[i]++;
		//cout << i << ' ' << nx[i] << endl;
		//if ((i + 1 - nx[i]) != 0 && (i + 1) % (i + 1 - nx[i]) == 0) cout << (i + 1) / (i + 1 - nx[i]) << endl;
	//}
	if (n % (n - nx[n])) return n;
	return n - nx[n];
}

typedef long long LL;
inline LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a;}
void gcd(LL a, LL b, LL &x, LL &y, LL &d) {
	if (b) { gcd(b, a % b, y, x, d); y -= a / b * x;}
	else { x = -1, y = 0, d = a;}
}

LL powmod(LL a, LL b) {
	LL ret = 1;
	while (b > 0) {
		if (b & 1) ret *= a, ret %= MOD;
		a *= a, a %= MOD, b >>= 1;;
	}
	return ret;
}

LL pw[N];

int main() {
	//freopen("in", "r", stdin);
	int n, m, T;
	scanf("%d", &T);
	while (T-- && ~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++) scanf("%d", x + i);
		for (int i = 0; i < n; i++) scanf("%d", y + i);
		int l = getnx(n), c = n / l;
		//cout << l << ' ' << c << endl;
		LL p = powmod(m, l);
		pw[0] = 1;
		for (int i = 1; i <= c; i++) pw[i] = pw[i - 1] * p % MOD;
		LL sum = 0;
		for (int i = 0; i < c; i++) sum += pw[gcd(i, c)], sum %= MOD;
		//cout << sum << ' ' << c << ' ' << powmod(n, MOD - 2) << endl;
		cout << powmod(c, MOD - 2) * sum % MOD << endl;
	}
	return 0;
}

