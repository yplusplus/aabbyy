#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef vector<DB> VDB;
typedef vector<VDB> VVDB;
typedef vector<int> VI;
struct Point {
	DB x, y, z;
	Point() {}
	Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
} ;
istream &operator >> (istream &in, Point &pt) { return in >> pt.x >> pt.y >> pt.z; }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y, a.z + b.z); }
Point operator * (const Point &a, const DB &p) {return Point(a.x * p, a.y * p, a.z * p); }
template <class T> inline T sqr(const T &a) { return a * a; }
inline DB getDist(const Point &a, const Point &b) { return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z); }
vector<Point> location, velocity;
int n;

const int N = 50;
const DB UPPER = 1e8;
const DB EPS = 5e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

struct Map {
	bool visit[N][N];
	Map() { memset(visit, 0, sizeof visit); }
	void clear() { memset(visit, 0, sizeof visit); }
	void show() {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cout << visit[i][j];
			}
			cout << endl;
		}
	}
} ;
bool operator == (const Map &a, const Map &b) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (a.visit[i][j] == b.visit[i][j]) continue;
			return 0;
		}
	}
	return 1;
}

Map getMap(const DB &t) {
	Map temp;
	vector<Point> current(n);
	for (int i = 0; i < n; ++i) {
		current[i] = location[i] + velocity[i] * t;
	}
	VVDB dist(n, VDB(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			dist[i][j] = getDist(current[i], current[j]);
		}
	}
	VDB best(n);
	VI pre(n);
	for (int i = 0; i < n; ++i) {
		pre[i] = 0;
		best[i] = dist[0][i];
	}
	for (int t = 1; t < n; ++t) {
		DB minDist = DBL_MAX;
		int id = 0;
		for (int i = 1; i < n; ++i) {
			if (pre[i] == -1) continue;
			if (minDist > best[i]) {
				minDist = best[i];
				id = i;
			}
		}
		temp.visit[pre[id]][id] = temp.visit[id][pre[id]] = 1;
		pre[id] = -1;
		for (int i = 0; i < n; ++i) {
			if (pre[i] == -1) continue;
			if (best[i] > dist[id][i]) {
				best[i] = dist[id][i];
				pre[i] = id;
			}
		}
	}
	return temp;
}

int solve(const DB &l, const DB &r) {
	Map ml = getMap(l);
	Map mr = getMap(r);
	if (ml == mr) return 0;
	if (sgn(r - l) == 0) return 1;
	DB m = (l + r) / 2;
	return solve(l, m) + solve(m, r);
}

int run() {
	int cas = 0;
	while (cin >> n) {
		location.resize(n);
		velocity.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> location[i] >> velocity[i];
		}
		assert(getMap(UPPER / 2) == getMap(UPPER));
		cout << "Case " << ++cas << ": " << (solve(0, UPPER) + 1) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_a", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
