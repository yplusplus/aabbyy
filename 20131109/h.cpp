#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int lowbit(int x) { return x & -x; }
const int N = 222222;
struct BIT {
	int a[N], n;
	void init(int sz) { n = sz + 10; memset(a, 0, sizeof(int) * n); }
	void add(int x, int p) { for ( ; p <= n; p += lowbit(p)) a[p] += x; }
	int sum(int p) { int s = 0; for ( ; p > 0; p -= lowbit(p)) s += a[p]; return s; }
} bit;

int pos[N], prev[N];
void get_prm() {
	memset(prev, 0, sizeof(prev));
	prev[1] = 1;
	for (int i = 2; i < N; i++) {
		if (prev[i]) continue;
		for (int j = i; j < N; j += i) prev[j] = i;
	}
}

int n, m, rabbit[N];
struct Query {
	int l, r, id;
	bool operator < (const Query &a) const {
		if (l != a.l) return l < a.l;
		return r < a.r;
	}
} qry[N];
struct Event {
	int x, l, r, d;
	Event() {}
	Event(int x, int l, int r, int d) : x(x), l(l), r(r), d(d) {}
	bool operator < (const Event &a) const {
		if (x != a.x) return x < a.x;
		return d < a.d;
	}
} ev[N << 1];
struct Seg { int a, b, c, d; } seg[N];
int ans[N];

int main() {
	//freopen("in", "r", stdin);
	get_prm();
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		for (int i = 1; i <= n; i++) scanf("%d", rabbit + i);
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &qry[i].l, &qry[i].r);
			qry[i].id = i;
		}
		sort(qry, qry + m); 
		for (int i = 0; i < N; i++) pos[i] = 1;
		for (int i = 1; i <= n; i++) {
			int x = rabbit[i], mx = 1;
			while (x > 1) {
				mx = max(pos[prev[x]], mx);
				pos[prev[x]] = i + 1;
				int t = prev[x];
				while (x > 1 && x % t == 0) x /= t;
			}
			seg[i].a = mx;
			seg[i].b = i;
		}
		for (int i = 0; i < N; i++) pos[i] = n;
		for (int i = n; i >= 1; i--) {
			int x = rabbit[i], mn = n;
			while (x > 1) {
				mn = min(pos[prev[x]], mn);
				pos[prev[x]] = i - 1;
				int t = prev[x];
				while (x > 1 && x % t == 0) x /= t;
			}
			seg[i].c = i;
			seg[i].d = mn;
		}
		//for (int i = 1; i <= n; i++) cout << rabbit[i] << ' ' << seg[i].a << ' ' << seg[i].b << ' ' << seg[i].c << ' ' << seg[i].d << endl;
		for (int i = 1; i <= n; i++) {
			ev[i - 1 << 1] = Event(seg[i].a, seg[i].c, seg[i].d, 1);
			ev[i - 1 << 1 | 1] = Event(seg[i].b + 1, seg[i].c, seg[i].d, -1);
		}
		bit.init(n);
		n <<= 1;
		sort(ev, ev + n); 
		for (int i = 0, j = 0; i < n; ) {
			int cur = ev[i].x;
			//cout << "cur " << cur << endl;
			while (i < n && ev[i].x == cur) {
				if (ev[i].d == 1) {
					bit.add(1, ev[i].l);
					bit.add(-1, ev[i].r + 1);
				} else {
					bit.add(-1, ev[i].l);
					bit.add(1, ev[i].r + 1);
				}
				i++;
			}
			while (qry[j].l == cur) {
				ans[qry[j].id] = bit.sum(qry[j].r);
				j++;
			}
		}
		for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
	}
	return 0;
}
