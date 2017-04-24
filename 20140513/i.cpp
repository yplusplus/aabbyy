#include <bits/stdc++.h>
using namespace std;

int run() {
	int n;
	while (cin >> n) {
		if(n == 1) cout << 1.0 << endl;
		else if(n == 2) cout << 0.5 << endl;
		else {
			double ans = 0;
			for(int i = 1; i < n; i ++) {
				double sum = 0;
				for(int j = i + 1; j <= n; j ++) {
					sum += 1.0 / (j - 1);
				}
				sum = sum * i / n;
				ans = max(ans,sum);
			}
			cout << ans << endl;
		}
	}
	return 0;
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(20);
	ios::sync_with_stdio(0);
	freopen("princess.in", "r", stdin);
	freopen("princess.out", "w", stdout);
	return run();
}
