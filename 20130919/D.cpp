#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007;

LL multi(LL a, LL p) {
	LL ret = 1;
	while (p > 0) {
		if (p & 1) ret *= a, ret %= MOD;
		a *= a, a %= MOD, p >>= 1;
	}
	return ret;
}

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a;}

const int N = 11111;
LL ep[N];
LL cal(LL n, LL m) {
	ep[0] = 1;
	for (int i = 1; i <= m; i++) ep[i] = ep[i - 1] * n, ep[i] %= MOD;
	LL c1 = 0;
	for (int i = 0; i < m; i++) c1 += ep[gcd(i, m)], c1 %= MOD;
	LL c2;
	if (m & 1) c2 = m * ep[m + 1 >> 1], c2 %= MOD;
	else c2 = (m >> 1) * ep[m >> 1] % MOD + (m >> 1) * ep[m + 2 >> 1] % MOD, c2 %= MOD;
	//cout << c1 + c2 << endl;
	return (c1 + c2) * multi(m * 2, MOD - 2) % MOD;
}

int main() {
	//freopen("in", "r", stdin);
	int T;
	cin >> T;
	for (int cas = 1; cas <= T; cas++) {
		LL n, m;
		cin >> n >> m;
		cout << "Case #" << cas << ": " << cal(n, m) << endl;
	}
	return 0;
}


