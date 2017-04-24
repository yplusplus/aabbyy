#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 333;
const double PI = acos(-1.0);
int n, m;
char mat[N][N];

struct MFS {
	int fa[N * N];
	double sum[N * N];
	void init(int n) { for (int i = 0; i < n; i++) fa[i] = i, sum[i] = 0; }
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	void add(int x, double s) {
		int fx = find(x);
		sum[fx] += s;
	}
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return ;
		fa[fx] = fy;
		sum[fy] += sum[fx];
	}
	double get(int x) { return sum[find(x)]; }
} mfs;

inline int encode(int x, int y) { return x * m + y; }

void gao() {
	int a = n, b = m;
	n = n << 1 | 1;
	m = m << 1 | 1;
	mfs.init(n * m);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			int x = i << 1 | 1, y = j << 1 | 1, c = encode(x, y);
			mfs.add(c, 4 - PI / 2);
			if (mat[i][j] & 1) {
				mfs.add(encode(x - 1, y + 1), PI / 4);
				mfs.add(encode(x + 1, y - 1), PI / 4);
				mfs.merge(c, encode(x + 1, y + 1));
				mfs.merge(c, encode(x - 1, y - 1));
			} else {
				mfs.add(encode(x - 1, y - 1), PI / 4);
				mfs.add(encode(x + 1, y + 1), PI / 4);
				mfs.merge(c, encode(x - 1, y + 1));
				mfs.merge(c, encode(x + 1, y - 1));
			}
		}
	}
}

int main() {
	int _;
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) scanf("%s", mat[i]);
		gao();
		int q, x, y;
		scanf("%d", &q);
		printf("Case %d:\n", cas);
		while (q--) {
			scanf("%d%d", &x, &y);
			printf("%.4lf\n", mfs.get(encode(x, y)));
		}
	}
	return 0;
}
