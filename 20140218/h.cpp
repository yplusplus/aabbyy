#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int n;
int a[N], b[N];
vector<int> vec;
int visit[N];

int main() {
	int Case = 1;
	while (~scanf("%d", &n), n) {
		vec.clear();
		int gmin = 1111;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			gmin = min(gmin, a[i]);
			vec.push_back(a[i]);
		}
		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		for (int i = 0; i < n; i++) {
			b[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
			//cout << b[i] << " ";
		}
		//cout << endl;
		int ans = 0;
		memset(visit, -1, sizeof(visit));
		//cout << gmin << endl;
		for (int i = 0; i < n; i++) {
			if (visit[i] == -1) {
				int sum = 0;
				int mi = 1111;
				int cnt = 0;
				while (visit[i] == -1) {
					cnt++;
					visit[i] = true;
					i = b[i];
					sum += vec[b[i]];
					mi = min(mi, vec[b[i]]);
					//cout << i << " ";
				}
				//cout << endl;
				//cout << cnt << " " << mi << " " << sum << endl;
				ans += min(sum - mi + (cnt - 1) * mi, 2 * (mi + gmin) + (cnt - 1) * gmin + sum - mi);
			}
		}
		printf("Case %d: %d\n\n", Case++, ans);
	}
	return 0;
}
