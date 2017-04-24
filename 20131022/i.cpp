#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n) {
		if ((n & 1) && n % 6 != 3) {
			vector<int> vec;
			for (int i = 2; i <= n; i += 2) {
				vec.push_back(i);
			}
			for (int i = 1; i <= n; i += 2) {
				vec.push_back(i);
			}
			cout << "Yes" << endl;
			for (int i = 0; i < n; i++) {
				cout << vec[i];
				if (i + 1 == n) cout << endl;
				else cout << " ";
			}
		} else cout << "No" << endl;
	}
	return 0;
}

