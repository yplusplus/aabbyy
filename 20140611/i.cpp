#include <bits/stdc++.h>
using namespace std;

const int N = 27;
const int M = 105;
const int KIND = 26;
int n, m;
long long dp[N][M][1 << 10];
vector<pair<pair<int, int>, char> > vec[N][M][1 << 10];

struct Node {
	int child[KIND];
	int fail, id;
	void init() {
		memset(child, 0, sizeof(child));
		fail = id = 0;
	}
} node[M];

vector<string> ans_str;

struct Trie {
	int root, alloc;
	void clear() {
		root = alloc = 0;
		node[root].init();
	}
	void insert(char *str, int id) {
		int p = root;
		while (*str) {
			int idx = *str - 'a';
			if (!node[p].child[idx]) {
				node[p].child[idx] = ++alloc;
				node[alloc].init();
			}
			p = node[p].child[idx];
			str++;
		}
		node[p].id |= 1 << id;
	}
	void build() {
		queue<int> que;
		que.push(root);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (int i = 0; i < KIND; i++) {
				int v = node[u].child[i];
				int ufail = node[u].fail;
				if (v) {
					if (u != root) {
						node[v].fail = node[ufail].child[i];
					} else {
						node[v].fail = root;
					}
					node[v].id |= node[node[v].fail].id;
					que.push(v);
				} else {
					node[u].child[i] = node[ufail].child[i];
				}
			}
		}
	}
} trie;

char str[100];

void dfs(int i, int pos, int mask) {
	if (i == 0) {
		ans_str.push_back(string(str));
		return;
	} else {
		for (int j = 0; j < vec[i][pos][mask].size(); j++) {
			str[i - 1] = vec[i][pos][mask][j].second;
			dfs(i - 1, vec[i][pos][mask][j].first.first, vec[i][pos][mask][j].first.second);
		}
	}
}

void solve() {
	trie.build();
	//cout << 123123 << endl;
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= trie.alloc; j++) {
			for (int k = 0; k < (1 << m); k++) {
				//cout << i << " " << j << " " << k << endl;
				if (dp[i][j][k] == 0) continue;
				for (int l = 0; l < KIND; l++) {
					int son = node[j].child[l];
					int nk = k | node[son].id;
					dp[i + 1][son][nk] += dp[i][j][k];
				}
			}
		}
	}
	//cout << 123123 << endl;
	long long ans = 0;
	for (int i = 0; i <= trie.alloc; i++) {
		ans += dp[n][i][(1 << m) - 1];
	}
	printf("%lld suspects\n", ans);
	if (ans <= 42) {
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= trie.alloc; j++) {
				for (int k = 0; k < (1 << m); k++) {
					vec[i][j][k].clear();
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= trie.alloc; j++) {
				for (int k = 0; k < (1 << m); k++) {
					if (dp[i][j][k] == 0) continue;
					for (int l = 0; l < KIND; l++) {
						int son = node[j].child[l];
						int nk = k | node[son].id;
						vec[i + 1][son][nk].push_back(make_pair(make_pair(j, k), 'a' + l));
						dp[i + 1][son][nk] += dp[i][j][k];
					}
				}
			}
		}
		str[n] = 0;
		ans_str.clear();
		for (int i = 0; i <= trie.alloc; i++) {
			if (dp[n][i][(1 << m) - 1]) dfs(n, i, (1 << m) - 1);
		}
		sort(ans_str.begin(), ans_str.end());
		for (int i = 0; i < ans_str.size(); i++) {
			puts(ans_str[i].c_str());
		}
	}
}

int main() {
	int Case = 1;
	while (~scanf("%d%d", &n, &m), n || m) {
		trie.clear();
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			trie.insert(str, i);
		}
		printf("Case %d: ", Case++);
		solve();

	}
	return 0;
}
