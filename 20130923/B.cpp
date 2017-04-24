#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int kind = 4;
const int N = 66;
int w[256];
int que[N];
int root, tot;
int n, m, L;
struct Node {
	int child[kind], fail, id;
	void init() {
		memset(child, 0, sizeof(child));
		fail = id = 0;
	}
} T[N];

void init() {
	root = tot = 0;
	T[root].init();
}

void insert(char *s, int id) {
	int p = root;
	while (*s) {
		int index = w[*s];
		if (!T[p].child[index]) {
			T[++tot].init();
			T[p].child[index] = tot;
		}
		p = T[p].child[index];
		s++;
	}
	T[p].id = id;
}

void build_ac_auto() {
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
					T[son].id += T[T[p].child[i]].id;
				}
				que[tail++] = son;
			} else {
			 	int p = T[u].fail;
				T[u].child[i] = T[p].child[i];
			}
		}
	}
}

char str[10][10];

struct Mat {
	int val[N][N];
	void zero() {
		memset(val, 0, sizeof(val));
	}
	void unit() {
		zero();
		for (int i = 0; i < N; i++) {
			val[i][i] = 1;
		}
	}
};

const int MOD = 10007;
int add(int a, int b) {
	return (a + b) % MOD;
}

Mat operator*(const Mat &a, const Mat &b) {
	Mat res;
	res.zero();
	for (int k = 0; k < m; k++) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				res.val[i][j] = add(res.val[i][j], a.val[i][k] * b.val[k][j]);
			}
		}
	}
	return res;
}

Mat operator^(Mat a, int n) {
	Mat res;
	res.unit();
	while (n) {
		if (n & 1) res = res * a;
		a = (a * a);
		n >>= 1;
	}
	return res;
}

int mul(int a, int b) {
	return (a * b) % MOD;
}
int fac[1111111];
int dp[2][33][3];
int main() {
	fac[0] = 1;
	for (int i = 1; i < 1111111; i++) fac[i] = mul(fac[i - 1], 4);
	w['A'] = 0;
	w['C'] = 1;
	w['T'] = 2;
	w['G'] = 3;
	Mat res, b;
	while (~scanf("%d%d", &n, &L)) {
		init();
		for (int i = 0; i < n; i++) {
			scanf("%s", str[i]);
			insert(str[i], 1);
		}
		build_ac_auto();
		b.zero();
		m = tot + 1;
		for (int i = 0; i <= tot; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < kind; k++) {
					int son = T[i].child[k];
					int jj = j + T[son].id;
					if (jj >= 2) continue;
					b.val[i + (m * j)][son + (jj * m)]++;
				}
			}
		}
		res.zero();
		res.val[0][0] = 1;
		m = 2 * m;
		res = res * (b ^ L);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			ans = add(ans, res.val[0][i]);
		}
		//cout << ans << endl;
		ans = (fac[L] - ans + MOD) % MOD;
		printf("%d\n", ans);
		
	}
	return 0;
}