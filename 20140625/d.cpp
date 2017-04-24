#include <bits/stdc++.h>
using namespace std;

const int N = 30;
int dp[N][N];
int n;
vector<int> choice[N];

inline int lowbit(int x) { return x & (-x); }
inline int char2int(char ch) { return ch - 'a'; }
inline int str2int(char *str) {
	int res = 0;
	while (*str) {
		res += 1 << char2int(*str);
		str++;
	}
	return res;
}

map<int, int> mp;

void handle(int target) {
	int mask = 1 << target;
	dp[target][target] = 0;
	for (int step = 1; ; step++) {
		int now = (~mask & ((1 << n) - 1));
		int nmask = mask;
		int u;
		while (now) {
			u = lowbit(now);
			now -= u;
			int v = mp[u];
			bool found = false;
			for (int i = 0; i < choice[v].size(); i++) {
				if ((choice[v][i] & mask) == choice[v][i]) {
					found = true;
					break;
				}
			}
			if (found) {
				nmask |= u;
				dp[v][target] = step;
			}
		}
		if (mask == nmask) break;
		mask = nmask;
	}
}

void solve2() {
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++) {
		handle(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d%c", dp[i][j], j == n - 1 ? '\n' : ' ');
		}
	}
}
char str[N];
int main() {
	for (int i = 0; i < N; i++) { mp[1 << i] = i; }
	while (~scanf("%d", &n)) {
		for (int i = 0; i < N; i++) choice[i].clear();
		for (int i = 0; i < n; i++) {
			int k;
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				scanf("%s", str);
				int res = str2int(str);
				if (res >> i & 1) continue;
				choice[i].push_back(res);
			}
		}
		solve2();
	}
	return 0;
}
