#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
const char *MSG = "unstable";
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
istream &operator >> (istream &in, Point &a) { return in >> a.x >> a.y; }
ostream &operator << (ostream &out, const Point &a) { return out << a.x << ' ' << a.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
const DB EPS = 1e-10;
const DB FINF = 1e30;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

Point getGravity(const vector<Point> &pt) {
	DB area = 0, temp;
	Point g(0, 0);
	int n = pt.size();
	area += (temp = cross(pt[n - 1], pt[0]));
	g = g + (pt[n - 1] + pt[0]) * temp;
	for (int i = 1; i < pt.size(); ++i) {
		area += (temp = cross(pt[i - 1], pt[i]));
		g = g + (pt[i - 1] + pt[i]) * temp;
	}
	g = g / area / 3;
	return g;
}

DB getArea(const vector<Point> &pt) {
	DB area = cross(pt[pt.size() - 1], pt[0]);
	for (int i = 1; i < pt.size(); ++i) {
		area += cross(pt[i - 1], pt[i]);
	}
	return fabs(area / 2);
}

vector<Point> crane;
DB Left, Right;

void gao() {
	Point g = getGravity(crane);
	const Point &p = crane[0];
	DB ttWt = getArea(crane);
	if (sgn(Left - g.x) <= 0 && sgn(g.x - Right) <= 0) {
		if (sgn(Left - p.x) <= 0 && sgn(p.x - Right) <= 0) {
			cout << "0 .. inf" << endl;
			return ;
		}
		DB mxWt;
		if (p.x < Left) {
			mxWt = ttWt * (g.x - Left) / (Left - p.x);
		} else {
			mxWt = ttWt * (g.x - Right) / (Right - p.x);
		}
		cout << "0 .. " << int(ceil(mxWt)) << endl;
	} else {
		if (sgn(Left - p.x) < 0 && sgn(p.x - Right) < 0) {
			DB mnWt;
			if (g.x < Left) {
				mnWt = ttWt * (Left - g.x) / (p.x - Left);
			} else {
				mnWt = ttWt * (g.x - Right) / (Right - p.x);
			}
			cout << int(floor(mnWt)) << " .. inf" << endl;
		} else {
			DB mnWt, mxWt;
			if (g.x < Left) {
				if (sgn(p.x - Left) <= 0) {
					cout << MSG << endl;
					return ;
				} else {
					if (sgn(p.x - Right) == 0) {
						mnWt = ttWt * (Left - g.x) / (p.x - Left);
						cout << int(floor(mnWt)) << " .. inf" << endl;
						return ;
					} else {
						mnWt = ttWt * (Left - g.x) / (p.x - Left);
						mxWt = ttWt * (Right - g.x) / (p.x - Right);
					}
				}
			} else {
				if (sgn(p.x - Right) >= 0) {
					cout << MSG << endl;
					return ;
				} else {
					if (sgn(p.x - Left) == 0) {
						mnWt = ttWt * (g.x - Right) / (Right - p.x);
						cout << int(floor(mnWt)) << " .. inf" << endl;
						return ;
					} else {
						mnWt = ttWt * (g.x - Right) / (Right - p.x);
						mxWt = ttWt * (g.x - Left) / (Left - p.x);
					}
				}
			}
			cout << int(floor(mnWt)) << " .. " << int(ceil(mxWt)) << endl;
		}
	}
}

int run() {
	int n;
	while (cin >> n) {
		crane.resize(n);
		Left = DBL_MAX;
		Right = DBL_MIN;
		for (int i = 0; i < n; ++i) {
			cin >> crane[i];
			if (sgn(crane[i].y)) {
				continue;
			}
			Left = min(crane[i].x, Left);
			Right = max(crane[i].x, Right);
		}
		//cout << Left << ' ' << Right << endl;
		//cout << getGravity(crane) << endl;
		gao();
	}
	return 0;
}

int main() {
	//freopen("in_c", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
