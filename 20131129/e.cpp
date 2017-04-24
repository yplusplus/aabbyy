#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 22222;
int a[N], b[N], pos[N];
vector<int> box[N];

inline int lowbit(int x) { return x & -x; }
struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof(a)); }
	void add(int x, int d) { for ( ; x < N; x += lowbit(x)) a[x] += d; }
	int sum(int x) { int s = 0; for ( ; x > 0; x -= lowbit(x)) s += a[x]; return s; }
	int sum(int l, int r) { return sum(r) - sum(l - 1); }
} bit;

int main() {
	int _, n, k;
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		scanf("%d%d", &n, &k);
		int bc = n / k + (n % k != 0);
		for (int i = 0; i < bc; i++) box[i].clear();
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		for (int i = 1; i <= n; i++) pos[a[i]] = i;
		for (int i = 1; i <= n; i++) box[(a[i] - 1) / k].push_back(a[i]);
		int t = 1;
		for (int i = 0, sz; i < bc; i++) {
			sz = box[i].size();
			for (int j = 0; j < sz; j++) b[t++] = box[i][j];
		}
		int method1 = 0, method2 = 0;
		for (int i = 1; i <= n; i++) method2 = max(abs(i - pos[b[i]]), method2);
		for (int i = 1; i <= n; i++) b[i] = pos[b[i]];
		bit.init();
		for (int i = 1; i <= n; i++) {
			bit.add(b[i], 1);
			method1 += bit.sum(b[i] + 1, n);
		}
		printf("Case %d: %d\n", cas, method1 - method2);
	}
	return 0;
}
