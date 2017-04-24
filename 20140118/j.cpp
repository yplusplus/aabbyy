#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 111;
int n, m;
int next[N];
int val[N];

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(next, -1, sizeof(next));
		for (int i = 0; i < n; i++) { scanf("%d", &val[i]); }
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (next[a] == -1) next[a] = b;
			else if (val[next[a]] < val[b]) next[a] = b;
		}
		int ans = 0;
		int x = 0;
		int prev = -1;
		while (x != -1) {
			prev = x;
			ans += val[x];
			x = next[x];
		}
		printf("Case %d: %d %d\n", Case++, ans, prev);
	}
	return 0;
}
