#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long LL;
inline LL lowbit(LL x) { return x & -x; }

LL highbit(LL x) {
	while (x != lowbit(x)) x ^= lowbit(x);
	return x;
}

void convert(LL x, LL y, LL &a, LL &b, LL &c, LL &d) {
	LL hi;
	c = x; d = y;
	while (1) {
		hi = highbit(c + d);
		//cout << c << ' ' << d << ' ' << hi << endl;
		if (c > hi) { c -= hi; continue; }
		if (d > hi) { d -= hi; continue; }
		break;
	}
	hi = highbit(c + d);
	a = x / hi;
	b = y / hi;
}

bool ignore(LL x, LL y) {
	LL a, b, c, d;
	if (x == 0 || y == 0) return 1;
	convert(x, y, a, b, c, d);
	if (c == 0 || d == 0) return 1;
	LL hx = highbit(c);
	LL hy = highbit(d);
	if (hx == c && (d / hx & 1) == 0) return 1;
	if (hy == d && (c / hy & 1) == 0) return 1;
	return 0;
}


bool same(LL a, LL b, LL c, LL d) {
	LL a1, a2, b1, b2;
	convert(a, b, a1, b1, a2, b2);
	LL c1, c2, d1, d2;
	convert(c, d, c1, d1, c2, d2);
	return highbit(a2 + b2) == highbit(c2 + d2) && a1 == c1 && b1 == d1;
}

typedef pair<LL, LL> PII;
typedef pair<PII, LL> PIII;
set<PIII> has;
LL cal(LL x, LL y) {
	LL a, b, c, d;
	convert(x, y, a, b, c, d);
	LL hi = highbit(c + d);
	if (has.find(PIII(PII(a, b), hi)) != has.end()) return 0;
	has.insert(PIII(PII(a, b), hi));
	return hi * (hi - 1) >> 1;
}

const int N = 5555;
LL X[N], Y[N], tt;

int main() {
	int _, n;
	ios::sync_with_stdio(0);
	cin >> _;
	while (_--) {
		cin >> n;
		tt = 0;
		for (int i = 0; i < n; i++) {
			cin >> X[tt] >> Y[tt];
			if (ignore(X[tt], Y[tt])) continue;
			tt++;
		}
		LL ans = 0;
		has.clear();
		for (int i = 0; i < tt; i++) ans += cal(X[i], Y[i]);
		cout << ans << endl;
	}
	return 0;
}
