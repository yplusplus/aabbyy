#include <bits/stdc++.h>
using namespace std;

const int N = 222;
bool board[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};
char line[N][N];
int cycle[N * N];
int n, m;

int char2int(char ch) {
	if (isdigit(ch)) return ch - '0';
	return ch - 'a' + 10;
}

bool inmat(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

char int2char(int x) {
	if (x == 0) return 'W';
	if (x == 1) return 'A';
	if (x == 2) return 'K';
	if (x == 3) return 'J';
	if (x == 4) return 'S';
	if (x == 5) return 'D';
	assert(1 == 0);
}

int color[N][N];
int colors;

void dfs(int x, int y) {
	color[x][y] = colors;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (inmat(nx, ny) && board[nx][ny] && !color[nx][ny]) {
			dfs(nx, ny);
		}
	}
}

vector<int> vec;
void dfs2(int x, int y) {
	color[x][y] = -1;
	//if (vec.size() >= 2) return;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (!inmat(nx, ny)) {
			vec.push_back(0);
		} else if (board[nx][ny]) {
			vec.push_back(color[nx][ny]);
		} else {
			if (!color[nx][ny]) {
				dfs2(nx, ny);
			}
		}
	}
}

void solve() {
	memset(color, 0, sizeof(color));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x = char2int(line[i][j]);
			for (int k = 0; k < 4; k++) {
				int y = x >> (3 - k) & 1;
				board[i][j * 4 + k] = y;
			}
		}
	}
	m *= 4;
	/*
	cout << n << " " << m << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	*/
	colors = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 1 && color[i][j] == 0) {
				++colors;
				dfs(i, j);
			}
		}
	}
	//cout << colors << endl;
	memset(cycle, 0, sizeof(cycle));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!color[i][j] && !board[i][j]) {
				vec.clear();
				dfs2(i, j);
				sort(vec.begin(), vec.end());
				vec.erase(unique(vec.begin(), vec.end()), vec.end());
				//cout << i << " " << j << " " << vec.size() << endl;
				if (vec.size() == 1 && vec[0] > 0) {
					cycle[vec[0]]++;
				}
			}
		}
	}
	char ans[N * N];
	for (int i = 1; i <= colors; i++) {
		ans[i - 1] = int2char(cycle[i]);
	}
	ans[colors] = 0;
	if (colors) sort(ans, ans + colors);
	printf("%s\n", ans);
}

int main() {
	int Case = 1;
	while (~scanf("%d%d", &n, &m), n && m) {
		for (int i = 0; i < n; i++) scanf("%s", line[i]);
		printf("Case %d: ", Case++);
		solve();
	}
	return 0;
}
