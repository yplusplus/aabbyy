#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 16;
typedef long long LL;
#define x first
#define y second
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
} ;
typedef pair<int, Point> Node;
typedef vector<Point> VP;
typedef vector<Node> VN;
bool operator < (const Point &a, const Point &b) { return a.x < b.x; }
bool operator == (const Point &a, const Point &b) { return a.x == b.x; }

VP points;
VN nodes(N);
set<Point> segments;

void work(VN &nodes, LL &black, LL &white, int nodeSize) {
	segments.clear();
	black = white = 0;
	LL cntBlack = 0, cntWhite = 0, sum;
	int last = nodes[0].x;
	sort(nodes.begin(), nodes.begin() + nodeSize);
	set<Point>::iterator before, after;
	for (int i = 0, current; i < nodeSize; ) {
		current = nodes[i].x;
		int d = current - last;
		sum = (cntBlack + cntWhite) * (d >> 1);
		black += sum;
		white += sum;
		if (d & 1) {
			if (last & 1) {
				black += cntWhite;
				white += cntBlack;
			} else {
				black += cntBlack;
				white += cntWhite;
			}
		}
		//cout << last << ' ' << current << ' ' << cntBlack << ' ' << cntWhite << ' ' << black << ' ' << white << endl;
		while (i < nodeSize && current == nodes[i].x) {
			Point &temp = nodes[i].y;
			//cout << i << ' ' << temp.x << ' ' << temp.y << endl;
			int d = temp.y - temp.x;
			before = after = segments.upper_bound(temp);
			if (before != segments.begin()) --before;
			if (after == segments.begin() || before->y <= temp.x) {
				if (temp.x & 1) {
					cntBlack += d >> 1;
					cntWhite += d - (d >> 1);
				} else {
					cntWhite += d >> 1;
					cntBlack += d - (d >> 1);
				}
				if (after != segments.end()) {
					if (temp.y == after->x) {
						temp.y = after->y;
						segments.erase(after);
					}
				}
				if (after != segments.begin()) {
					if (temp.x == before->y) {
						temp.x = before->x;
						segments.erase(before);
					}
				}
				segments.insert(temp);
			} else {
				int l, r;
				Point cur = *before;
				segments.erase(before);
				l = cur.x;
				r = temp.x;
				if (r - l > 0) segments.insert(Point(l, r));
				l = temp.y;
				r = cur.y;
				if (r - l > 0) segments.insert(Point(l, r));
				if (temp.x & 1) {
					cntBlack -= d >> 1;
					cntWhite -= d - (d >> 1);
				} else {
					cntWhite -= d >> 1;
					cntBlack -= d - (d >> 1);
				}
			}
			++i;
		}
		last = current;
	}
}

int run() {
	int n, tt;
	while (cin >> n) {
		points.resize(n + 1);
		for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;
		points[n] = points[0];
		tt = 0;
		for (int i = 0; i < n; ++i) {
			if (points[i].y == points[i + 1].y) {
				if (points[i].x <= points[i + 1].x) nodes[tt++] = Node(points[i].y, Point(points[i].x, points[i + 1].x));
				else nodes[tt++] = Node(points[i].y, Point(points[i + 1].x, points[i].x));
			}
		}
		LL ansBlack, ansWhite;
		work(nodes, ansBlack, ansWhite, tt);
		cout << ansBlack << ' ' << ansWhite << endl;
	}
	return 0;
}

int main() {
	//freopen("in_c", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
