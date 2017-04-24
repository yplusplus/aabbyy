#include <bits/stdc++.h>
using namespace std;

const int N = 60;
long long fib[N];
int n, m;

long long calc(long long n, long long m) {
	for (int i = N - 1; i >= 2; i--) {
		if (n % fib[i] == 0) {
			return n * m - n / fib[i] * m;
		}
	}
	return -1;
}

int main() {
	fib[0] = fib[1] = 1;
	for (int i = 2; i < N; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	//cout << fib[N - 1] << endl;
	while (cin >> n >> m) {
		long long ans = max(calc(n, m), calc(m, n));
		if (ans == -1) ans = 0;
		cout << ans << endl << endl;
	}
	return 0;
}
