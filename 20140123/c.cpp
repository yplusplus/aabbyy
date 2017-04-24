#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
long long pri[N];
int a[N * 2];
int cnt;
bool c[N];

void prime()
{
	cnt = 0;
	memset(a,0,sizeof(a));
	for(int i = 2; i * i < N * 2; i ++)
		if(!a[i]) {
			for(int j = i * i; j < N * 2; j += i)
				a[j] = 1;
		}
	for(int i = 2; i < N * 2; i ++)
		if(!a[i]) pri[cnt ++] = i;
}

long long x,y;
long long ex_gcd(long long a,long long b)
{
	if(!b) {
		x = 1,y = 0;
		return a;
	}
	long long d = ex_gcd(b,a % b);
	long long tmp = x;
	x = y;
	y = tmp - (a / b) * y;
	return d;
}

int isprime(long long b)
{
	if(b < 2) return 0;
	for(int i = 0; pri[i] * pri[i] <= b; i ++)
		if(b % pri[i] == 0) return 0;
	return 1;
}
	
int main()
{
	prime();
	long long a,b,L,U;
	int cas = 0;
	while(scanf("%lld",&a) != EOF) {
		if(!a) break;
		scanf("%lld%lld%lld",&b,&L,&U);
		printf("Case %d: ",++ cas);
		if(b == 0 && a != 1) {
			if(isprime(a) && L <= 1 && U >= 1) printf("1\n");
			else printf("0\n");
			continue;
		}
		if(__gcd(a,b) > 1) {
			if(L == 0) printf("%d\n",isprime(b));
			else printf("0\n");
			continue;
		}
		int len = U - L + 1;
		for(int i = 0; i <= len; i ++) c[i] = true;
		for(int i = 0; ; i ++) {
			if(pri[i] * pri[i] > a * U + b) break;
			long long p = pri[i];
			if(__gcd(a,p) > 1) continue;
			long long d = ex_gcd(a,p);
			x *= (p - b % p);
			//cout << x << " " << p << endl;
			long long st = (L - x) / p;
			long long ed = (U - x) / p;
		//	cout << p << " " << x << endl;
			for(long long j = st - 8; j <= ed + 8; j ++) {
				if(x + p * j >= L && x + p * j <= U) {
					if((x + p * j) * a + b == p) continue;
					c[x + p * j - L] = false;
			//		if(x + p * j == 2) cout << p << " " << x << endl;
			//		cout << x + p * j - L << endl;
				}
			}
		}
		for(int i = 0; i < len && i < 3; i ++)
			if(!isprime((i + L) * a + b)) c[i] = false;
		long long ans = 0;
		for(int i = 0; i < len; i ++)
			if(c[i]) ans ++;
		printf("%lld\n",ans);
	}
	return 0;
}
