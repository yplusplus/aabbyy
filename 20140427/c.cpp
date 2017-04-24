#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 3 << 18 | 1;
const int ROOT = 10;
const int K = 16;
const int N = 1 << K;

LL powerMod(LL a, int p) {
	a %= MOD;
	LL s = 1;
	while (p > 0) {
		if (p & 1) s *= a, s %= MOD;
		a *= a, a %= MOD, p >>= 1;
	}
	return s;
}
inline LL inverse(LL a) { return powerMod(a, MOD - 2); }

void NTT(LL *const P, int n, bool intt) {
	for (int i = 1, j = 0; i < n - 1; ++i) {
		for (int s = n; j ^= s >>= 1, ~j & s; ) ;
		if (i < j) swap(P[i], P[j]);
	}
	for (int d = 0; (1 << d) < n; ++d) {
		int m = 1 << d, m2 = m << 1;
		LL op = powerMod(ROOT, MOD - 1 >> d + 1);
		if (intt) op = inverse(op);
		for (int i = 0; i < n; i += m2) {
			LL base = 1;
			for (int j = 0; j < m; ++j) {
				LL &P1 = P[i + j + m], &P2 = P[i + j];
				LL t = base * P1 % MOD;
				P1 = (P2 - t + MOD) % MOD;
				P2 += t;
				P2 %= MOD;
				base *= op;
				base %= MOD;
			}
		}
	}
}

inline int lowbit(int x) { return x & -x; }
LL t1[N], t2[N], temp[N];
int multiply(const LL *const A, const int n, const LL *const B, const int m, LL *const C) {
	int len = n + m;
	while (lowbit(len) != len) len += lowbit(len);
	for (int i = 0; i < len; ++i) t1[i] = i < n ? A[i] : 0;
	for (int i = 0; i < len; ++i) t2[i] = i < m ? B[i] : 0;
	NTT(t1, len, 0);
	NTT(t2, len, 0);
	for (int i = 0; i < len; ++i) C[i] = t1[i] * t2[i] % MOD;
	NTT(C, len, 1);
	LL inv = inverse(len);
	for (int i = 0; i < len; ++i) C[i] *= inv, C[i] %= MOD;
	return len;
}

inline LL inverse2(const LL &a) { return a <= 1 ? a : (LL) (MOD - MOD / a) * inverse2(MOD % a) % MOD; }
LL ans[K][N] = { {0, 1}, { 0, 0, 2, 1} };
void PRE(int k = K) {
	for (int i = 2; i < k; ++i) {
		multiply(ans[i - 1], 1 << i, ans[i - 1], 1 << i, temp);
		for (int j = 1; j < (1 << i + 1); ++j) {
			ans[i][j] += temp[j - 1];
			ans[i][j] %= MOD;
		}
		multiply(ans[i - 1], 1 << i, ans[i - 2], 1 << i, temp);
		for (int j = 1; j < (1 << i + 1); ++j) {
			ans[i][j] += temp[j - 1] << 1;
			ans[i][j] %= MOD;
		}
	}
}

void test() {
	const int T = 1 << 5;
	LL A[T], B[T], C[T];
	for (int i = 0; i < 3; ++i) cin >> A[i];
	for (int i = 0; i < 3; ++i) cin >> B[i];
	int t = multiply(A, 3, B, 3, C), n;
	for (int i = 0; i < t; ++i) cout << C[i] << ' '; cout << endl;
	while (cin >> n) cout << inverse(n) << ' ' << inverse2(n) << endl;
}

int run() {
	int n, m;
	//test();
	//PRE();
	while (cin >> n >> m) {
		PRE(m + 1);
		cout << ans[m][n] << endl;
	}
	return 0;
}

int main() {
	freopen("avl.in", "r", stdin);
	freopen("avl.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}