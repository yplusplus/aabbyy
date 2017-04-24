#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
const int N = 22;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool visit[N][N];
char board[N][N];
int cnt[N], ans[N];;
vector<pair<int, int> > bag;
int n;

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}

void find_color(int x, int y, char origin) {
	cnt[origin - '0']++;
	visit[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (!check(nx, ny) || visit[nx][ny]) continue;
		char color = board[nx][ny];
		if (color == origin) find_color(nx, ny, origin);
	}
}
void dfs(int x, int y, char origin) {
	bag.push_back(MP(x, y));
	visit[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (!check(nx, ny) || visit[nx][ny]) continue;
		char color = board[nx][ny];
		if (color == origin) dfs(nx, ny, origin);
		else find_color(nx, ny, color);
	}
}

void solve() {
	memset(ans, 0, sizeof(ans));
	int times = 0;
	while (1) {
		memset(visit, false, sizeof(visit));
		memset(cnt, 0, sizeof(cnt));
		bag.clear();
		dfs(0, 0, board[0][0]);
		int id = 0;
		for (int i = 1; i <= 6; i++) {
			if (cnt[id] < cnt[i]) id = i;
		}
		if (id == 0) break;
		//cout << id << endl;
		times++;
		ans[id]++;
		for (int i = 0; i < bag.size(); i++) {
			board[bag[i].first][bag[i].second] = id + '0';
		}
	}
	printf("%d\n", times);
	for (int i = 1; i <= 6; i++) {
		printf("%d%c", ans[i], i == 6 ? '\n' : ' ');
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%s", board[i]);
		solve();
	}
	return 0;
}
