#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

const int N = 222;
int a[N];
int n, m;
vector<int> vec[N];
int match[N * N];
bool visit[N * N];

bool dfs(int u) {
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (visit[v]) continue;
		visit[v] = true;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int Match() {
	int cnt = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < n; i++) {
		memset(visit, false, sizeof(visit));
		if (dfs(i)) cnt++;
	}
	return cnt;
}

map<long long, int> mp;
int main() {
	while (~scanf("%d%d", &n, &m)) {
		mp.clear();
		int tot = 0;
		for (int i = 0; i < n; i++) {
			vec[i].clear();
			scanf("%d", &a[i]);
			long long tmp = 1 % m;
//			if (a[i] == 0) tmp = 0;
			for (int j = 0; j < n; j++) {
				if (mp.count(tmp) == 0) mp[tmp] = ++tot;
				vec[i].push_back(mp[tmp]);
				tmp = tmp * a[i] % m;
			}
		}
		int ret = Match();
		printf("%d\n", ret);
	}
}
