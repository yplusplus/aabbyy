#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PI2;
typedef pair<int, PI2> PI3;
typedef vector<PI2> VI2;
typedef vector<PI3> VI3;
typedef vector<VI2> V2I2;
#define x first
#define y second

void get_range(const PI2 &a, const PI2 &b, int &l, int &r) {
	l = max(a.x, b.x);
	r = min(a.y, b.y);
}

LL work(V2I2 &hori, VI3 &vert) {
	LL ans = 0;
	int n = hori.size(), m = vert.size();
	for (int i = 0; i < n; ++i) sort(hori[i].begin(), hori[i].end());
	sort(vert.begin(), vert.end());
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			VI2 &dn = hori[i], &up = hori[j];
			int d_size = dn.size(), u_size = up.size();
			int d = 0, u = 0, l, r, cnt, cv = 0;
			while (d < d_size && u < u_size) {
				get_range(dn[d], up[u], l, r);
				//cout << "bound " << i << ' ' << j << ' ' << l << ' ' << r << endl;
				cnt = 0;
				while (cv < m && vert[cv].x <= r) {
					//cout << cnt << ' ' << cv << endl;
					if (vert[cv].x >= l) cnt += vert[cv].y.x <= i && j <= vert[cv].y.y;
					++cv;
				}
				ans += cnt * (cnt - 1) >> 1;
				if (dn[d].y < up[u].y) ++d;
				else ++u;
			}
			//cout << i << ' ' << j << ' ' << ans << endl;
		}
	}
	return ans;
}

int run() {
	int n;
	while (cin >> n) {
		map<int, int> id_x, id_y;
		VI a(n), b(n), c(n), d(n);
		for (int i = 0; i < n; ++i) cin >> a[i] >> b[i] >> c[i] >> d[i];
		for (int i = 0; i < n; ++i) if (a[i] > c[i]) swap(a[i], c[i]);
		for (int i = 0; i < n; ++i) if (b[i] > d[i]) swap(b[i], d[i]);
		for (int i = 0; i < n; ++i) id_x[a[i]] = id_x[c[i]] = 1;
		for (int i = 0; i < n; ++i) id_y[b[i]] = id_y[d[i]] = 1;
		map<int, int>::iterator mi;
		int cid;
		for (mi = id_x.begin(), cid = -1; mi != id_x.end(); ++mi) mi->y = ++cid;
		for (mi = id_y.begin(), cid = -1; mi != id_y.end(); ++mi) mi->y = ++cid;
		for (int i = 0; i < n; ++i) a[i] = id_x[a[i]];
		for (int i = 0; i < n; ++i) b[i] = id_y[b[i]];
		for (int i = 0; i < n; ++i) c[i] = id_x[c[i]];
		for (int i = 0; i < n; ++i) d[i] = id_y[d[i]];
		//for (int i = 0; i < n; ++i) cout << a[i] << ' ' << b[i] << ' ' << c[i] << ' ' << d[i] << endl;
		V2I2 hori(id_y.size());
		VI3 vert;
		for (int i = 0; i < n; ++i) {
			if (a[i] == c[i]) vert.push_back(PI3(a[i], PI2(b[i], d[i])));
			else hori[b[i]].push_back(PI2(a[i], c[i]));
		}
		cout << work(hori, vert) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	return run();
}
