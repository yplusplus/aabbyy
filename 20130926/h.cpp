#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;


const int N = 11111;

pair<int, int> mon[N];
int n, m;

bool cmp(const pair<int, int> &x, const pair<int, int> &y) {
	return x.first * y.second < y.first * x.second;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		long long ans = 0;
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a = (a / m) + (a % m > 0);
			mon[i] = make_pair(a, b);
			ans += b;
		}
		sort(mon, mon + n, cmp);
		long long cnt = 0;
		for (int i = 0; i < n; i++) {
			ans += (cnt + mon[i].first - 1) * mon[i].second;
			cnt += mon[i].first;
		}
		printf("Case #%d: ", Case++);
		cout << ans << endl;
	}
	return 0;
}

