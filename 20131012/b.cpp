#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-5;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
const int N = 22;
double a[N];

void check(int n, double r) {
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) a[j] *= 2;
		if (sgn(a[i - 1] - a[i] * r) < 0) {
			cout << "Yes" << endl;
			return ;
		}
	}
	cout << "No" << endl;
}

int main() {
	int n, _;
	double r;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> n >> r;
		for (int i = 0; i < n; i++) cin >> a[i];
		cout << "Case #" << cas << ":" << endl;
		check(n, r);
	}
	return 0;
}


