#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Seg;
typedef pair<DB, int> Node;
#define x first
#define y second
const int N = 33333;
const DB EPS = 1e-10;
const DB DT = EPS * 10;
const DB PI = acos(-1.0);
const DB PI2 = PI * 2;
Seg seg[N << 1];
Node node[N << 2];
DB x[N], y[N];

inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
inline DB solve_bigger(const DB &a, const DB &b, const DB &c) {
	DB dt = b * b - 4 * a * c;
	return (-b + sqrt(dt)) / (2 * a);
}

Seg cal(const DB &x, const DB &y, const DB &a) {
	DB d = hypot(x, y), k = solve_bigger(1, 1, - a * a * d * d);
	if (sgn(d) == 0) return Seg(-PI, PI - DT);
	DB ang = atan2(y, x), dt = PI / 2 - atan(sqrt(k));
	return Seg(ang - dt, ang + dt);
}

inline bool cmp(const Node &a, const Node &b) {
	if (sgn(a.x - b.x)) return a.x < b.x;
	return a.y > b.y;
}

int work(int n) {
	int tt = 0, cnt = 0, ans = 0;
	//for (int i = 0; i < n; i++) cout << seg[i].x << ' ' << seg[i].y << endl;
	for (int i = 0; i < n; i++) {
		node[tt++] = Node(seg[i].x, 1);
		node[tt++] = Node(seg[i].x + PI2, 1);
		node[tt++] = Node(seg[i].y, -1);
		node[tt++] = Node(seg[i].y + PI2, -1);
	}
	sort(node, node + tt, cmp);
	for (int i = 0; i < tt; i++) {
		//cout << node[i].x << ' ' << node[i].y << ' ' << cnt << endl;
		cnt += node[i].y;
		ans = max(cnt, ans);
	}
	return ans;
}

int main() {
	int n;
	DB a;
	ios::sync_with_stdio(0);
	while (cin >> n >> a) {
		for (int i = 0; i < n; i++) cin >> x[i];
		for (int i = 0; i < n; i++) cin >> y[i];
		for (int i = 0; i < n; i++) seg[i] = cal(x[i], y[i], a);
		cout << work(n) << " daze" << endl;
	}
	return 0;
}
