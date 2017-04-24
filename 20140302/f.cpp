#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
typedef pair<DB, int> Node;
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline DB pt2line(const Point &p, const Point &a, const Point &b) { return fabs(cross(a - p, b - p) / veclen(a - b)); }

const DB EPS = 1e-10;
const DB PI = acos(-1.0);
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

typedef vector<Point> VP;
typedef vector<Node> VN;
void andrew(VP &pt, VP &ch) {
	int m = 0, n = pt.size();
	ch.resize(n + 1);
	sort(pt.begin(), pt.end());
	for (int i = 0; i < n; ++i) {
		while (m > 1 && sgn(cross(pt[i] - ch[m - 1], ch[m - 1] - ch[m - 2])) <= 0) --m;
		ch[m++] = pt[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; --i) {
		while (m > k && sgn(cross(pt[i] - ch[m - 1], ch[m - 1] - ch[m - 2])) <= 0) --m;
		ch[m++] = pt[i];
	}
	if (n) --m;
	ch.resize(m);
}

DB work(VP &pt) {
	VP ch;
	andrew(pt, ch);
	DB ans = 0;
	int n = pt.size(), m = ch.size();
	//for (int i = 0; i < m; ++i) cout << ch[i].x << " && " << ch[i].y << endl;
	//for (int i = 0; i < n; ++i) cout << pt[i].x << " || " << pt[i].y << endl;
	ch.push_back(ch[0]);
	VN node(m);
	for (int i = 0; i < m; ++i) node[i] = Node(angle(ch[i + 1] - ch[i]), i + 1);
	//for (int i = 0; i <= m + 1; ++i) cout << node[i].x << ' ' << node[i].y << endl;
	sort(node.begin(), node.end());
	node.push_back(Node(node[m - 1].x - PI * 2, node[m - 1].y));
	node.push_back(Node(node[0].x + PI * 2, node[0].y));
	sort(node.begin(), node.end());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			int p;
			p = lower_bound(node.begin(), node.end(), Node(angle(pt[i] - pt[j]), 0)) - node.begin();
			ans = max(pt2line(ch[node[p].y], pt[i], pt[j]), ans);
			p = lower_bound(node.begin(), node.end(), Node(angle(pt[j] - pt[i]), 0)) - node.begin();
			ans = max(pt2line(ch[node[p].y], pt[i], pt[j]), ans);
		}
	}
	return ans;
}

int run() {
	int n;
	while (cin >> n) {
		VP pt(n);
		for (int i = 0; i < n; ++i) cin >> pt[i].x >> pt[i].y;
		cout << work(pt) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_f", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
