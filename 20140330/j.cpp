#include <bits/stdc++.h>
using namespace std;

const int N = 40;
const long long MOD = 47789421357654LL;
const long long KEY = 131;
int st[N];
int ed[N];
map<long long, int> mp;
int L[N], M[N];
int n, m, k;
int first, second;

void rot(int b[], int a[], int ll, int mm, int n) {
	int len = n - ll - mm;
	for(int i = 0; i < ll; i ++) b[i] = a[i + len];
	for(int i = 0; i < len; i ++) b[i + ll] = a[i];
	for(int i = 0; i < mm; i ++) b[i + len + ll] = a[i + len + ll];
}

long long encode(int a[], int n) {
	long long res = 0;
	long long pw = 1;
	for (int i = 0; i < n; i++) {
		res = (res + a[i] * pw) % MOD;
		pw = (pw * KEY) % MOD;
	}
	return res;
}

void dfs1(int a[], int depth, int op) {
	if (depth == 0) {
		mp[encode(a, n)] = op;
		return;
	}
	int b[N];
	for (int i = 0; i < m; i++) {
		int ll = L[i], mm = M[i];
		rot(b,a,ll,mm,n);
		dfs1(b, depth - 1, (op << 3) | i);
	}
}

bool dfs2(int a[], int depth, int op) {
	if (depth == 0) {
		if (mp.count(encode(a, n))) {
			int fi = mp[encode(a, n)];
			int se = op;
			int tmp = 0;
			for (int i = 0; i < first; i++) {
				tmp <<= 3;
				tmp |= fi & 7;
				fi >>= 3;
			}
			for (int i = 0; i < first; i++) {
				printf("%d ", (tmp & 7) + 1);
				tmp >>= 3;
			}
			for (int i = 0; i < second; i++) {
				printf("%d%c", (se & 7) + 1, i == second - 1 ? '\n' : ' ');
				se >>= 3;
			}
			return true;
		}
		return false;
	}
	int b[N];
	for (int i = 0; i < m; i++) {
		int ll = L[i], mm = M[i];
		rot(b,a,n - ll - mm,mm,n);
		if (dfs2(b, depth - 1, (op << 3) | i)) return true;
	}
	return false;
}

int main() {
	while (~scanf("%d%d%d", &n, &k, &m)) {
		mp.clear();
		for (int i = 0; i < n; i++) scanf("%d", &st[i]);
		for (int i = 0; i < n; i++) scanf("%d", &ed[i]);
		for (int i = 0; i < m; i++) { scanf("%d%d", &M[i], &L[i]); }
		first = k / 2;
		second = k - first;
		dfs1(st, first, 0);
		if (!dfs2(ed, second, 0)) { puts("Impossible"); }
	}
	return 0;
}
