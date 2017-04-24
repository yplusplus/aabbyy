#include <bits/stdc++.h>
using namespace std;

inline int pos(char ch) { return ch - 'a'; }
inline char tochar(int x) { return x + 'a'; }

vector<int> vec[26];

bool query(char now, int len, int mul, int add) {
	int pre = -1;
	for (int i = 0; i < len; i++) {
		int ret = lower_bound(vec[pos(now)].begin(), vec[pos(now)].end(), pre + 1) - vec[pos(now)].begin();
		if (ret == vec[pos(now)].size()) return false;
		pre = vec[pos(now)][ret];
		now = tochar((pos(now) * mul + i * add + add) % 26);
	}
	return true;
}

int main() {
	freopen("mahdi.in", "r", stdin);
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 26; i++) vec[i].clear();
		int len, mul, add;
		char str[10];
		scanf("%s%d%d%d", str, &len, &mul, &add);
		char now = str[0];
		for (int i = 0; i < len; i++) {
			vec[pos(now)].push_back(i);
			now = tochar((pos(now) * mul + 1LL * i * add + add) % 26);
		}
		printf("Case %d:\n", Case++);
		int q;
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%s%d%d%d", str, &len, &mul, &add);
			if (query(str[0], len, mul, add)) puts("BRAVO");
			else puts("REPEAT");
		}
	}
	return 0;
}
