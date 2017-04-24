#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 55;
const int dx[4] = { 0, -1, 0, 1 };
const int dy[4] = { 1, 0, -1, 0 };
int n, m;
char mat[N][N], cpy[N][N];
const char *p = "BGRWY";

inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

bool find(char c) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (mat[i][j] == c) return 1;
	}
	return 0;
}

bool vis[N][N];
int sx[N * N], sy[N * N];
int qx[N * N], qy[N * N];
int bfs(int x, int y, char to) {
	int top = -1, qh, qt;
	qh = qt = 0;
	qx[qt] = x; qy[qt++] = y;
	sx[++top] = x; sy[top] = y;
	vis[x][y] = 1;
	int c = 0, nx, ny;
	while (qh < qt) {
		x = qx[qh]; y = qy[qh++];
		c++;
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i]; ny = y + dy[i];
			if (!inmat(nx, ny)) continue;
			if (vis[nx][ny]) continue;
			if (mat[x][y] != mat[nx][ny]) continue;
			qx[qt] = nx; qy[qt++] = ny;
			sx[++top] = nx; sy[top] = ny;
			vis[nx][ny] = 1;
		}
		mat[x][y] = to;
	}
	while (~top) {
		vis[sx[top]][sy[top]] = 0;
		top--;
	}
	return c;
}

void fix() {
	int p, q = 0, mx = 0;
	for (int i = 0; i < m; i++) {
		p = 0;
		for (int j = 0; j < n; j++) {
			if (mat[j][i] != ' ') {
				swap(mat[j][i], mat[p][i]);
				p++;
			}
		}
		mx = max(p, mx);
		if (p) {
			for (int j = 0; j < n; j++) {
				swap(mat[j][i], mat[j][q]);
			}
			q++;
		}
	}
	n = mx; m = q;
}

bool find_other(char c, int &x, int &y) {
	x = -1; y = -1;
	int mx = 0, t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i && mat[i - 1][j] == mat[i][j]) continue;
			if (j && mat[i][j - 1] == mat[i][j]) continue;
			if (mat[i][j] != ' ' && mat[i][j] != c) {
				t = bfs(i, j, mat[i][j]);
				if (mx < t) {
					mx = t;
					x = i; y = j;
				}
			}
		}
	}
	return mx >= 2;
}

bool find_this(char c, int &x, int &y) {
	x = -1; y = -1;
	int mx = 0, t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i && mat[i - 1][j] == mat[i][j]) continue;
			if (j && mat[i][j - 1] == mat[i][j]) continue;
			if (mat[i][j] == c) {
				t = bfs(i, j, mat[i][j]);
				if (mx < t) {
					mx = t;
					x = i; y = j;
				}
			}
		}
	}
	return mx >= 2;
}

void print() {
	cout << "~~~~~~~~~~~~~~~" << endl;
	for (int i = n - 1; i >= 0; i--) cout << mat[i] << endl;
	cout << "~~~~~ end ~~~~~" << endl;
}

int work(char c) {
	int score = 0;
	int x, y;
	while (1) {
		if (find_other(c, x, y)) {
			//cout << x << ' ' << y << ' ' << mat[x][y];
			int s = bfs(x, y, ' ');
			score += s * (s - 1);
			//cout << ' ' << s << endl;
		} else if (find_this(c, x, y)) {
			int s = bfs(x, y, ' ');
			score += s * (s - 1);
			//cout << x << ' ' << y << ' ' << c << ' ' << s << endl;
		} else break;
		fix();
		//print();
		//cout << "cur-score " << score << endl;
	}
	return score;
}

void test() {
	for (int j = 0; j < n; j++) strcpy(mat[j], cpy[j]);
	print();
	cout << bfs(0, 2, ' ') << endl;
	print();
	fix();
	print();
}

int main() {
	//freopen("in", "r", stdin);
	while (~scanf("%d%d", &n, &m)) {
		int a = n, b = m;
		memset(vis, 0, sizeof(vis));
		for (int i = n - 1; i >= 0; i--) scanf("%s", cpy[i]);
		//test();
		for (int i = 0; i < 5; i++) {
			n = a, m = b;
			for (int j = 0; j < n; j++) strcpy(mat[j], cpy[j]);
			if (find(p[i])) printf("%c: %d\n", p[i], work(p[i]));
		}
	}
	return 0;
}




