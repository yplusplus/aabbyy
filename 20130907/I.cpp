#pragma comment(linker,"/STACK:102400000,102400000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 111111;
int a[N], tot;
int son[N], pos[N];
vector<int> vec[N];
int n, root;
void dfs(int u, int fa) {
	son[u] = 1;
	pos[u] = ++tot;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		dfs(v, u);
		son[u] += son[v];
	}
}

struct BIT {
	int c[N];
	void clear() {
		memset(c, 0, sizeof(c));
	}
	int lowbit(int x) { return x & (-x); }
	void insert(int x, int v) {
		for (int i = x; i <= n; i += lowbit(i)) c[i] += v;
	}
	int query(int x) {
		int res = 0;
		for (int i = x; i; i -= lowbit(i)) res += c[i];
		return res;
	}
} bit;

int main() {
	while (~scanf("%d%d", &n, &root), n + root) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			vec[a].push_back(b);
			vec[b].push_back(a);
		}
		tot = 0;
		dfs(root, 0);
		bit.clear();
		for (int i = 1; i <= n; i++) {
			int l = pos[i], r = pos[i] + son[i] - 1;
			int ans = bit.query(r) - bit.query(l);
			printf("%d%c", ans, i == n ? '\n' : ' ');
			bit.insert(pos[i], 1);
		}
	}
	return 0;
}