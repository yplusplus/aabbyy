#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
int n;
int a[N];
int b[N];
vector<pair<int, int> > interval;

inline void rot(int l, int r) {
	//cout << "interval" << l << " " << r << endl;
	interval.push_back(make_pair(l, r));
	int mid = (l + r) >> 1;
	int len = (r - l + 1) >> 1;
	//cout << mid << endl;
	for (int i = l; i <= mid; i++) {
		swap(b[a[i]], b[a[i + len]]);
		swap(a[i], a[i + len]);
	}
}

void output() {
	for (int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void gao(int l, int r, int pos) {
	//output();
	if (pos == l) return;
	int rlen = r - pos + 1;
	int llen = pos - l;
	int mi = min(llen, rlen);
	//cout << l << " " << r << " " << pos << " " << mi << endl;
	rot(pos - mi, pos + mi - 1);
	gao(l, r, pos - mi);
}

void solve() {
	interval.clear();
	for (int i = 1; i <= n; i++) {
		int pos = b[i];
		if (pos == i) continue;
		gao(i, pos, pos);
	}
	printf("%d\n", (int)interval.size());
	for (int i = 0; i < (int) interval.size(); i++) {
		printf("%d %d\n", interval[i].first, interval[i].second);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			b[a[i]] = i;
		}
		solve();
	}
	return 0;
}
