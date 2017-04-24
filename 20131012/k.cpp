#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
	double x, y, z;
	Point() {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	void get() { cin >> x >> y >> z;}
	Point operator - (Point a) { return Point(x - a.x, y - a.y, z - a.z);}
} ;

inline Point cross(Point a, Point b) { return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y + a.z * b.z;}

int main() {
	int _;
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(3);
	Point a, b, c, d;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		a.get(); b.get(); c.get(); d.get();
		cout << "Case #" << cas << ": " << fabs(dot(cross(b - a, c - a), d - a)) / 6 << endl;
	}
	return 0;
}

