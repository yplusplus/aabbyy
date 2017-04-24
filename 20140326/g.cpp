#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int bits[1 << N];
int fri[N];
int dist[1 << N];
int n, m, K;

int solve() {
	if (fri[n - 1] & 1) return 0;
	memset(dist, -1, sizeof(dist));
	dist[fri[0]] = 0;
	queue<int> que;
	que.push(fri[0]);
	while (!que.empty()) {
		int now = que.front(); que.pop();
		if (bits[now & fri[n - 1]] >= K) return dist[now];
		for (int i = 1; i < n - 1; i++) {
			if (now >> i & 1) continue;
			if (bits[now & fri[i]] >= K) {
				int next = now | (1 << i);
				if (dist[next] == -1) {
					dist[next] = dist[now] + 1;
					que.push(next);
				}
			}
		}
	}
	return -1;
}

int main() {
	bits[0] = 0;
	for (int i = 1; i < (1 << N); i++) {
		bits[i] = bits[i >> 1] + (i & 1);
	}
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &K);
		memset(fri, 0, sizeof(fri));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--, b--;
			fri[a] |= 1 << b;
			fri[b] |= 1 << a;
		}
		printf("Case #%d: %d\n", Case++, solve());
	}
	return 0;
}
