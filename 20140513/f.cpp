#include <bits/stdc++.h>
using namespace std;

typedef vector<int> Point;
const int N = 1 << 14;
struct MFS {
	int fa[N], cnt;
	void init() { cnt = 0; for (int i = 0; i < N; ++i) fa[i] = i; };
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	void merge(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (fx == fy) return ;
		++cnt;
		fa[fx] = fy;
	}
} mfs;

map<Point, int> id;
void init() {
	id.clear();
	mfs.init();
}

inline int getID(const Point &a) {
	if (id.find(a) == id.end()) id[a] = id.size();
	return id[a];
}

int run() {
	int n;
	while (cin >> n) {
		init();
		vector<Point> pts(3, Point(3));
		set<pair<Point, Point> > edge;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					cin >> pts[j][k];
				}
			}
			sort(pts.begin(), pts.end());
			for (int j = 0; j < 3; ++j) {
				for (int k = j + 1; k < 3; ++k) {
					edge.insert(make_pair(pts[j], pts[k]));
					mfs.merge(getID(pts[j]), getID(pts[k]));
				}
			}
		}
		cout << ((edge.size() - id.size() - n + 2) >> 1) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("genus.in", "r", stdin);
	freopen("genus.out", "w", stdout);
	return run();
}
