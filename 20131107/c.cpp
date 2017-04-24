#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long a[510],b[510];
long long lcm[1 << 15];
long long Lcm;
int bit[1 << 15];
long long cal(long long n,long long m,long long r)
{
	long long ans = 0;
	for(int i = 1; i < (1 << n); i ++) {
		long long tmp = lcm[i];
		long long d = __gcd(Lcm,tmp);
		long long x = Lcm / d;
		if(r / x < tmp) x = r + 1;
		else x *= tmp;
		int flag = 1;
		if(bit[i] % 2 == 0) flag = -1;
		ans += flag * (r / tmp - r / x);
	}
	return ans;
}
int main()
{
	bit[0] = 0;
	for(int i = 1; i < (1 << 15); i ++)
		bit[i] = bit[i / 2] + (i & 1);
	long long n,m,lt,rt;
	while(scanf("%lld%lld%lld%lld",&n,&m,&lt,&rt) != EOF) {
		if(!n && !m && !lt && !rt) break;
		for(int i = 0; i < n; i ++)
			scanf("%lld",&a[i]);
		for(int i = 1; i <= m; i ++)
			scanf("%lld",&b[i]);
		Lcm = b[1];
		for(int i = 2; i <= m; i ++) {
			long long d = __gcd(Lcm,b[i]);
			Lcm /= d;
			if(rt / Lcm < d) {
				Lcm = rt + 1;
				break;
			}
			else Lcm *= b[i];
		}
		lcm[0] = 1;
		for(int i = 1; i < (1 << n); i ++) {
			for(int j = 0; j < n; j ++) {
				if(i & (1 << j)) {
					long long d = __gcd(lcm[i ^ (1 << j)],a[j]);
					long long x = lcm[i ^ (1 << j)] / d;
					if(rt / x < a[j]) lcm[i] = rt + 1;
					else lcm[i] = x * a[j];
					break;
				}
			}
		}
		cout << cal(n,m,rt) - cal(n,m,lt - 1) << endl;
	}
	return 0;
}
