#include <bits/stdc++.h>
using namespace std;

const int N = 333333;
const int inf = 1 << 30;
int d[N];
int n;
struct SegmentTree {
	int minus[N << 2], v[N << 2];
	void pushup(int p) {
		v[p] = min(v[p << 1], v[p << 1 | 1]);
	}
	void pushdown(int p) {
		if (minus[p]) {
			minus[p << 1] += minus[p];
			minus[p << 1 | 1] += minus[p];
			v[p << 1] -= minus[p];
			v[p << 1 | 1] -= minus[p];
			minus[p] = 0;
		}
	}
	void build(int p, int l, int r) {
		minus[p] = 0;
		if (l == r) { v[p] = d[l]; return; }
		int mid = l + r >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		pushup(p);
	}
	void update(int p, int l, int r, int L, int R, int m) {
		if (L <= l && r <= R) {
			minus[p] += m;
			v[p] -= m;
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (L <= mid) update(p << 1, l, mid, L, R, m);
		if (mid < R) update(p << 1 | 1, mid + 1, r, L, R, m);
		pushup(p);
	}
	int query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return v[p];
		}
		pushdown(p);
		int mid = l + r >> 1;
		int ret = inf;
		if (L <= mid) ret = min(ret, query(p << 1, l, mid, L, R));
		if (mid < R) ret = min(ret, query(p << 1 | 1, mid + 1, r, L, R));
		pushup(p);
		return ret;
	}
} T;

bool check(vector<pair<int, int> > worker) {
	int sum = 0;
	for (int i = 0; i < worker.size(); i++) {
		sum += abs(worker[i].first - worker[i].second) + 1;
		int step = worker[i].first <= worker[i].second ? 1 : -1;
		if (step == 1) {
			int cnt = 1;
			for (int j = worker[i].first; j <= worker[i].second; j ++) {
				if (d[j] < cnt) return false;
			}
		} else {
			int cnt = 1;
			for (int j = worker[i].second; j <= worker[i].first; j ++) {
				if (d[j] < cnt) return false;
			}
		}
	}
	if (sum != n) return false;
	return true;
}

int main() {
	while (cin >> n) {
		for (int i = 1; i <= n; i++) cin >> d[i];
		T.build(1, 1, n);
		int now_pos = 0;
		vector<pair<int, int> > worker;
		while (now_pos < n) {
			int cnt = 0;
			int t1 = n, t2 = -1;
			//cout << now_pos << " " << now_pos + 1 << " " << n << endl;
			for (int i = now_pos + 1; i <= n; i++) {
				//if (now_pos == 0) cout << "#############" << endl;
				//cout << now_pos << " " << i << endl;
				cnt++;
				if (d[i] < cnt) {
					t1 = i - 1;
					break;
				}
			}
			//cout << now_pos << " " << t1 << " " << t2 << endl;
			cnt = 0;
			while (true) {
				cnt ++;
				if (now_pos + cnt == n + 1) {
					t2 = n;
					break;
				}
				int ret = T.query(1, 1, n, now_pos + 1, now_pos + cnt);
				if (ret == 0) {
					t2 = now_pos + cnt - 1;
					break;
				} else {
					T.update(1, 1, n, now_pos + 1, now_pos + cnt, 1);
				}
			}
			//cout << now_pos << " " << t1 << " " << t2 << endl;
			if (t1 > t2) {
				worker.push_back(make_pair(now_pos + 1, t1));
				now_pos = t1;
			} else {
				worker.push_back(make_pair(t2, now_pos + 1));
				now_pos = t2;
			}
		}
		cout << worker.size() << endl;
		for (int i = 0; i < worker.size(); i++) {
			cout << worker[i].first << " " << worker[i].second << endl;
		}
		//if (!check(worker)) puts("error");
	}
	return 0;
}

