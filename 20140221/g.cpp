#include <bits/stdc++.h>
using namespace std;

const int N = 111;
const int M = 1 << 4;
int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};
int board[N][N];
int mask[N][N];
int bits_count[M];

vector<pair<int, int> > vampire;
bool check(int x, int y) { return x >= 0 && x < N && y >= 0 && y < N; }

int get_dir(char ch) {
	if (ch == 'E') return 0;
	if (ch == 'N') return 1;
	if (ch == 'S') return 2;
	return 3;
}

string get_dir_name(int x) {
	if (x == 1) return "east";
	if (x == 2) return "north";
	if (x == 4) return "south";
	return "west";
}

void solve() {
	memset(mask, 0, sizeof(mask));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == -1 || board[i][j] == 4) continue;
			//cout << i << " " << j << endl;
			//for (int k = 0; k < 4; k++) {
			int k = board[i][j];
				int x = i + dx[k], y = j + dy[k];
				while (check(x, y) && board[x][y] == -1) {
					mask[x][y] |= 1 << (3 - k);
					x += dx[k], y += dy[k];
				}
			//}
		}
	}
	vector<pair<int, int> > vv;
	for (int i = 0; i < vampire.size(); i++) {
		int x = vampire[i].first, y = vampire[i].second;
		if (mask[x][y]) {
			//cout << i << " " << mask[x][y] << endl;
			vv.push_back(make_pair(i + 1, mask[x][y]));
		}
	}
	//cout << "ok" << endl;
	if (vv.empty()) {
		puts("none");
	} else {
		for (int i = 0; i < vv.size(); i++) {
			printf("vampire %d", vv[i].first);
			for (int j = 0; j < 4; j++) {
				if (vv[i].second >> j & 1) {
					printf(" %s", get_dir_name(1 << j).c_str());
				}
			}
			puts("");
		}
	}
}

int main() {
	//bits_count[0] = 0; for (int i = 1; i < M; i++) { bits_count[i] = bits_count[i >> 1] + (i & 1); }
	int v, o, m;
	int Case = 1;
	while (~scanf("%d%d%d", &v, &o, &m), v + o + m) {
		memset(board, -1, sizeof(board));
		vampire.clear();
		int x, y;
		for (int i = 0; i < v; i++) {
			scanf("%d%d", &x, &y);
			vampire.push_back(make_pair(x, y));
		}
		for (int i = 0; i < o; i++) {
			scanf("%d%d", &x, &y);
			board[x][y] = 4;
		}
		for (int i = 0; i < m; i++) {
			char str[10];
			int x1, x2, y1, y2;
			scanf("%s%d%d%d%d", str, &x1, &y1, &x2, &y2);
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			int dir = get_dir(str[0]);
			for (int ii = x1; ii <= x2; ii++) {
				for (int jj = y1; jj <= y2; jj++) {
					board[ii][jj] = dir;
				}
			}
		}
		printf("Case %d:\n", Case++);
		solve();
	}
	return 0;
}
