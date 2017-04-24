#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL good[] = { 1, 2, 3, 3, 4, 10 };
const LL evil[] = { 1, 2, 2, 2, 3, 5, 10 };

int main() {
	int _;
	ios::sync_with_stdio(0);
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		LL s1 = 0, s2 = 0, x;
		for (int i = 0; i < 6; ++i) {
			cin >> x;
			s1 += good[i] * x;
		}
		for (int i = 0; i < 7; ++i) {
			cin >> x;
			s2 += evil[i] * x;
		}
		cout << "Battle " << cas << ": ";
		if (s1 == s2) {
			cout << "No victor on this battle field" << endl;
		} else if (s1 < s2) {
			cout << "Evil eradicates all trace of Good" << endl;
		} else {
			cout << "Good triumphs over Evil" << endl;
		}
	}
	return 0;
}


