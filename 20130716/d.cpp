#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long mod = 1000000007;

//caculate n * (n - 1) - (n - 1) * (2 * n - 1) / 3)
long long cal(long long n)
{
	long long ans = n * (n - 1) % mod;
	long long x = n - 1,y = 2 * n - 1;
	if(x % 3 == 0) x /= 3;
	else y /= 3;
	ans = (ans - x * y) % mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main()
{
	int t;
	long long n;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%lld",&n);
		printf("Case #%d: ",cas);
		if((n - 1) % 3 && (2 * n - 1) % 3) {
			printf("not integer\n");
			continue;
		}
		long long x = cal(n);
		long long ans = (n * n % mod * x + 2 * x * x % mod) % mod;
		printf("%lld\n",ans);
	}
	return 0;
}


