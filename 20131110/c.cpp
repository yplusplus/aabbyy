#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 11111;
const int M = 22222;
const int Q = 55555;
int power[N];
struct MFS {
	int mx[N], fa[N];
	void init() { for (int i = 0; i < N; i++) mx[i] = fa[i] = i; }
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return ;
		fa[fy] = fx;
		if (power[mx[fx]] < power[mx[fy]] || power[mx[fx]] == power[mx[fy]] && mx[fx] > mx[fy]) mx[fx] = mx[fy];
	}
	int query(int x) {
		int fx = find(x);
		if (mx[fx] == x || power[mx[fx]] == power[x]) return -1;
		return mx[fx];
	}
} mfs;

int u[M], v[M];
bool destroy[M];
int qry[Q][3], ans[Q];
int n, m, q;
typedef pair<int, int> PII;
map<PII, int> id;

int main() {
	//freopen("in", "r", stdin);
	bool pnt = 0;
	while (~scanf("%d", &n)) {
		if (pnt) puts("");
		pnt = 1;
		for (int i = 0; i < n; i++) scanf("%d", power + i);
		scanf("%d", &m);
		id.clear();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", u + i, v + i);
			if (u[i] > v[i]) swap(u[i], v[i]);
			id[PII(u[i], v[i])] = i;
			destroy[i] = 0;
		}
		scanf("%d", &q);
		char op[11];
		for (int i = 0; i < q; i++) {
			scanf("%s", op);
			if (*op == 'q') {
				qry[i][0] = 0;
				scanf("%d", qry[i] + 1);
			} else {
				qry[i][0] = 1;
				scanf("%d%d", qry[i] + 1, qry[i] + 2);
				if (qry[i][1] > qry[i][2]) swap(qry[i][1], qry[i][2]);
				destroy[id[PII(qry[i][1], qry[i][2])]] = 1;
			}
		}
		mfs.init();
		for (int i = 0; i < m; i++) {
			if (destroy[i]) continue;
			mfs.merge(u[i], v[i]);
		}
		for (int i = q - 1; i >= 0; i--) {
			if (qry[i][0]) mfs.merge(qry[i][1], qry[i][2]);
			else ans[i] = mfs.query(qry[i][1]);
		}
		for (int i = 0; i < q; i++) if (!qry[i][0]) printf("%d\n", ans[i]);
	}
	return 0;
}

