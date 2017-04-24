#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 55555;
vector<int> vec[N];
int n;
int tot, st[N], ed[N];
void dfs(int u) {
	st[u] = ++tot;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		dfs(v);
	}
	ed[u] = tot;
}

struct BIT {
	int c[N];
	void clear() { memset(c, 0, sizeof(c)); }
	int lowbit(int x) { return (x & (-x)); }
	void insert(int x) {
		for (int i = x; i <= n; i += lowbit(i)) c[i]++;
	}
	int query(int x) {
		int res = 0;
		for (int i = x; i; i -= lowbit(i)) res += c[i];
		return res;
	}
} bit;

int ans[N];
int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 2; i <= n; i++) {
			int p;
			scanf("%d", &p);
			vec[p].push_back(i);
		}
		tot = 0;
		dfs(1);

		bit.clear();
		for (int i = n; i >= 1; i--) {
			ans[i] = bit.query(ed[i]) - bit.query(st[i]);
			bit.insert(st[i]);
		}
		printf("Case #%d:", Case++);
		for (int i = 1; i <= n; i++) {
			printf(" %d", ans[i]);
		}
		puts("");
	}
	return 0;
}

