#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[] = {2,3,5,7,11};
long long phi(long long n)
{
	long long ans = n;
	for(int i = 0; i < 5; i ++) {
		if(ans % a[i]) continue;
		ans = ans / a[i] * (a[i] - 1);
	}
	return ans;
}

long long pow(long long a,long long b,long long c)
{
	long long ans = 1;
	a %= c;
	while(b) {
		if(b & 1LL) ans = ans * a % c;
		a = a * a % c;
		b /= 2;
	}
	return ans;
}

long long solve(long long p,long long m)
{
	if(m == 1) return 0;
//	cout << m << " " << phi(m) << endl;
	long long ans = pow(p,solve(p,phi(m)) + phi(m),m);
//	cout << p << " " << m << " " << phi(m) << " " << ans << endl;
	return ans;

}

int main()
{
	long long fac[25];
	long long p,m;
	fac[0] = 1;
	for(int i = 1; i < 15; i ++) fac[i] = fac[i - 1] * i;
	bool flag = false;
	while(scanf("%lld%lld",&p,&m) != EOF) {
		if(flag) printf("\n");
		flag = true;
		printf("%lld\n",solve(p,fac[m]));
	}
}

