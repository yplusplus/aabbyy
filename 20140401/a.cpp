#include <bits/stdc++.h>
using namespace std;

int run() {
	int n;
	while (cin >> n) {
		vector<char> has;
		string buf;
		for (int i = 0; i < n; ++i) {
			cin >> buf;
			has.push_back(buf[0]);
		}
		sort(has.begin(), has.end());
		int k = unique(has.begin(), has.end()) - has.begin();
		int ans = k;
		for (int i = 0; i < k; ++i) if (has[i] != 'A' + i) {
			ans = i;
			break;
		}
		cout << ans << endl;
	}
	return 0;
}

int main() {
	freopen("arrange.in", "r", stdin);
	freopen("arrange.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
