#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

const int N = 222;
const int M = N * N;
int n, m, k;
int fa[N];
bool power[N];

void init() {
	for (int i = 0; i < N; i++) fa[i] = i;
}

struct Edge {
	int a, b, c;
	void read() {
		scanf("%d%d%d", &a, &b, &c);
	}
	bool operator < (const Edge &x) const {
		return c < x.c;
	}
} et[M];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool Union(int a, int b) {
	a = find(a), b = find(b);
	if (a == b || (power[a] && power[b])) return false;
	fa[a] = b;
	power[b] |= power[a];
	return true;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		memset(power, false, sizeof(power));
		for (int i = 0; i < k; i++) {
			int x;
			scanf("%d", &x);
			power[x] = true;
		}
		init();
		for (int i = 0; i < m; i++) et[i].read();
		sort(et, et + m);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			if (Union(et[i].a, et[i].b)) {
				ans += et[i].c;
			}
		}
		printf("Case #%d: %d\n", Case++, ans);
	}
	return 0;
}

