#include <bits/stdc++.h>
using namespace std;

int run() {
	string container;
	int cas = 0;
	while (cin >> container && "end" != container) {
		int n = container.length();
		set<char> cnt;
		for (int i = 0; i < n; ++i) {
			set<char>::iterator si = cnt.lower_bound(container[i]);
		   	if (si == cnt.end()) cnt.insert(container[i]);
			else {
				cnt.erase(si);
				cnt.insert(container[i]);
			}
		}
		cout << "Case " << ++cas << ": " << cnt.size() << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
