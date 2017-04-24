#include <bits/stdc++.h>
using namespace std;

int run() {
	int n;
	cin >> n;
	while (n--) {
		string str;
		cin >> str;
		int l = str.length();
		str += str;
		int cnt = 0;
		for (int i = 0; i < l; ++i) {
			bool ok = 1;
			for (int j = 0; j < l; ++j) {
				if (str[j] != str[i + j]) {
					ok = 0;
					break;
				}
			}
			cnt += ok;
		}
		cout << cnt << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
