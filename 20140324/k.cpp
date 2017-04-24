#include <bits/stdc++.h>
using namespace std;

const int N = 111;
int val[N];
int n;

int main() {
	freopen("cubes.in", "r", stdin);
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &val[i]);
		}
		sort(val, val + n);
		reverse(val, val + n);
		vector<int> a, b;
		for (int i = 0; i < n; i++) {
			if (i & 1) a.push_back(val[i]);
			else b.push_back(val[i]);
		}
		reverse(b.begin(), b.end());
		for (int i = 0; i < b.size(); i++) {
			a.push_back(b[i]);
		}
		printf("Case %d:\n", Case++);
		for (int i = 0; i < n; i++) {
			printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
