#include <bits/stdc++.h>
using namespace std;

const int N = 33;
const int M = 6;
char face[N][N][N];
int n;
int dx[] = {0, 0, 1, -1, 0, 0};
int dy[] = {-1, 1, 0, 0, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};
int pre[N][N][N];

bool inmat(int x, int y, int z) { return x >= 0 && x < n && y >= 0 && y < n && z >= 0 && z < n; }

bool check(int x, int y, int z) {
	int a, b;
	a = n - 1 - z, b = n - 1 - x;
	if (face[0][a][b] == 'X') return false;
	a = n - 1 - z, b = y;
	if (face[1][a][b] == 'X') return false;
	a = n - 1 - z, b = x;
	if (face[2][a][b] == 'X') return false;
	a = n - 1 - z, b = n - 1 - y;
	if (face[3][a][b] == 'X') return false;
	a = n - 1 - y, b = n - 1 - x;
	if (face[4][a][b] == 'X') return false;
	a = y, b = n - 1 - x;
	if (face[5][a][b] == 'X') return false;
	return true;
}

char action_name[] = {"FBLRUD"};

void solve() {
	queue<int> que;
	que.push(1); que.push(1); que.push(1);
	memset(pre, -1, sizeof(pre));
	pre[1][1][1] = 6;
	int x, y, z;
	while (!que.empty()) {
		x = que.front(); que.pop();
		y = que.front(); que.pop();
		z = que.front(); que.pop();
		//cout << x << " " << y << " " << z << endl;
		for (int i = 0; i < M; i++) {
			int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
			if (!inmat(nx, ny, nz) || !check(nx, ny, nz)) continue;
			if (pre[nx][ny][nz] != -1) continue;
			//cout << x << " " << y << " " << z << " -> " << nx << " " << ny << " " << nz << " " << action_name[i] << endl;
			pre[nx][ny][nz] = i;
			que.push(nx);
			que.push(ny);
			que.push(nz);
		}
	}
	x = y = z = n - 2;
	vector<int> steps;
	while (pre[x][y][z] != 6) {
		int id = pre[x][y][z];
		steps.push_back(action_name[id]);
		x += dx[id ^ 1];
		y += dy[id ^ 1];
		z += dz[id ^ 1];
	}
	reverse(steps.begin(), steps.end());
	for (int i = 0; i < steps.size(); i++) {
		putchar(steps[i]);
	}
	puts("");

}

int main() {
	while (~scanf("%d", &n), n) {
		char line[100];
		gets(line);
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < n; j++) gets(face[i][j]);
			//for (int j = 0; j < n; j++) { printf("%s", face[i][j]); cout << endl; }
		}
		solve();
	}
	return 0;
}
