#include <bits/stdc++.h>
using namespace std;

const int B = 22;
const int N = 555;
const int Q = 11111;
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { 1, 0, -1, 0 };
#define x first
#define y second
int n, m, mat[N][N];
bool vis[N][N];

struct Point {
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
} ;
bool operator < (const Point &a, const Point &b) { return mat[a.x][a.y] > mat[b.x][b.y]; }
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

void print_mat() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << mat[i][j] << ' ';
		cout << endl;
	}
}

void fix_mat() {
	priority_queue<Point> q;
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; i++) {
		q.push(Point(i, 0));
		q.push(Point(i, m - 1));
		vis[i][0] = vis[i][m - 1] = 1;
	}
	for (int i = 1; i < m - 1; i++) {
		q.push(Point(0, i));
		q.push(Point(n - 1, i));
		vis[0][i] = vis[n - 1][i] = 1;
	}
	int nx, ny;
	while (!q.empty()) {
		Point cur = q.top();
		q.pop();
		for (int i = 0; i < 4; i++) {
			nx = cur.x + dx[i], ny = cur.y + dy[i];
			if (!inmat(nx, ny)) continue;
			if (vis[nx][ny]) continue;
			mat[nx][ny] = max(mat[cur.x][cur.y], mat[nx][ny]);
			q.push(Point(nx, ny));
			vis[nx][ny] = 1;
		}
	}
	//print_mat();
}

struct Query {
	int d, A, id;
	Query() {}
	Query(int a, int b, int c) : d(a), A(b), id(c) {}
} qry[Q];
bool operator < (const Query &a, const Query &b) { return a.d > b.d; }
int ans[Q];

struct Node {
	int x, y, h;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), h(c) {}
} node[N * N];
bool operator < (const Node &a, const Node &b) { return a.h > b.h; }

inline int encode(int x, int y) { return x * m + y; }
struct MFS {
	int fa[N * N], cnt[N * N];
	void init(int n) { for (int i = 0; i < n; i++) fa[i] = i, cnt[i] = 0; }
	int find(int x) { return fa[x] == x ? x : find(fa[x]); }
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return ;
		fa[fx] = fy;
		cnt[fy] += cnt[fx];
	}
	int get_cnt(int x) { return cnt[find(x)]; }
	inline bool issame(int x, int y) { return find(x) == find(y); }
} mfs;

inline int lowbit(int x) { return x & -x; }
inline int cnt_bit(int x) { return x ? cnt_bit(x ^ lowbit(x)) + 1 : 0; }

struct Count {
	map<int, int> cnt;
	void init() { cnt.clear(); }
	inline void insert(int x) { cnt[x]++; }
	inline void erase(int x) { if (cnt[x] == 1) cnt.erase(x); else cnt[x]--; }
	int get_ans(int x) {
		int ans = 0;
		map<int, int>::iterator mi = cnt.begin();
		//cout << x << endl;
		while (mi != cnt.end()) {
			///cout << mi->x << ' ' << mi->y << endl;
			ans += mi->y << cnt_bit(mi->x & x);
			mi++;
		}
		return ans;
	}
} cnt;

void work() {
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) qry[i].id = i;
	for (int i = 0; i < k; i++) cin >> qry[i].d >> qry[i].A;
	sort(qry, qry + k);
	int tt = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) node[tt++] = Node(i, j, mat[i][j]);
	sort(node, node + tt);
	memset(vis, 0, sizeof vis);
	mfs.init(tt);
	cnt.init(); 
	int nx, ny;
	for (int i = 0, j = 0; i < k; i++) {
		Query &q = qry[i];
		//cout << q.d << ' ' << q.A << ' ' << q.id << endl;
		while (j < tt && node[j].h > q.d) {
			Node &nd = node[j];
			vis[nd.x][nd.y] = 1;
			int i1 = encode(nd.x, nd.y), i2;
			cnt.insert(++mfs.cnt[i1]);
			for (int d = 0; d < 4; d++) {
				nx = nd.x + dx[d], ny = nd.y + dy[d];
				i2 = encode(nx, ny);
				if (!inmat(nx, ny)) continue;
				if (!vis[nx][ny]) continue;
				if (mfs.issame(i1, i2)) continue;
				cnt.erase(mfs.get_cnt(i1));
				cnt.erase(mfs.get_cnt(i2));
				mfs.merge(i1, i2);
				cnt.insert(mfs.get_cnt(i1));
			}
			j++;
		}
		ans[q.id] = cnt.get_ans(q.A);
		//cout << "status: " << j << ' '; cnt.get_ans(0);
	}
	for (int i = 0; i < k; i++) cout << ans[i] << endl;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	while (cin >> n >> m) {
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> mat[i][j];
		fix_mat();
		work();
	}
	return 0;
}
