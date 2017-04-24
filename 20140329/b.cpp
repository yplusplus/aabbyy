#include <bits/stdc++.h>
using namespace std;

const int kind = 2;
const int N = 64444;
const int M = 64;

int n;
long long dp[N][M];
struct Node {
	int child[kind], fail;
	bool occ;
	void init() {
		memset(child, 0, sizeof(child));
		fail = occ = 0;
	}
} T[N];

int root, tot;
int que[N];

void init() {
	root = tot = 0;
	T[root].init();
}

int get_bits(long long x) {
	int res = 0;
	while (x) {
		res++;
		x >>= 1;
	}
	return res;
}

void insert(long long x) {
	int p = root;
	int cnt = get_bits(x);
	for (int i = cnt - 1; i >= 0; i--) {
		int idx = (x >> i) & 1;
		if (!T[p].child[idx]) {
			T[p].child[idx] = ++tot;
			T[tot].init();
		}
		p = T[p].child[idx];
	}
	T[p].occ = true;
}

void build_auto() {
	int head = 0, tail = 0;
	que[tail++] = root;
	while (head < tail) {
		int u = que[head++];
		for (int i = 0; i < kind; i++) {
			if (T[u].child[i]) {
				int son = T[u].child[i];
				int p = T[u].fail;
				if (u) {
					T[son].fail = T[p].child[i];
					T[son].occ |= T[T[p].child[i]].occ;
				}
				que[tail++] = son;
			} else {
				int p = T[u].fail;
				T[u].child[i] = T[p].child[i];
			}
		}
	}
}

int digit[70], dn;

long long dfs(int pos, int num, bool e, bool occ) {
	if (num == -1) { return occ; }
	if (occ && !e) return 1LL << num << 1;
	if (!e && dp[pos][num] != -1) {
		return dp[pos][num];
	}
	int u = e ? digit[num] : 1;
	long long res = 0;
	for (int d = 0; d <= u; d++) {
		res += dfs(T[pos].child[d], num - 1, e & (u == d), occ | T[T[pos].child[d]].occ);
	}
	return e ? res : dp[pos][num] = res;
}

long long calc(long long x) {
	if (!x) return 0;
	dn = 0;
	while (x) {
		digit[dn++] = x & 1;
		x >>= 1;
	}
	return dfs(0, dn - 1, 1, 0);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		for (int i = 0, x; i < n; i++) {
			scanf("%d", &x);
			insert(x);
		}
		build_auto();
		memset(dp, -1, sizeof(dp));
		long long l, r;
		cin >> l >> r;
		//cout << calc(l - 1) << endl;
		//cout << calc(r) << endl;
		long long ans = calc(r) - calc(l - 1);
		cout << ans << endl;
	}
	return 0;
}
