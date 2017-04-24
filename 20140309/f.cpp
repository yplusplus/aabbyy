#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
const int N = 5;
const int base = 16;
int marble[N][N];
int hole[N][N];
int can[N][N][N][N];
int n, m, wall;
map<pair<ull, ull>, int> visit;

struct State {
	int sx, tx;
	int sy, ty;
	int xstep, ystep;
	State(int sx, int tx, int sy, int ty, int xstep, int ystep) : sx(sx), tx(tx), sy(sy), ty(ty), xstep(xstep), ystep(ystep) {}
};

bool inmat(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }

bool is_valid(int marble[N][N], int hole[N][N]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (marble[i][j] && hole[i][j] && marble[i][j] != hole[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void encode(int marble[N][N], ull &hash_value) {
	hash_value = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			hash_value <<= 4;
			hash_value |= marble[i][j];
		}
	}
}

void decode(int marble[N][N], ull hash_value) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			marble[i][j] = hash_value & (base - 1);
			hash_value >>= 4;
		}
	}
}

void handle(int marble[N][N], int hole[N][N]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (marble[i][j] && hole[i][j]) {
				assert(marble[i][j] == hole[i][j]);
				marble[i][j] = 0;
				hole[i][j] = 0;
			}
		}
	}
}

State get_state(int k) {
	assert(k >= 0 && k <= 3);
	if (k == 0) return State(0, n, n - 1, -1, 1, -1);//right
	if (k == 1) return State(0, n, 0, n, 1, 1);//left
	if (k == 2) return State(n - 1, -1, 0, n, -1, 1);//down
	if (k == 3) return State(0, n, 0, n, 1, 1);//up
}

int ma[N][N], ho[N][N];
int nma[N][N], nho[N][N];
queue<ull> que;

bool update(ull m1, ull m2, int w) {
	if (!visit.count(make_pair(m1, m2))) {
		visit[make_pair(m1, m2)] = w;
		que.push(m1);
		que.push(m2);
		return true;
	}
}

int solve() {
	if (!is_valid(marble, hole)) return -1;
	if (m == n * n) return 0;
	ull ma_hash, ho_hash, nma_hash, nho_hash;
	memcpy(ma, marble, sizeof(marble));
	memcpy(ho, hole, sizeof(hole));
	handle(ma, ho);
	encode(ma, ma_hash);
	encode(ho, ho_hash);
	update(ma_hash, ho_hash, 0);
	int cnt = 0;
	while (!que.empty()) {
		ma_hash = que.front(); que.pop();
		ho_hash = que.front(); que.pop();
		decode(ma, ma_hash);
		for (int k = 0; k < 4; k++) {
			memset(nma, 0, sizeof(nma));
			decode(nho, ho_hash);
			State state = get_state(k);
			for (int i = state.sx; i != state.tx; i += state.xstep) {
				for (int j = state.sy; j != state.ty; j += state.ystep) {
					if (ma[i][j]) {
						int ii = i, jj = j;
						bool found = false;
						for (int l = 1; l < n; l++) {
							int x = ii + dx[k], y = jj + dy[k];
							if (inmat(x, y) && can[ii][jj][x][y] && nma[x][y] == 0) {
								ii = x, jj = y;
								if (nho[ii][jj]) {
									if (nho[ii][jj] != ma[i][j]) goto fail;
									nho[ii][jj] = nma[ii][jj] = 0;
									found = true;
									break;
								}
							} else {
								break;
							}
						}
						if (!found) nma[ii][jj] = ma[i][j];
					}
				}
			}
			handle(nma, nho);
			encode(nma, nma_hash);
			encode(nho, nho_hash);
			update(nma_hash, nho_hash, visit[make_pair(ma_hash, ho_hash)] + 1);
fail: ;
		}
	}
	if (visit.count(make_pair(0, 0))) return visit[make_pair(0, 0)];
	return -1;
}

int main() {
	int Case = 1;
	while (~scanf("%d%d%d", &n, &m, &wall), n + m + wall) {
		memset(marble, 0, sizeof(marble));
		memset(hole, 0, sizeof(hole));
		memset(can, true, sizeof(can));
		visit.clear();
		bool found = false;
		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (marble[a][b]) found = true;
			marble[a][b] = i;
		}
		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (hole[a][b]) found = true;
			hole[a][b] = i;
		}
		for (int i = 0; i < wall; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			can[a][b][c][d] = false;
			can[c][d][a][b] = false;
		}
		int ans = -1;
		if (!found) ans = solve();
		printf("Case %d: ", Case++);
		if (ans == -1) { puts("impossible"); }
		else printf("%d moves\n", ans);
		puts("");
	}
	return 0;
}
