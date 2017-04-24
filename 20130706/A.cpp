#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const int C = 111;
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}

inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double veclen(Point a) { return sqrt(dot(a, a));}

Point pt[4];
inline bool get(Point &a) { return cin >> a.x >> a.y;}

bool input() {
	for (int i = 0; i < 4; i++) if (!get(pt[i])) return 0;
	return 1;
}

double cal(Point p, int a, int b) {
	double da = veclen(pt[a] - p), db = veclen(pt[b] - p);
	for (int i = 0; i < 4; i++) {
		if (i == a) continue;
		da = min(da, veclen(pt[i] - pt[a]));
	}
	for (int i = 0; i < 4; i++) {
		if (i == b) continue;
		db = min(db, veclen(pt[i] - pt[b]));
	}
	double sum = 0, t;
	for (int i = 0; i < 4; i++) {
		if (i == a || i == b) continue;
		double d = 1e100;
		for (int j = 0; j < 4; j++) {
			if (j == i) continue;
			else if (j == a) d = min(d, veclen(pt[i] - pt[j]) - da);
			else if (j == b) d = min(d, veclen(pt[i] - pt[j]) - db);
			else t = veclen(pt[i] - pt[j]);
		}
		sum += d;
	}
	sum = da + db + min(sum, t);
	return sum;
}

double cal(int a, int b) {
	Point l = pt[a], r = pt[b], m1, m2, d;
	for (int i = 0; i < C; i++) {
		d = (r - l) / 3;
		m1 = l + d, m2 = r - d;
		if (cal(m1, a, b) < cal(m2, a, b)) l = m1;
		else r = m2;
	}
	return cal(l, a, b);
}
		

double work() {
	double ret = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			ret = max(ret, cal(i, j));
		}
	}
	return ret;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(8);
	while (input()) cout << work() << endl;
	return 0;
}



