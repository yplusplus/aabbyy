#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
const int N = 7;
char board[N][N];
int n, m;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

void output(char board[N][N]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			putchar(board[i][j]);
		}
		cout << endl;
	}
}

bool dfs(char board[N][N]) {
	//cout << "**************" << endl;
	//output(board);
	//getchar();
	//getchar();
	pair<int, int> que[17];
	int tail, nx, ny;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'x') continue;
			for (int k = 0; k < 4; k++) {
				tail = 0;
				nx = i, ny = j;
				int cnt = 0;
				while (check(nx, ny) && board[nx][ny] == 'e') {
					cnt++;
					que[tail++] = MP(nx, ny);
					nx += dx[k], ny += dy[k];
				}
				if (!check(nx, ny) || cnt == 1) continue;
				for (int l = 0; l < tail; l++) {
					board[que[l].first][que[l].second] = 'x';
				}
				board[nx][ny] = 'e';
				bool ret = dfs(board);
				board[nx][ny] = 'x';
				for (int l = 0; l < tail; l++) {
					board[que[l].first][que[l].second] = 'e';
				}
				if (!ret) return true;
			}
		}
	}
	return false;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++) scanf("%s", board[i]);
		if (dfs(board)) {
			puts("Tewi first");
		} else {
			puts("Reisen first");
		}
	}
	return 0;
}
