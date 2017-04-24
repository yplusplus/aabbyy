#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111;
const int INF = 0x77777777;
const int dx[4] = { 0, -1, 0, 1 };
const int dy[4] = { 1, 0, -1, 0 };

int n, m, k;
char mat[N][N];
int dis[6][N][N];
int X[6], Y[6], id[6];

inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

void find(int &x, int &y) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == '@') {
				x = i; y = j;
				return ;
			}
		}
	}
}

int qx[N * N], qy[N * N];
void get_mat(int k) {
	memset(dis[k], -1, sizeof(dis[k]));
	int x, y, nx, ny;
	int qh, qt;
	qh = qt = 0;
	qx[qt] = X[k]; qy[qt] = Y[k]; qt++;
	dis[k][X[k]][Y[k]] = 0;
	while (qh < qt) {
		int x = qx[qh], y = qy[qh];
		qh++;
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i]; ny = y + dy[i];
			if (!inmat(nx, ny)) continue;
			if (mat[nx][ny] == '#') continue;
			if (dis[k][nx][ny] != -1) continue;
			dis[k][nx][ny] = dis[k][x][y] + 1;
			qx[qt] = nx; qy[qt] = ny; qt++;
		}
	}
}

int cal() {
	int sum = 0;
	for (int i = 1; i <= k; i++) {
		int a = id[i - 1], b = id[i];
		if (dis[a][X[b]][Y[b]] == -1) return INF;
		sum += dis[a][X[b]][Y[b]];
	}
	return sum;
}

void print(int k) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dis[k][i][j] << ' ';
		}
		cout << endl;
	}
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	while (cin >> n >> m && (n || m)) {
		for (int i = 0; i < n; i++) cin >> mat[i];
		cin >> k;
		for (int i = 1; i <= k; i++) {
			cin >> X[i] >> Y[i];
			X[i]--; Y[i]--;
		}
		find(X[0], Y[0]);
		for (int i = 0; i <= k; i++) get_mat(i);
		//for (int i = 0; i <= k; i++) print(i);
		for (int i = 0; i <= k; i++) id[i] = i;
		int ans = INF;
		do {
			ans = min(cal(), ans);
		} while (next_permutation(id + 1, id + k + 1));
		cout << (ans == INF ? -1 : ans) << endl;
	}
	return 0;
}
