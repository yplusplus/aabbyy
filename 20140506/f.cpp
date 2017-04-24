#include <bits/stdc++.h>
using namespace std;

const int DG = 6;
const int MOD = 1000000;
typedef vector<int> VI;
struct BigNumber {
	VI a;
	BigNumber() {}
	BigNumber(string s) {
		a.clear();
		int ep = 1, sum = 0;
		for (int i = s.length() - 1; i >= 0; --i) {
			sum += ep * (s[i] - '0');
			ep *= 10;
			if (ep >= MOD) {
				a.push_back(sum);
				ep = 1;
				sum = 0;
			}
		}
		if (sum) a.push_back(sum);
		//cout << "Build" << endl;
	}
	BigNumber(int x) {
		a.clear();
		a.push_back(x);
		//cout << "Build" << endl;
	}
	void fix() { while (a.size() > 1 && a[a.size() - 1] == 0) a.pop_back(); }
	void print() {
		for (int i = a.size() - 1; i >= 0; --i) {
			//cout << i << ' ' << a[i] << ' ' << a.size() - 1 << endl;
			if (i == a.size() - 1) {
				printf("%d", a[i]);
			} else {
				printf("%06d", a[i]);
			}
		}
	}
	int size() const { return a.size(); }
} ;

void operator *= (BigNumber &a, int x) {
	int n = a.size();
	a.a.resize(n + 1, 0);
	for (int i = 0; i < n; ++i) a.a[i] *= x;
	for (int i = 0; i < n; ++i) {
		if (a.a[i] >= MOD) {
			a.a[i + 1] += a.a[i] / MOD;
			a.a[i] %= MOD;
		}
	}
	a.fix();
}

bool operator < (const BigNumber &a, const BigNumber &b) {
	if (a.size() != b.size()) return a.size() < b.size();
	int n = a.size();
	for (int i = n - 1; i >= 0; --i) {
		//cout << a.size() << ' ' << b.size() << ' ' << n << ' ' << a.a[i] << ' ' << b.a[i] << endl;
		if (a.a[i] != b.a[i]) return a.a[i] < b.a[i];
	}
	return 0;
}

const int N = 1 << 10;
char buffer[N];

int run() {
	int answer = 0;
	for (int i = 0; i < 3; ++i) {
		cin >> buffer;
		BigNumber a(1), temp(buffer);
		//temp.print(); puts("");
		while (a < temp) {
			a *= 2;
			++answer;
			//a.print(); puts("");
		}
	}
	cout << answer << endl;
	return 0;
}

int main() {
	freopen("puzzle.in", "r", stdin);
	freopen("puzzle.out", "w", stdout);
	//ios::sync_with_stdio(0);
	return run();
}
