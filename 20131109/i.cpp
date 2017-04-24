#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int B = 21;
const int G = 8;
const int inf = 1 << 28;
int b, g, s;
int dp[1 << B];
int bag[B][G];
int sum[1 << B][G];
bool visit[1 << B];
int all;
int dfs(int mask) {
	if (mask == all) return 0;
	if (visit[mask]) return dp[mask];
	visit[mask] = true;
	int t = -inf;
	for (int i = 0; i < b; i++) {
		if (~mask >> i & 1) {
			int res = 0;
			for (int j = 0; j < g; j++) {
				res += (sum[mask][j] + bag[i][j]) / s;
			}
			if (res) t = max(t, res + dfs(mask | (1 << i)));
			else t = max(t, -dfs(mask | (1 << i)));
		}
	}
	return dp[mask] = t;
}

int main() {
	while (~scanf("%d%d%d", &g, &b, &s), g + b + s) {
		all = (1 << b) - 1;
		for (int i = 0; i < b; i++) {
			memset(bag[i], 0, sizeof(bag[i]));
			int cnt, x;
			scanf("%d", &cnt);
			for (int j = 0; j < cnt; j++) {
				scanf("%d", &x);
				x--;
				bag[i][x]++;
			}
		}
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i < (1 << b); i++) {
			for (int j = 0; j < b; j++) {
				if (i >> j & 1) {
					for (int k = 0; k < g; k++) {
						sum[i][k] += bag[j][k];
						sum[i][k] %= s;
					}
				}
			}
		}
		memset(visit, false, sizeof(visit));
		int ans = dfs(0);
		printf("%d\n", ans);
	}
	return 0;
}
