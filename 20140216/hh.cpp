#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define MP make_pair
const int M = 155;
const int N = 15;
const int TIMES = 100000;
int n, m;

struct Comp {
	pii in[2];
	int out[2];
	int t;
	void fix() { if (out[0] > out[1]) swap(out[0], out[1]); }
} comp[M];

pii record[N];
int a[N], b[N];
bool visit[M];
int dfs(int i) {
	if (i == 0) return 0;
	if (visit[i]) return comp[i].t;
	visit[i] = true;
	int t = 0;
	for (int j = 0; j < 2; j++) {
		t = max(dfs(comp[i].in[j].first), t);
	}
	return comp[i].t = t + 1;
}

void dfs_value(int i) {
	if (visit[i]) return;
	visit[i] = true;
	for (int j = 0; j < 2; j++) {
		int pre = comp[i].in[j].first;
		int pos = comp[i].in[j].second;
		if (pre) {
			dfs_value(pre);
			comp[i].out[j] = comp[pre].out[pos];
		} else comp[i].out[j] = a[pos];
	}
	comp[i].fix();
	return;
}

bool check() {
	memset(visit, false, sizeof(visit));
	for (int i = 1; i <= m; i++) dfs_value(i);
	for (int i = 1; i <= n; i++) {
		int pre = record[i].first;
		int pos = record[i].second;
		if (pre) {
			b[i] = comp[pre].out[pos];
		} else b[i] = a[pos];
		if (b[i] != i) return false;
	}
	return true;
}

void solve() {
	int ti = 0;
	memset(visit, false, sizeof(visit));
	for (int i = 1; i <= m; i++) { ti = max(ti, dfs(i)); }
	bool found = false;
	for (int i = 1; i <= n; i++) { a[i] = i; }
	if (n <= 8) {
		do {
			if (!check()) {
				found = true;
				break;
			}
		} while (next_permutation(a + 1, a + n + 1));
	} else {
		for (int i = 0; i < TIMES; i++) {
			random_shuffle(a + 1, a + n + 1);
			if (!check()) {
				found = true;
				break;
			}
		}
	}
	if (!found) {
		printf("is a sorting network and operates in %d time units.\n", ti);
	} else {
		printf("is not a sorting network and operates in %d time units.\n", ti);
	}
}

int main() { 
	int Case = 1;
	while (~scanf("%d%d", &n, &m), n + m) {
		for (int i = 1; i <= m; i++) {
			comp[i].t = 0;
		}
		for (int i = 1; i <= n; i++) {
			record[i] = MP(0, i);
		}
		for (int i = 1; i <= m; i++) {
			int fi, se;
			scanf("%d%d", &fi, &se);
			comp[i].in[0] = record[fi];
			record[fi] = MP(i, 0);
			//next[record[fi].first][record[fi].second] = MP(i, 0);
			comp[i].in[1] = record[se];
			record[se] = MP(i, 1);
			//next[record[se].first][record[se].second] = MP(i, 0);
		}
		printf("Case %d ", Case++);
		solve();
	}
	return 0;
}
