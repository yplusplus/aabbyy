#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 11111;
vector<int> vec[N];
bool visit[N];
vector<int> que;
int cnt[10];
int n, m;

void dfs(int u) {
	visit[u] = true;
	cnt[min((int)vec[u].size(), 4)]++;
	if (vec[u].size() == 3) que.push_back(u);
	for (int i = 0; i < vec[u].size(); i++) {
		if (!visit[vec[u][i]]) {
			dfs(vec[u][i]);
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			vec[a].push_back(b);
			vec[b].push_back(a);
		}
		memset(visit, false, sizeof(visit));
		int valid = false;
		for (int i = 1; i <= n && !valid; i++) {
			if (!visit[i]) {
				memset(cnt, 0, sizeof(cnt));
				que.clear();
				dfs(i);
				int sz = que.size();
				if (cnt[4] > 0) valid = true;
				else {
					for (int j = 0; j < sz; j++) {
						memset(cnt, 0, sizeof(cnt));
						visit[que[j]] = false;
						//cnt[que[j]] = true;
						for (int k = 0; k < 3; k++) {
							//cnt[vec[que[j]][k]] = true;
							visit[vec[que[j]][k]] = false;
						}
						for (int k = max(0, j - 10); k < min(sz, j + 10); k++) {
							int tot = 0;
							for (int l = 0; l < 3; l++) {
								tot += !visit[vec[que[k]][l]];
							}
							if (tot <= 1) {
								valid = true;
								break;
							}
						}
						visit[que[j]] = true;
						for (int k = 0; k < 3; k++) {
							//cnt[vec[que[j]][k]] = true;
							visit[vec[que[j]][k]] = true;
						}
					}
				}
			}
		}
		puts(valid ? "YES" : "NO");
	}
	return 0;
}
