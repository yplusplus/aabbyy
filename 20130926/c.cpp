#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int N = 55555;
vector<int> vec[N];

struct SegmentTree {
	int v[N << 2];
	int lazy[N << 2];
	void pushdown(int p) {
		if (lazy[p] != -2) {
			v[p << 1] = v[p << 1 | 1] = lazy[p];
			lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
			lazy[p] = -2;
		}
	}

	void update(int p, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) {
			lazy[p] = v[p] = x;
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (L <= mid) update(p << 1, l, mid, L, R, x);
		if (R > mid) update(p << 1 | 1, mid + 1, r, L, R, x);
	}
	
	int query(int p, int l, int r, int x) {
		if (l == r) return v[p];
		pushdown(p);
		int mid = l + r >> 1;
		if (x <= mid) return query(p << 1, l, mid, x);
		else return query(p << 1 | 1, mid + 1, r, x);
	}
} st;

int tot;
int pos[N], son[N];
void dfs(int u) {
	//cout << u << endl;
	pos[u] = ++tot;
	son[u] = 1;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		dfs(v);
		son[u] += son[v];
	}
}

bool isroot[N];
int n, m;
int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);

		memset(isroot, true, sizeof(isroot));
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &v, &u);
			vec[u].push_back(v);
			isroot[v] = false;
		}
		int root = -1;
		for (int i = 1; i <= n; i++) {
			if (isroot[i]) {
				root = i;
				break;
			}
		}
		//cout << 123123 << endl;
		tot = 0;
		dfs(root);
		//cout << 123123 << endl;
		scanf("%d", &m);
		st.update(1, 1, n, 1, n, -1);
		char cmd[5];
		int x, y;
		printf("Case #%d:\n", Case++);
		while (m--) {
			scanf("%s", cmd);
			if (cmd[0] == 'C') {
				scanf("%d", &x);
				printf("%d\n", st.query(1, 1, n, pos[x]));
			} else {
				scanf("%d%d", &x, &y);
				//cout << pos[x] << " " << pos[x] + son[x] - 1 << endl;
				st.update(1, 1, n, pos[x], pos[x] + son[x] - 1, y);
			}
		}
	}
	return 0;
}

