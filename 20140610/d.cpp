#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int T = 1 << 6;
const DB PI = acos(-1.0);
const DB EPS = 1e-6;
vector<DB> diameter;
typedef pair<DB, DB> Point;
#define x first
#define y second

inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline void precision(int p) { cout << setprecision(p); }
inline DB cosTheory(const DB &a, const DB &b, const DB &c) { return acos((b * b + c * c - a * a) / (2 * b * c)); }
inline Point getPoint(const DB &r, const DB &a) { return Point(r * cos(a), r * sin(a)); }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
} ;
inline bool isIntersect(const Circle &a, const Circle &b) { return sgn(veclen(a.c - b.c) - (a.r + b.r)) < 0; }

struct CircleSet {
	vector<DB> radius;
	vector<DB> position;
	int size;
	DB R;
	void clear(const DB &r) {
		R = r;
		size = 0;
		radius.clear();
		position.clear();
	}
	bool insert(const DB &r) {
		if (size == 0) {
			radius.push_back(r);
			position.push_back(0);
			++size;
			return 1;
		}
		DB maxPosition = position[size - 1];
		for (int i = 0; i < size; ++i) {
			maxPosition = max(position[i] + cosTheory(r + radius[i], R - radius[i], R - r), maxPosition);
		}
		for (int i = 0; i < size; ++i) {
			if (isIntersect(Circle(getPoint(R - radius[i], position[i]), radius[i]), Circle(getPoint(R - r, maxPosition), r))) {
				return 0;
			}
		}
		position.push_back(maxPosition);
		radius.push_back(r);
		++size;
		return 1;
	}
} circleSet;

bool input() {
	diameter.resize(4);
	for (int i = 0; i < 4; ++i) {
		cin >> diameter[i];
		if (diameter[i] == 0) return 0;
	}
	return 1;
}

bool check(const vector<DB> &radius, const DB &r) {
	circleSet.clear(r);
	for (int i = 0; i < 4; ++i) {
		if (circleSet.insert(radius[i])) continue;
		return 0;
	}
	//for (int i = 0; i < 4; ++i) { cout << circleSet.position[i] << ' '; } cout << endl;
	return 1;
}

bool test(const vector<DB> &diameter, const DB &r) {
	vector<DB> radius(4);
	vector<int> id(4);
	for (int i = 0; i < 4; ++i) {
		id[i] = i;
	}
	do {
		for (int i = 0; i < 4; ++i) {
			radius[i] = diameter[id[i]] / 2;
		}
		if (check(radius, r)) {
			return 1;
		}
	} while (next_permutation(id.begin() + 1, id.end()));
	return 0;
}

DB solve() {
	precision(6);
	sort(diameter.begin(), diameter.end());
	DB l = (diameter[2] + diameter[3]) / 2 + EPS;
	DB r = 10 * l, m;
	//cout << l << ' ' << r << endl;
	//test(diameter, 1.3); return 0;
	for (int i = 0; i < T; ++i) {
		m = (l + r) / 2;
		if (test(diameter, m)) {
			r = m;
		} else {
			l = m;
		}
	}
	//cout << "Answer " << (m * 2) << endl;
	return m * 2;
}

int run() {
	int cas = 0;
	while (input()) {
		DB answer = solve();
		precision(0);
		cout << "Case " << ++cas << ": " << answer << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed);
	return run();
}
