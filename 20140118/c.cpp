#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

int target[5];
const int N = 14;
double dp[N][N][N][N][5][5];
bool visit[N][N][N][N][5][5];

bool check(int now[]) {
	for (int i = 1; i <= 4; i++) {
		if (now[i] < target[i]) return false;
	}
	return true;
}

double dfs(int a, int b, int c, int d, int e, int f) {
	int now[5] = {0, a, b, c, d};
	if (e) now[e]++; if (f) now[f]++;
	if (check(now)) return 0.0;
	if (visit[a][b][c][d][e][f]) return dp[a][b][c][d][e][f];
	visit[a][b][c][d][e][f] = true;
	int sum = 0;
	for (int i = 1; i <= 4; i++) { sum += now[i]; }
	double left = 54 - sum;
	double res = 0;
	if (a < 13) { res += (13 - a) * (dfs(a + 1, b, c, d, e, f)); }
	if (b < 13) { res += (13 - b) * (dfs(a, b + 1, c, d, e, f)); }
	if (c < 13) { res += (13 - c) * (dfs(a, b, c + 1, d, e, f)); }
	if (d < 13) { res += (13 - d) * (dfs(a, b, c, d + 1, e, f)); }
	if (!e) {
		double tmp = 54.0;
		for (int i = 1; i <= 4; i++) { tmp = min(tmp, dfs(a, b, c, d, i, f)); }
		res += tmp;
	}
	if (!f) {
		double tmp = 54.0;
		for (int i = 1; i <= 4; i++) { tmp = min(tmp, dfs(a, b, c, d, e, i)); }
		res += tmp;
	}
	res = res / left + 1.0;
	return dp[a][b][c][d][e][f] = res;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		int sum = 0;
		for (int i = 1; i <= 4; i++) {
			scanf("%d", &target[i]);
			sum += target[i];
		}
		printf("Case %d: ", Case++);
		int cnt = 0;
		for (int i = 1; i <= 4; i++) {
			if (target[i] > 13) cnt += target[i] - 13;
		}
		if (sum > 54 || cnt > 2) {
			puts("-1.000");
		} else {
			memset(visit, false, sizeof(visit));
			double ans = dfs(0, 0, 0, 0, 0, 0);
			printf("%.3f\n", ans);
		}
	}
	return 0;
}
