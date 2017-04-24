#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
set<int> digit;

void getDigit(LL a) {
	do {
		digit.insert(a % 10);
		a /= 10;
	} while (a > 0);
}

int run() {
	LL a;
	while (cin >> a) {
		digit.clear();
		int answer = 0;
		while (digit.size() < 10) {
			++answer;
			getDigit(a * answer);
		}
		cout << answer << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
