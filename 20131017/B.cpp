#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
int n, m;
int fa[N];
int sig[N];
int cnt[N][2];
void init() {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		sig[i] = 1;
		cnt[i][0] = 1, cnt[i][1] = 0;
	}
}

int find(int x) {
	if (x == fa[x]) return x;
	int t = find(fa[x]);
	sig[x] = sig[x] * sig[fa[x]];
	return fa[x] = t;
}

bool Union(int a, int b, int c) {
	int ra = find(a), rb = find(b);
	if (ra == rb) {
		return sig[a] * sig[b] != c;
	} else {
		fa[ra] = rb;
		sig[ra] = sig[a] * sig[b] * c;
		if (sig[ra] == 1) {
			cnt[rb][0] += cnt[ra][0];
			cnt[rb][1] += cnt[ra][1];
		} else {
			cnt[rb][0] += cnt[ra][1];
			cnt[rb][1] += cnt[ra][0];
		}
		return false;
	}
}

int press[N];
int main() {
	while (~scanf("%d%d", &n, &m)) {
		init();
		bool found = false;
		for (int i = 0; i < m; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			found |= Union(a, b, c * d * -1);
		}
		if (found) {
			puts("NO");
		} else {
			puts("YES");
			vector<int> hasPress;
			for (int i = 1; i <= n; i++) {
				if (fa[i] == i) {
					if (cnt[i][0] > cnt[i][1]) press[i] = 0;
					else press[i] = 1;
				}
			}
			for (int i = 1; i <= n; i++) {
				int t = find(i);
				if (sig[i] == 1 && press[t] == 1) hasPress.push_back(i);
				if (sig[i] == -1 && press[t] == 0) hasPress.push_back(i);
			}
			printf("%d\n", (int)hasPress.size());
			sort(hasPress.begin(), hasPress.end());
			for (int i = 0; i < hasPress.size(); i++) {
				printf("%d\n", hasPress[i]);
			}
		}
	}
	return 0;
}