#include <bits/stdc++.h>
using namespace std;

int f[10000010];

int get_period(int n)
{
	f[1] = f[2] = 1;
	for(int i = 3; ; i ++) {
		f[i] = (f[i - 1] + f[i - 2]);
		if(f[i] >= n) f[i] -= n;
		if(f[i] == 1 && f[i - 1] == 1) return i - 2;
	}
}

long long solve(int n)
{
	long long ans = 1;
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		int cnt = 0;
		while(n / i == 0) {
			if(cnt == 0) {
				long long x = get_period(i);
				ans = ans / __gcd(ans,x) * x;
			}
			else ans = ans / __gcd(ans,(long long)i) * i;
			cnt ++;
			n /= i;
		}
	}
	if(n > 1) {
		long long x = get_period(n);
		ans = ans / __gcd(ans,x) * x;
	}
	return ans;
}

int main()
{
	int t,id,n;
	cin >> t;
	while(t --) {
		cin >> id >> n;
		cout << id << " " << solve(n) << endl;
	}
	return 0;
}
