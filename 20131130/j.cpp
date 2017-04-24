#include <cstdio>
#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 0, 1000000, 1

typedef long long LL;
const LL MOD = 1e9 + 7;
const int N = 1111111;
inline LL fix(LL x) { return (x % MOD + MOD) % MOD; }
template<class T> T sqr(T x) { return x * x; }
LL sum[N << 2], add[N << 2][4];

LL get_sum(int x, int xp) {
	if (xp == 0) return x;
	if (xp == 1) return fix((LL) x * (x + 1) >> 1);
	if (xp == 2) return fix((LL) x * (x + 1) * (x << 1 | 1) / 6);
	if (xp == 3) return fix(sqr(get_sum(x, 1)));
	return 0;
}
LL get_sum(int l, int r, int xp) { return fix(get_sum(r, xp) - get_sum(l - 1, xp)); }
inline void up(int rt) { sum[rt] = fix(sum[rt << 1] + sum[rt << 1 | 1]); }

void down(int rt, int l, int r) {
	int ls = rt << 1, rs = rt << 1 | 1, m = l + r >> 1;
	for (int i = 0; i < 4; i++) {
		if (add[rt][i]) {
			sum[ls] = fix(sum[ls] + add[rt][i] * get_sum(l, m, i));
			sum[rs] = fix(sum[rs] + add[rt][i] * get_sum(m + 1, r, i));
			add[ls][i] = fix(add[ls][i] + add[rt][i]);
			add[rs][i] = fix(add[rs][i] + add[rt][i]);
			add[rt][i] = 0;
		}
	}
}

void build(int l, int r, int rt) {
	sum[rt] = 0;
	for (int i = 0; i < 4; i++) add[rt][i] = 0;
	if (l == r) return ;
	int m = l + r >> 1;
	build(lson);
	build(rson);
}

void insert(int *x, int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		for (int i = 0; i < 4; i++) {
			sum[rt] = fix(sum[rt] + x[i] * get_sum(l, r, i));
			add[rt][i] = fix(add[rt][i] + x[i]);
		}
		return ;
	}
	int m = l + r >> 1;
	down(rt, l, r);
	if (L <= m) insert(x, L, R, lson);
	if (m < R) insert(x, L, R, rson);
	up(rt);
}

LL query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) return sum[rt];
	LL sum = 0;
	int m = l + r >> 1;
	down(rt, l, r);
	if (L <= m) sum = fix(sum + query(L, R, lson));
	if (m < R) sum = fix(sum + query(L, R, rson));
	up(rt);
	return sum;
}

int main() {
	//freopen("in", "r", stdin);
	int _, n;
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		printf("Case #%d:\n", cas);
		scanf("%d", &n);
		build(root);
		char op[3];
		int l, r, x[4];
		while (n--) {
			scanf("%s%d%d", op, &l, &r);
			for (int i = 3; i >= 0; i--) {
				scanf("%d", x + i);
				x[i] = fix(x[i]);
			}
			if (*op == 't') {
				LL ans = query(l, r, root);
				printf("%d\n", (int) ans);
				l = l * ans % 1000000;
				r = r * ans % 1000000;
				if (l > r) swap(l, r);
			}
			insert(x, l, r, root);
		}
	}
	return 0;
}

