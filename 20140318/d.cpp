#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PI2;
typedef vector<PI2> VI2;
#define x first
#define y second

void fix(VI &a) {
	int n = a.size();
	VI l = a, r = a;
	for (int i = 1; i < n; ++i) l[i] = min(l[i - 1], l[i]);
	for (int i = n - 2; i >= 0; --i) r[i] = min(r[i + 1], r[i]);
	for (int i = 0; i < n; ++i) a[i] = max(l[i], r[i]);
}

void work(const VI &l, const VI &r, const VI &x) {
	VI2 ans;
	int n = l.size();
	ans.push_back(PI2(x[0], l[0]));
	for (int i = 1; i < n; ++i) {
		if (l[i - 1] == l[i]) continue;
		if (l[i - 1] > l[i]) {
			ans.push_back(PI2(x[i], l[i - 1]));
			ans.push_back(PI2(x[i], l[i]));
		} else {
			ans.push_back(PI2(x[i - 1], l[i - 1]));
			ans.push_back(PI2(x[i - 1], l[i]));
		}
	}
	ans.push_back(PI2(x[n - 1], l[n - 1]));
	ans.push_back(PI2(x[n - 1], -r[n - 1]));
	for (int i = n - 1; i >= 1; --i) {
		if (r[i - 1] == r[i]) continue;
		if (r[i - 1] < r[i]) {
			ans.push_back(PI2(x[i - 1], -r[i]));
			ans.push_back(PI2(x[i - 1], -r[i - 1]));
		} else {
			ans.push_back(PI2(x[i], -r[i]));
			ans.push_back(PI2(x[i], -r[i - 1]));
		}
	}
	ans.push_back(PI2(x[0], -r[0]));
	reverse(ans.begin() + 1, ans.end());
	for (int i = 0; i < ans.size(); ++i) cout << ' ' << ans[i].x << ' ' << ans[i].y;
	cout << endl;
}

int run() {
	int n, cas = 0;
	while (cin >> n && n) {
		VI rx(n), ry(n);
		for (int i = 0; i < n; ++i) cin >> rx[i] >> ry[i];
		int cnt;
		map<int, int> xi;
		map<int, int>::iterator mi;
		for (int i = 0; i < n; ++i) xi[rx[i]] = xi[rx[i] + 9] = 1;
		VI L(xi.size(), INT_MAX), R(xi.size(), INT_MAX), ix(xi.size());;
		for (mi = xi.begin(), cnt = -1; mi != xi.end(); ++mi) ix[mi->y = ++cnt] = mi->x;;
		for (int i = 0, t; i < n; ++i) {
			t = xi[rx[i]];
			L[t] = min(ry[i], L[t]);
			R[t] = min(-ry[i] - 9, R[t]);
			t = xi[rx[i] + 9];
			L[t] = min(ry[i], L[t]);
			R[t] = min(-ry[i] - 9, R[t]);
		}
		fix(L);
		fix(R);
		//for (int i = 0; i < xi.size(); ++i) cout << ix[i] << ' ' << L[i] << ' ' << R[i] << endl;
		cout << "Case " << ++cas << ":";
		work(L, R, ix);
	}
	return 0;
}

int main() {
	//freopen("in_d", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
