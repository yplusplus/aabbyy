#include <bits/stdc++.h>
using namespace std;

const int M = 35;
const int N = 111111;
long long n;
long long ct[M];
bool is_prime[N];
int prime[N], tot;
long long c[M][M];

void get_factor() {
	tot = 0;
	memset(is_prime, true, sizeof(is_prime));
	for (int i = 2; i < N; i++) {
		if (is_prime[i]) {
			prime[tot++] = i;
			for (long long j = 1LL * i * i; j < N; j += i) {
				is_prime[j] = false;
			}
		}
	}
}

int main() {
	ct[1] = 1;
	for (int i = 2; i < M; i++) {
		ct[i] = 0;
		for (int j = 1; j < i; j++) {
			ct[i] += ct[j] * ct[i - j];
		}
	}
	for (int i = 0; i < M; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++) {
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	}
	get_factor();
	while (cin >> n) {
		int sum = 0;
		long long ans = 1;
		for (int i = 0; i < tot; i++) {
			if (n % prime[i] == 0) {
				int cnt = 0;
				while (n % prime[i] == 0) {
					cnt++;
					n /= prime[i];
				}
				sum += cnt;
				ans = ans * c[sum][cnt];
			}
		}
		if (n > 1) {
			sum++;
			ans = ans * c[sum][1];
		}
		ans *= ct[sum];
		cout << ans << endl;
	}
	return 0;
}
