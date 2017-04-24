#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int W = 55555;
int n, w;
int dp[W];
bool cmp(const pair<int, int> &x, const pair<int, int> &y) {
	return x.second * y.first > x.first * y.second;
}

int main() {
	while (~scanf("%d%d", &n, &w)) {
		memset(dp, 0, sizeof(dp));
		vector<pair<int, int> > vec;
		for (int i = 0; i < n; i++) {
			int a, b, t;
			scanf("%d%d%d", &a, &b, &t);
			if (t) {
				vec.push_back(make_pair(a, b));
			} else {
				for (int j = w; j >= a; j--) {
					dp[j] = max(dp[j], dp[j - a] + b);
				}
			}
		}
		sort(vec.begin(), vec.end(), cmp);
		double ans = 0.0;
		for (int i = 0; i <= w; i++) {
			double tmp = dp[i];
			int x = w - i;
			for (int j = 0; j < vec.size(); j++) {
				if (x > vec[j].first) {
					x -= vec[j].first;
					tmp += vec[j].second;
				} else {
					tmp += vec[j].second * 1.0 / vec[j].first * x;
					break;
				}
			}
			ans = max(ans, tmp);
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
