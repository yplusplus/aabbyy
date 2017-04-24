#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const int N = 111;
int n, m;
char maz[N][N];
int dist[2][N][N];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
vector<pii> teleport[30];

bool check(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < m && maz[x][y] != '#' && maz[x][y] != '*');
}

void bfs(pii st, int offset) {
	queue<pii> que;
	memset(dist[offset], -1, sizeof(dist[offset]));
	dist[offset][st.fi][st.se] = 0;
	que.push(st);
	//cout << st.fi << " " << st.se << endl;
	while (!que.empty()) {
		pii now = que.front();
		que.pop();
		int x = now.fi, y = now.se;
		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (check(nx, ny) && dist[offset][nx][ny] == -1) {
				if (isupper(maz[nx][ny])) {
					int type = maz[nx][ny] - 'A';
					for (int i = 0; i < teleport[type].size(); i++) {
						int xx = teleport[type][i].fi;
						int yy = teleport[type][i].se;
						dist[offset][xx][yy] = dist[offset][x][y] + 1;
						que.push(mp(xx, yy));
					}
				} else {
					dist[offset][nx][ny] = dist[offset][x][y] + 1;
					que.push(mp(nx, ny));
					//cout  << nx << " " << ny << endl;
				}
			}
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		int ax, ay, bx, by, cx, cy;
		for (int i = 0; i < 30; i++) teleport[i].clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", maz[i]);
			for (int j = 0; j < m; j++) {
				if (maz[i][j] == '!') ax = i, ay = j;
				if (maz[i][j] == '$') bx = i, by = j;
				if (maz[i][j] == '*') cx = i, cy = j;
				if (isupper(maz[i][j])) { teleport[maz[i][j] - 'A'].pb(mp(i, j)); }
			}
		}
		//cout << ax << " " << ay << endl;
		//cout << bx << " " << by << endl;
		//cout << cx << " " << cy << endl;

		bfs(mp(ax, ay), 0);
		bfs(mp(bx, by), 1);
		/*
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m; k++) {
					cout << dist[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		*/
		int ans = 1 << 30;
		for (int i = 0; i < 8; i++) {
			int x = cx + dx[i], y = cy + dy[i];
			if (!check(x, y)) continue;
			if (dist[0][x][y] == -1 || dist[1][x][y] == -1) continue;
			int t = max(dist[0][x][y], dist[1][x][y]);
			ans = min(ans, t);
		}
		ans++;
		if (ans == (1 << 30) + 1) puts("Impossible");
		else cout << ans << endl;
	}
	return 0;
}

