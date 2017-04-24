#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int MOD = 1;
struct Mat {
	int v[2][2];
	Mat() {}
	Mat(int x) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				v[i][j] = 0;
			}
			v[i][i] = x;
		}
	}
} ;

Mat operator * (Mat a, Mat b) {
	Mat ret(0);
	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			if (a.v[i][k]) {
				for (int j = 0; j < 2; j++) {
					ret.v[i][j] += a.v[i][k] * b.v[k][j];
					ret.v[i][j] %= MOD;
				}
			}
		}
	}
	return ret;
}

const int N = 33333;
Mat val[N << 2];

void up(int rt) {
	val[rt] = val[rt << 1] * val[rt << 1 | 1];
}

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
void build(int l, int r, int rt) {
	if (l == r) {
		for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) scanf("%d", &val[rt].v[i][j]);
		return ;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	up(rt);
}

Mat query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) return val[rt];
	int m = l + r >> 1;
	Mat ret(1);
	if (L <= m) ret = ret * query(L, R, lson);
	if (m < R) ret = ret * query(L, R, rson);
	return ret;
}	


int main() {
	//freopen("in", "r", stdin);
	bool p1 = 0;
	int n, q, x, y;
	while (~scanf("%d%d%d", &MOD, &n, &q)) {
		if (p1) puts("");
		else p1 = 1;
		build(1, n, 1);
		bool p2 = 0;
		while (q--) {
			if (p2) puts("");
			else p2 = 1;
			scanf("%d%d", &x, &y);
			Mat out = query(x, y, 1, n, 1);
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					if (j) putchar(' ');
					printf("%d", out.v[i][j]);
				}
				puts("");
			}
		}
	}
	return 0;
}
