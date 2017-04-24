#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
const int M = 333333;
#define fi first
#define se second

int n, m;
typedef pair<int, int> pii;
pair<int, pii> edge[N];
bool cmp(const pair<int, pii> &a, const pair<int, pii> &b) {
	return a.se.se - a.se.fi > b.se.se - b.se.fi;
}

struct SegmentTree {
	int a[M * 3];
	void clear() { memset(a, 0, sizeof(a)); }
	void pushdown(int p) {
		if (a[p]) {
			a[p << 1] = a[p << 1 | 1] = a[p];
			a[p] = 0;
		}
	}
	void update(int p, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) {
			a[p] = x;
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (L <= mid) update(p << 1, l, mid, L, R, x);
		if (mid < R) update(p << 1 | 1, mid + 1, r, L, R, x);
	}
	int query(int p, int l, int r, int x) {
		if (l == r) {
			return a[p];
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (x <= mid) return query(p << 1, l, mid, x);
		else return query(p << 1 | 1, mid + 1, r, x);
	}
} st;

int main() {
	while (~scanf("%d", &n)) {
		vector<int> vec, query;
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			edge[i] = make_pair(i + 1, make_pair(a, b));
			vec.push_back(a);
			vec.push_back(b);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int x;
			scanf("%d", &x);
			query.push_back(x);
			vec.push_back(x);
		}
		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		st.clear();
		sort(edge, edge + n, cmp);
		for (int i = 0; i < n; i++) {
			//cout << edge[i].fi << " " << edge[i].se << endl;
			int l = lower_bound(vec.begin(), vec.end(), edge[i].se.fi) - vec.begin() + 1;
			int r = lower_bound(vec.begin(), vec.end(), edge[i].se.se) - vec.begin() + 1;
			//cout << l << " " << r << endl;
			st.update(1, 1, vec.size(), l, r, edge[i].fi);
		}
		for (int i = 0; i < m; i++) {
			int x = lower_bound(vec.begin(), vec.end(), query[i]) - vec.begin() + 1;
			int ans = st.query(1, 1, vec.size(), x);
			if (ans == 0) ans = -1;
			cout << ans << endl;
		}
	}
	return 0;
}

