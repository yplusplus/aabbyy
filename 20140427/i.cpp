#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
typedef pair<int, int> pii;
#define x first
#define y second
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	void read() { scanf("%d%d", &x, &y); }
	bool operator< (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator== (const Point &p) const {
		return x == p.x && y == p.y;
	}
	bool operator!= (const Point &p) const {
		return !(*this == p);
	}
	void output() {
		printf("(%d, %d)\n", x, y);
	}
} point[N];

int n;
vector<int> vec[4];
set<Point> st[4][N];
typedef set<Point>::iterator spit;

// heng
// shu
// zhu xie
// fu xie

int get_type(const Point &a, const Point &b) {
	if (a.y == b.y) return 0;
	if (a.x == b.x) return 1;
	if (a.y - a.x == b.y - b.x) return 2;
	if (a.y + a.x == b.y + b.x) return 3;
	return -1;
}

int get_hash(const Point &a, int type) {
	if (type == 0) return a.y;
	if (type == 1) return a.x;
	if (type == 2) return a.y - a.x;
	return a.y + a.x;
}

void add(const Point &a) {
	for (int i = 0; i < 4; i++) {
		int pos = lower_bound(vec[i].begin(), vec[i].end(), get_hash(a, i)) - vec[i].begin();
		st[i][pos].insert(a);
		//cout << i << endl;
	}
}

void remove(const Point &a) {
	for (int i = 0; i < 4; i++) {
		int pos = lower_bound(vec[i].begin(), vec[i].end(), get_hash(a, i)) - vec[i].begin();
		st[i][pos].erase(a);
	}
}

void solve () {
	for (int i = 0; i < n; i++) {
		vec[0].push_back(point[i].y);
		vec[1].push_back(point[i].x);
		vec[2].push_back(point[i].y - point[i].x);
		vec[3].push_back(point[i].y + point[i].x);
	}
	for (int i = 0; i < 4; i++) {
		sort(vec[i].begin(), vec[i].end());
		vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
	}
	//cout << "ok" << endl;
	for (int i = 0; i < n; i++) {
		add(point[i]);
		//cout << i << endl;
	}
	//cout << "ok" << endl;
	Point now(0, 0);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int type = get_type(now, point[i]);
		if (type == -1) break;
		//cout << "***********" << endl;
		//cout << i << " " << type << endl;
		int pos = lower_bound(vec[type].begin(), vec[type].end(), get_hash(point[i], type)) - vec[type].begin();
		spit it = st[type][pos].lower_bound(now);
		if (point[i] < now) it--;
		//cout << it->x << " " << it->y << endl;
		if (*it != point[i]) {
			break;
		}
		ans++;
		now = point[i];
		remove(point[i]);
	}
	printf("%d\n", ans);
}

int main() {
	freopen("queen2.in", "r", stdin);
	freopen("queen2.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) { point[i].read(); }
	for (int j = 0; j < 4; j++) {
		vec[j].clear();
		for (int i = 0; i < n; i++) {
			st[j][i].clear();
		}
	}
	solve();
	return 0;
}
