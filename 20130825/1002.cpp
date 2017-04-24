#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>

using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;
const int N = 2222;
struct MFS {
	int fa[N], cnt;
	void init() { for (int i = 0; i < N; i++) fa[i] = i; cnt = 0;}
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]);}
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) cnt++;
		fa[fx] = fy;
	}
} mfs;

int rx[N], ry[N];
map<int, int> id;

int powmod(int a, int p) {
	int ret = 1;
	while (p > 0) {
		if (p & 1) ret = (LL) ret * a % MOD;
		a = (LL) a * a % MOD;
		p >>= 1;
	}
	return ret;
}

int main() {
	int n, m;
	//cout << MOD << endl;
	while (~scanf("%d%d", &n, &m)) {
		id.clear();
		mfs.init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", rx + i, ry + i);
			ry[i]++;
			id[rx[i]] = id[ry[i]] = 1;
		}
		int c = 0;
		for (map<int, int>::iterator mi = id.begin(); mi != id.end(); mi++) {
			(*mi).second = c++;
		}
		for (int i = 0; i < m; i++) rx[i] = id[rx[i]], ry[i] = id[ry[i]];
		for (int i = 0; i < m; i++) {
			mfs.merge(rx[i], ry[i]);
		}
		//cout << mfs.cnt << endl;
		printf("%d\n", powmod(26, n - mfs.cnt));
	}
	return 0;
}