#include <bits/stdc++.h>
using namespace std;

const int N = 444444;
const int K = 2222;
int n, m, a[N];
int L, R, M;
int l[K], r[K], cnt[K];

inline void add(int x) {
	if (cnt[x] < l[x]) L++;
	else if (r[x] < cnt[x]) R++;
	else M++;
}

inline void sub(int x) {
	if (cnt[x] < l[x]) L--;
	else if (r[x] < cnt[x]) R--;
	else M--;
}

void init() {
	L = R = M = 0;
	for (int i = 0; i < m; i++) cnt[i] = 0;
	for (int i = 0; i < m; i++) add(i);
}

void insert(int x) {
	sub(x);
	cnt[x]++;
	add(x);
}

void erase(int x) {
	sub(x);
	cnt[x]--;
	add(x);
}

inline void update(int &a, int b) {
	if (~a) a = min(b, a);
	else a = b;
}

inline bool check() { return M == m; }

int work() {
	init();
	int h = 0, mk = -1;
	if (R) return -1;
	if (check()) return 0;
	for (int i = 0; i < n; i++) {
		insert(a[i]);
		//cout << i << ' ' << L << ' ' << M << ' ' << R << ' ' << h << endl;
		while (R && h <= i) erase(a[h++]);
		while (check()) { update(mk, i - h + 1); erase(a[h++]); }
	}
	return mk;
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n >> m) {
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) a[i]--;
		for (int i = 0; i < m; i++) cin >> l[i] >> r[i];
		cout << work() << endl;
	}
	return 0;
}
