#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cctype>
using namespace std;

#define ll long long
const int N = 111111;
ll sum[N], rev[N];
ll p[N], x[N];
ll cost[N], k;
int n;

ll read() {
	char ch;
	ch = getchar();
	while (ch > '9' || ch < '0') ch = getchar();
	ll t = 0;
	while (isdigit(ch)) {
		t = t * 10 + ch - '0';
		ch = getchar();
	}
	return t;
}

bool check2(int mid) {
	int j = n + 1, t = 0, pos = n + 1;
	int tmp = (mid + 1) >> 1;
	//cout << "****************" << endl;
	//cout << mid << endl;
	for (int i = n; i >= 1; i--) {
		t -= p[i + 1];
		while (t < mid && j - 1 >= 1) {
			j--;
			t += p[j];
		}
		if (t < mid) break;
		pos = min(pos, i);
		while (rev[pos] - rev[i + 1] < tmp) pos--;
		//cout << i << " " << pos << endl;
		ll pain = (sum[pos - 1] - sum[j - 1] - (t - mid)) * x[pos] - (cost[pos - 1] - cost[j - 1] - x[j] * (t - mid))
			+ ((cost[i] - cost[pos]) - (sum[i] - sum[pos]) * x[pos]);
		if (pain <= k) return true;
	}
	return false;
}

bool check(int mid) {
	int j = 0, t = 0, pos = 0;
	int tmp = (mid + 1) >> 1;
	//cout << "****************" << endl;
	//cout << mid << endl;
	for (int i = 1; i <= n; i++) {
		t -= p[i - 1];
		while (t < mid && j + 1 <= n) {
			j++;
			t += p[j];
		}
		if (t < mid) break;
		pos = max(pos, i);
		while (sum[pos] - sum[i - 1] < tmp) pos++;
		ll pain = (sum[pos - 1] - sum[i - 1]) * x[pos] - (cost[pos - 1] - cost[i - 1])
			+ ((cost[j] - cost[pos] - x[j] * (t - mid)) - (sum[j] - sum[pos] - (t - mid)) * x[pos]);
		//cout << "pain1 = " << pain << endl;
		if (pain <= k) return true;

	}
	return false;
}

pair<ll, ll> peach[N];

int main() {
	while (~scanf("%d", &n)) {
		k = read();
		p[0] = p[n + 1] = 0;
		sum[0] = rev[n + 1] = 0;
		cost[0] = 0;
		for (int i = 1; i <= n; i++) {
			peach[i].first = read();
			peach[i].second = read();
		}

		sort(peach + 1, peach + 1 + n);

		for (int i = 1; i <= n; i++) {
			p[i] = peach[i].second;
			x[i] = peach[i].first;
			cost[i] = cost[i - 1] + p[i] * x[i];
		}
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + p[i];
		for (int i = n; i >= 1; i--) rev[i] = rev[i + 1] + p[i];

		int ans = -1;
		int l = 0, r = (int) sum[n];
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid) || check2(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}