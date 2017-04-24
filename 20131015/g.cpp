#include <bits/stdc++.h>
using namespace std;

const int N = 2222;
int a[N], pos[N];
int main() {
	int n;
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			pos[a[i]] = i;
		}
		for (int i = 1; i <= n; i++) {
			int t = pos[i];
			int best = 0, worst = 0;
			for (int j = 1; j < t; j++) {
				best += a[j] > i;
			}
			for (int j = t + 1; j <= n; j++) {
				worst += a[j] < i;
			}
			best++;
			worst = n - worst;
			cout << best << " " << worst << endl;
		}
	}
	return 0;
}

