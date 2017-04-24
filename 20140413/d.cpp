#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

long long cal(long long n)
{
	long long inv2 = (mod + 1) / 2,inv3 = (mod + 1) / 3;
	long long ans = n * (n + 1) % mod * (2 * n + 1) % mod * inv2 % mod * inv3 % mod - n * (n + 1) % mod * inv2 % mod;
	ans = (ans % mod + mod) % mod;
	return ans;
}

int main()
{
	long long n;
	cin >> n;
	long long tmp = cal(n) + cal(n - 1);
	tmp = 2 * tmp % mod;
	long long ans = n * n % mod * n % mod * n % mod - n * n % mod;
	ans = (ans - tmp) % mod + mod;
	ans = ans % mod;
	ans = ans * ((mod + 1) / 2) % mod;
	cout << ans << endl;
	return 0;
}
