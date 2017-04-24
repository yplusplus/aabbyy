#include <bits/stdc++.h>
using namespace std;

map<string, string> slogan;

int main() {
	string buf, a, b;
	int n;
	while (cin >> n) {
		getline(cin, buf);
		slogan.clear();
		for (int i = 0; i < n; ++i) {
			getline(cin, a);
			getline(cin, b);
			slogan[a] = b;
		}
		cin >> n;
		getline(cin, buf);
		for (int i = 0; i < n; ++i) {
			getline(cin, a);
			cout << slogan[a] << endl;
		}
	}
	return 0;
}
