#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int f[8000010];

unsigned long long get_period(int prime,int exp)
{
	unsigned long long ans = 1;
	for(int i = 1; i < exp; i ++) ans *= prime;
	f[0] = f[1] = 1;
	for(int i = 2; ; i ++) {
		f[i] = (f[i - 1] + f[i - 2]) % prime;
		if(f[i] == 1 && f[i - 1] == 1) return ans * (i - 1);
		//cout << prime << " " << i << endl;
	}
}

void solve()
{
	int n;
	scanf("%d",&n);
	unsigned long long ans = 1;
	if(n == 1) {
		cout << 1 << endl;
		return;
	}
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		int cnt = 0;
		while(n % i == 0) n /= i,cnt ++;
		unsigned long long period = get_period(i,cnt);
		unsigned long long d = __gcd(ans,period);
		ans = ans / d * period;
	}
	if(n > 1) {
		unsigned long long period = get_period(n,1);
		unsigned long long d = __gcd(ans,period);
		ans = ans / d * period;
	}
	cout << ans << endl;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case #%d: ",cas);
		solve();
	}
	return 0;
}

