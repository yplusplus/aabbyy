#include <bits/stdc++.h>
using namespace std;

const int dx[8] = { 0, 1, 0, -1, -1, 1, -1, 1 };
const int dy[8] = { 1, 0, -1, 0, -1, -1, 1, 1 };

const int MAXSIZE = 1 << 10;
const int MAXN = MAXSIZE * MAXSIZE;
const int OFFSET = MAXSIZE >> 1;
struct MFS {
	int fa[MAXN], cnt[MAXN], S, temp[MAXN];
	void init(int s) { S = s; for (int i = 0; i < MAXN; ++i) fa[i] = i, cnt[i] = 0; }
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	inline int encode(int x, int y) { x += OFFSET, y += OFFSET; return x * MAXSIZE + y; }
	void merge(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (fx == fy) return ;
		fa[fx] = fy;
		cnt[fy] += cnt[fx];
	}
	bool check(int x, int y) {
		int id = encode(x, y), tid, tt = 0;
		if (cnt[id]) return 0;
		for (int i = 0; i < 4; ++i) {
			tid = encode(x + dx[i], y + dy[i]);
			if (cnt[find(tid)]) temp[tt++] = find(tid);
		}
		if (x & 1) {
			for (int i = 6; i < 8; ++i) {
				tid = encode(x + dx[i], y + dy[i]);
				if (cnt[find(tid)]) temp[tt++] = find(tid);
			}
		} else {
			for (int i = 4; i < 6; ++i) {
				tid = encode(x + dx[i], y + dy[i]);
				if (cnt[find(tid)]) temp[tt++] = find(tid);
			}
		}
		sort(temp, temp + tt);
		int k = unique(temp, temp + tt) - temp, ttCnt = 1;
		for (int i = 0; i < k; ++i) ttCnt += cnt[temp[i]];
		if (ttCnt > S) return 0;
		++cnt[id];
		for (int i = 0; i < k; ++i) merge(id, temp[i]);
		return 1;
	}
	void print() {
		int tt = 0;
		for (int i = 0; i < MAXN; ++i) if (cnt[find(i)]) temp[tt++] = find(i);
		sort(temp, temp + tt);
		int k = unique(temp, temp + tt) - temp;
		for (int i = 0; i < k; ++i) temp[i] = cnt[temp[i]];
		sort(temp, temp + k);
		cout << k << endl;
		for (int i = 0; i < k; ++i) {
			if (i) cout.put(' ');
			cout << temp[i];
		}
		cout << endl;
	}
} mfs;

int run() {
	int n, s;
	while (cin >> n >> s) {
		mfs.init(s);
		int x, y;
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			//cout << mfs.check(x, y) << endl;
			mfs.check(x, y);
		}
		mfs.print();
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
