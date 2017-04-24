#include <bits/stdc++.h>
using namespace std;

typedef vector<string> VS;
typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
#define x first
#define y second

const int N = 111;
const int M = N * N;
vector<PIII> candidate;
char mat[N][N];
int n, m, id[N][N];

struct MFS {
	int fa[M];
	void init(int n) { n++; for (int i = 0; i < n; i++) fa[i] = i; }
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return 0;
		fa[fx] = fy;
		return 1;
	}
} mfs;

const int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const int dy[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

void flood_fill(int x, int y, int z) {
	queue<int> qx, qy;
	int nx, ny;
	qx.push(x);
	qy.push(y);
	id[x][y] = z;
	while (!qx.empty()) {
		x = qx.front(); qx.pop();
		y = qy.front(); qy.pop();
		for (int i = 0; i < 8; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (!inmat(nx, ny)) continue;
			if ('#' != mat[nx][ny]) continue;
			if (-1 != id[nx][ny]) continue;
			qx.push(nx);
			qy.push(ny);
			id[nx][ny] = z;
		}
	}
}

void get_connect(int x, int y) {
	int nx, ny;
	for (int i = 1; i < n; i++) {
		nx = x + i;
		ny = y;
		if (!inmat(nx, ny)) break;
		if (inmat(nx, ny - 1) && '#' == mat[nx][ny - 1]) {
			if (id[nx][ny - 1] != id[x][y]) candidate.push_back(PIII(PII(id[nx][ny - 1], id[x][y]), i - 1));
		}
		if (inmat(nx, ny) && '#' == mat[nx][ny]) {
			if (id[nx][ny] != id[x][y]) candidate.push_back(PIII(PII(id[nx][ny], id[x][y]), i - 1));
		}
		if (inmat(nx, ny + 1) && '#' == mat[nx][ny + 1]) {
			if (id[nx][ny + 1] != id[x][y]) candidate.push_back(PIII(PII(id[nx][ny + 1], id[x][y]), i - 1));
		}
	}
	for (int i = 1; i < m; i++) {
		nx = x;
		ny = y + i;
		if (!inmat(nx, ny)) break;
		if (inmat(nx - 1, ny) && '#' == mat[nx - 1][ny]) {
			if (id[nx - 1][ny] != id[x][y]) candidate.push_back(PIII(PII(id[nx - 1][ny], id[x][y]), i - 1));
		}
		if (inmat(nx, ny) && '#' == mat[nx][ny]) {
			if (id[nx][ny] != id[x][y]) candidate.push_back(PIII(PII(id[nx][ny], id[x][y]), i - 1));
		}
		if (inmat(nx + 1, ny) && '#' == mat[nx + 1][ny]) {
			if (id[nx + 1][ny] != id[x][y]) candidate.push_back(PIII(PII(id[nx + 1][ny], id[x][y]), i - 1));
		}
	}
}

inline bool cmp(const PIII &a, const PIII &b) { return a.y < b.y; }
PIII work() {
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) id[i][j] = -1;
	int cc_cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ('#' == mat[i][j] && -1 == id[i][j]) flood_fill(i, j, cc_cnt++);
		}
	}
	//cout << cc_cnt << endl;
	//for (int i = 0; i < n; i++) {
		//for (int j = 0; j < m; j++) cout << id[i][j] << ' ';
		//cout << endl;
	//}
	PII bridge(0, 0);
	if (cc_cnt > 1) {
		candidate.clear();
		mfs.init(cc_cnt);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if ('#' == mat[i][j]) get_connect(i, j);
			}
		}
	} else cc_cnt = 1;
	sort(candidate.begin(), candidate.end(), cmp);
	int sz = candidate.size();
	for (int i = 0; i < sz; i++) {
		//cout << candidate[i].x.x << ' ' << candidate[i].x.y << ' ' << candidate[i].y << endl;
		if (mfs.merge(candidate[i].x.x, candidate[i].x.y)) {
			bridge.x++;
			bridge.y += candidate[i].y;
			cc_cnt--;
		}
	}
	if (cc_cnt > 1 && 0 == bridge.x) bridge.x = -1;
	return PIII(bridge, cc_cnt);
}

void output(const PIII &a) {
	if (-1 == a.x.x) cout << "No bridges are possible." << endl;
	else if (0 == a.x.x) cout << "No bridges are needed." << endl;
	else {
		if (1 == a.x.x) cout << a.x.x << " bridge of total length " << a.x.y << endl;
		else cout << a.x.x << " bridges of total length " << a.x.y << endl;
	}
	if (1 < a.y) cout << a.y << " disconnected groups" << endl;
}

int main() {
	//freopen("in", "r", stdin);
	int cas = 0;
	while (cin >> n >> m && (n || m)) {
		if (cas) cout << endl;
		for (int i = 0; i < n; i++) cin >> mat[i];
		PIII ans = work();
		cout << "City " << ++cas << endl;
		output(ans);
	}
	return 0;
}
