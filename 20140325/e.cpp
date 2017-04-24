#include <bits/stdc++.h>
using namespace std;

const int M = 26;
const int N = 111;
char str[1111];
int n, q;
struct Node {
	int a, b, c;
	void read() {
		scanf("%s", str); a = str[0] - 'A';
		scanf("%s", str); b = str[0] - 'A';
		scanf("%d", &c);
	}
};
vector<Node> vec[N];

int dp[N][N][M];
bool visit[N][N][M];

void check_min(int &a, int b) {
	if (a == -1 || a > b) a = b;
}

int dfs(int l, int r, int id) {
	if (l == r && id == str[l] - 'A') return 0;
	if (l == r && id != str[l] - 'A') return -1;
	if (visit[l][r][id]) return dp[l][r][id];
	visit[l][r][id] = true;
	for (int i = 0; i < vec[id].size(); i++) {
		for (int k = l; k < r; k++) {
			int a = dfs(l, k, vec[id][i].a);
			int b = dfs(k + 1, r, vec[id][i].b);
			if (a == -1 || b == -1) continue;
			check_min(dp[l][r][id], a + b + vec[id][i].c);
		}
	}
	return dp[l][r][id];
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		for (int i = 0; i < N; i++) vec[i].clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			int id = str[0] - 'A';
			Node node;
			node.read();
			vec[id].push_back(node);
		}
		printf("CASE #%d\n", Case++);
		for (int i = 0; i < q; i++) {
			int len;
			scanf("%d%s", &len, str);
			for (int i = 0; i < len; i++) str[i] = toupper(str[i]);
			memset(dp, -1, sizeof(dp));
			memset(visit, false, sizeof(visit));
			int ans = dfs(0, len - 1, 0);
			if (ans == -1) {
				puts("IMPOSSIBLE");
			} else {
				ans += len;
				printf("POSSIBLE WITH %d DIAMONDS\n", ans);
			}
		}
	}
	return 0;
}
