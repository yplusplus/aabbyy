#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

const int N = 1010;
const double eps = 1e-8;
int rak[N], pre[N];

int find(int x) {
	if (pre[x] == -1) return x;
	return pre[x] = find(pre[x]);
}

void init() {
	memset(pre, -1, sizeof(pre));
	for (int i = 0; i < N; i++) rak[i] = 1;
}

void unions(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (rak[x] < rak[y]) swap(x, y);
	pre[y] = x;
	rak[x] += rak[y];
}

int a[N], b[N], c[N];

double sqr(double x) {
	return x * x;
}

double dis(int x, int y) {
	return sqr(a[x] - a[y]) + sqr(b[x] - b[y]);
}

bool check(int x, int y, double mid) {
    return (dis(x, y) <= sqr(c[x] + c[y] + mid * 2));
}

void build_graph(int n, double mid, int w) {
	if (2 * mid > b[n]) {
		pre[0] = n;
		return;
	}

	for (int i = 1; i < n; i++)
		if (c[i] + 2 * mid + eps > b[i]) {
			unions(0, i);
		}
	for (int i = 1; i < n; i++) {
		if (c[i] + mid * 2 + eps > w - b[i]) { 
			unions(n, i);
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (check(i, j, mid)) {
				unions(i, j);
				if(find(0) == find(n)) return;
			}
		}
	}
}

void solve() {
	int w;
	scanf("%d", &w);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	a[++n] = 0;
	b[n] = w;
	c[n] = 0;
	double ans = 0;
	double lt = 0, rt = w, mid;
	while (lt <= rt) {
		mid = (lt + rt) / 2;
		init();
		build_graph(n, mid, w);
		if (find(0) == find(n)) rt = mid - eps;
		else ans = mid, lt = mid + eps;
	}

	printf("%.20lf\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) solve();
	return 0;
}
