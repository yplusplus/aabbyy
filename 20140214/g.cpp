#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
int n, d;
int a[N];

struct SegTree {
	int mx[N << 2];
	void clear() { memset(mx, 0, sizeof(mx)); }
	void update(int p, int l, int r, int x, int v) {
		if (l == r) {
			mx[p] = max(mx[p], v);
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) update(p << 1, l, mid, x, v);
		else update(p << 1 | 1, mid + 1, r, x, v);
		mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
	}
	int query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return mx[p];
		int mid = l + r >> 1;
		int res = 0;
		if (L <= mid) res = max(res, query(p << 1, l, mid, L, R));
		if (mid < R) res = max(res, query(p << 1 | 1, mid + 1, r, L, R));
		return res;
	}
} st;

int main() {
	while (~scanf("%d%d", &n, &d)) {
		vector<int> v;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			v.push_back(a[i]);
		}
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		st.clear();
		int all = v.size();
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int L = lower_bound(v.begin(), v.end(), a[i] - d) - v.begin() + 1;
			int R = upper_bound(v.begin(), v.end(), a[i] + d) - v.begin();
			int p = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
			int ret = st.query(1, 1, all, L, R) + 1;
			ans = max(ans, ret);
			st.update(1, 1, all, p, ret);
		}
		cout << ans << endl;
	}
	return 0;
}
