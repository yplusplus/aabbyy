#include <bits/stdc++.h>
using namespace std;

int cal(int x) {
	vector<int> prm;
	int i = 2;
	while (x > 1) {
		if (x % i == 0) {
			prm.push_back(i);
			while (x % i == 0) x /= i;
		}
		i++;
	}
	return prm[prm.size() - 1] - accumulate(prm.begin(), prm.end() - 1, 0);
}

int main() {
	int a, b;
	while (cin >> a >> b) cout << (cal(a) > cal(b) ? 'a' : 'b') << endl;
	return 0;
}
