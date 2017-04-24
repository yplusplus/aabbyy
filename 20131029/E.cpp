#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double DB;

const int N = 1111;
const int T = 111;
const DB EPS = 1e-12;
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }

typedef pair<DB, DB> Point;
typedef pair<Point, int> Node;
#define x first
#define y second

int n;
DB m, p, no_use, tt_val;
DB sum, wt_sum, ans[N];
Node node[N];

DB cal(DB l, DB r) {
	DB ret = 0;
	int id;
	memset(ans, 0, sizeof(ans));
	id = 1;
	while (id <= n && sgn(l) > 0) {
		DB d = min(node[id].x.y, l);
		ans[node[id].y] += d;
		ret += d * node[id].x.x;
		l -= d;
		id++;
	}
	//cout << "1 " << l << ' ' << r << ' ' << ret << endl;
	id = n;
	while (id >= 1 && sgn(r) > 0) {
		DB d = min(node[id].x.y, r);
		ans[node[id].y] += d;
		ret += d * node[id].x.x;
		r -= d;
		id--;
	}
	//cout << "2 " << l << ' ' << r << ' ' << ret << endl;
	return ret;
}

DB dc2(DB l, DB r) {
	DB mid;
	for (int i = 0; i < T; i++) {
		mid = (l + r) / 2;
		if (sgn(cal(mid, sum - no_use - mid) - tt_val) < 0) r = mid;
		else l = mid;
	}
	return l;
}

bool work() {
	sort(node + 1, node + n + 1);
	tt_val = m * p;
	if (sgn(wt_sum - tt_val) < 0) return 0;
	if (sgn(sum - m) < 0) return 0;
	if (sgn(tt_val - m * node[1].x.x) < 0) return 0;
	if (sgn(tt_val - m * node[n].x.x) > 0) return 0;
	no_use = sum - m;
	//for (int i = 1; i <= n; i++) cout << node[i].x.x << ' ' << node[i].x.y << endl;
	//cout << sum - no_use << ' ' << tt_val << endl;
	//cout << cal(0, sum - no_use) << ' ' << cal(sum - no_use, 0) << endl;
	if (sgn(cal(0, sum - no_use) - tt_val) < 0) return 0;
	if (sgn(cal(sum - no_use, 0) - tt_val) > 0) return 0;
	DB pos = dc2(0, sum - no_use);
	//cout << pos << endl;
	DB val = cal(pos, sum - no_use - pos);
	//cout << val << endl;
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(15);
	while (cin >> n >> m >> p) {
		sum = 0, wt_sum = 0;
		for (int i = 1; i <= n; i++) cin >> node[i].x.y >> node[i].x.x;
		for (int i = 1; i <= n; i++) node[i].y = i, sum += node[i].x.y, wt_sum += node[i].x.x * node[i].x.y;
		if (work()) {
			cout << "YES" << endl;
			for (int i = 1; i <= n; i++) cout << ans[i] << endl;
		} else cout << "NO" << endl;
		
	}
	return 0;
}

