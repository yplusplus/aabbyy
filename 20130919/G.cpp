#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 11111;
int fa[N], cnt[N];
bool islink[N];
int circle[N], chain[N];
int n, m;

void init () {
	for (int i = 0; i < N; i++) fa[i] = i, cnt[i] = 1;
	memset(islink, true, sizeof(islink));
}

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	fa[a] = b;
	cnt[b] += cnt[a];
	return true;
}

int main() {
	int T, Case = 1;
	int a, b;
	scanf("%d", &T);

	while (T--) {
		memset(circle, 0, sizeof(circle));
		memset(chain, 0, sizeof(chain));

		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			if (!Union(a, b)) {
				a = find(a), b = find(b);
				islink[a] = false, islink[b] = false;
				circle[cnt[a] + cnt[b]]++;
			}
		}
		for (int i = 1; i <= n; i++) {
			if (fa[i] == i && islink[i]) chain[cnt[i]]++;
		}

		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			if (!Union(a, b)) {
				a = find(a), b = find(b);
				islink[a] = false, islink[b] = false;
				circle[cnt[a] + cnt[b]]--;
			}
		}
		for (int i = 1; i <= n; i++) {
			if (fa[i] == i && islink[i]) chain[cnt[i]]--;
		}

		bool found = false;
		for (int i = 1; i <= n; i++) {
			found |= circle[i] != 0;
			found |= chain[i] != 0;
		}


		printf("Case #%d: %s\n", Case++, found ? "NO" : "YES");
	}
}