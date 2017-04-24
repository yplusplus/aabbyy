#include <bits/stdc++.h>
using namespace std;

const int N = 33;
const int inf = 1 << 29;
int dp[N][N];
bool visit[N][N];
int n;
int a[N][N][N];
bool spfa_up() {
	queue<int> que;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = -inf;
		}
	}
	memset(visit, false, sizeof(visit));
	int x, y, z;
	que.push(0);
	que.push(0);
	dp[0][0] = 0;
	while (!que.empty()) {
		x = que.front(), que.pop();
		y = que.front(), que.pop();
		visit[x][y] = false;
		if (dp[x][y] + a[x][y][0] + a[y][0][0] > 0) return true;
		for (z = 0; z <= n; z++) {
			if (dp[y][z] < dp[x][y] + a[x][y][z] - z) {
				dp[y][z] = dp[x][y] + a[x][y][z] - z;
				if (!visit[y][z]) {
					visit[y][z] = true;
					que.push(y), que.push(z);
				}
			}
		}
	}
	return false;
}

bool spfa_down() {
	queue<int> que;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = -inf;
		}
	}
	memset(visit, false, sizeof(visit));
	int x, y, z;
	que.push(0);
	que.push(0);
	dp[0][0] = 0;
	while (!que.empty()) {
		x = que.front(), que.pop();
		y = que.front(), que.pop();
		visit[x][y] = false;
		if (dp[x][y] - a[x][y][0] - a[y][0][0] > 0) return true;
		for (z = 0; z <= n; z++) {
			if (dp[y][z] < dp[x][y] - a[x][y][z] + z) {
				dp[y][z] = dp[x][y] - a[x][y][z] + z;
				if (!visit[y][z]) {
					visit[y][z] = true;
					que.push(y), que.push(z);
				}
			}
		}
	}
	return false;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int y = 0; y <= n; y++) {
			for (int x = 0; x <= n; x++) {
				for (int z = 0; z <= n; z++) {
					scanf("%d", &a[x][y][z]);
				}
			}
		}
		bool up = spfa_up();
		bool down = spfa_down();

		if (up && down) puts("<>");
		else if (up) puts(">");
		else if (down) puts("<");
		else puts("=");
	}
	return 0;
}

