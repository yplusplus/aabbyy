#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <climits>
using namespace std;

const int N = 1111;
vector<pair<int, int> > vec[N];
int n, center;

int dfs(int u, int fa) {
	int leaf = true;
	int sum = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (v == fa) continue;
		leaf = false;
		int ret = dfs(v, u);
		sum += min(ret, vec[u][i].second);
		//cout << sum << " " << ret << " " << vec[u][i].second << endl;
	}
	if (leaf) return INT_MAX;
	return sum;
}
int main() {
	while (~scanf("%d%d", &n, &center)) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(pair<int, int>(b, c));
			vec[b].push_back(pair<int, int>(a, c));
		}
		int ans = dfs(center, -1);
		printf("%d\n", ans);
	}
	return 0;
}
