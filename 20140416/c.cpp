#include <bits/stdc++.h>
using namespace std;

const int N = 2222;
int n; 
int pos;
double dp[N];
int a[N];
bool visit[N];

int get_value(char *str) {
	int d;
	if (isdigit(str[0])) {
		sscanf(str, "%d", &d);
		return d;
	} else if (str[0] == 'A') {
		d = 11;
	} else d = 10;
	return d;
}

int main() {
	while (cin >> n >> pos) {
		memset(dp, 0, sizeof(dp));
		memset(visit, false, sizeof(visit));
		for (int i = 1; i <= n; i++) {
			visit[pos] = true;
			dp[pos] = 1.0;
			char str[10];
			scanf("%s", str);
			if (i < n) pos += get_value(str);
		}
		//cout << pos << endl;
		for (int i = pos; i >= 1; i--) {
			if (visit[i]) continue;
			for (int j = 2; j < 10; j++) {
				dp[i] += dp[i + j] / 13;
			}
			dp[i] += dp[i + 10] * 4 / 13;
			dp[i] += dp[i + 11] / 13;
		}
		double ans = 0;
		for (int i = 1; i <= 10; i++) {
			ans += dp[i];
		}
		printf("%.15f\n", ans / 10);
	}
	return 0;
}
