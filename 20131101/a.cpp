#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double DB;
const DB PI = acos(-1.0);
const DB P = 100.0;
const DB EPS = 1e-6;
inline int sgn(const DB &a) { return (a > EPS) - (a < EPS); }
const DB g = 981;
const int T = 111;
DB L, H, W;

int main() {
	//freopen("in", "r", stdin);
	while (cin >> L >> H >> W) {
		int ang = 0;
		while (1) {
			DB t = (ang / P + EPS) / (W * 6.0);
			DB rad = (ang / P + EPS) * PI / 180;
			DB d = g * t * t / 2 + L * fabs(sin(rad)) / 2;
			if (sgn(d - H) >= 0) break;
			ang++;
		}
		DB l = ang - 5, r = ang;
		for (int i = 0; i < T; i++) {
			DB m = (l + r) / 2;
			DB t = (m / P + EPS) / (W * 6.0);
			DB rad = (m / P + EPS) * PI / 180;
			DB d = g * t * t / 2 + L * fabs(sin(rad)) / 2;
			if (sgn(d - H) >= 0) r = m;
			else l = m;
		}
		//cout << ang << endl;
		//cout << fmod(ang / P + EPS + 90, 360.0) << endl;
		if (fmod(l / P + EPS + 90, (DB) 360.0) < 180) cout << "butter" << endl;
		else cout << "bread" << endl;
	}
	return 0;
}
