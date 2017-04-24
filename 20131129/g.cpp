#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 111;
pair<int, int> a[N];
bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	return a.second < b.second;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n = 0;
		while (true) {
			scanf("%d%d", &a[n].first, &a[n].second);
			if (a[n] == make_pair(0, 0)) break;
			n++;
		}
		sort(a, a + n, cmp);
		int ans = 0;
		int r = -1;
		for (int i = 0; i < n; i++) {
			if (a[i].first >= r) {
				ans++;
				r = a[i].second;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

