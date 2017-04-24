#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10000010;
bool a[10000010];
int pri[1000010],tot;

void prime()
{
	memset(a,false,sizeof(a));
	for(int i = 2; i * i < 10000010; i ++)
		if(!a[i])
			for(int j = i * i; j < 10000010; j += i)
				a[j] = true;
	tot = 0;
	for(int i = 2; i < 10000000; i ++)
		if(!a[i]) pri[tot ++] = i;
}

long long fac[55],num[55];
int cnt;

void factor(long long n)
{
	memset(num,0,sizeof(num));
	cnt = 0;
	for(int i = 0; i < tot && 1LL * pri[i] * pri[i] <= n; i ++) {
		if(n % pri[i]) continue;
		while(n % pri[i] == 0) n /= pri[i],num[cnt] ++;
		fac[cnt ++] = pri[i];
	}
	if(n > 1) {
		num[cnt] = 1;
		fac[cnt ++] = n;
	}
}

long long cal(long long n,long long x)
{
	long long y = x;
	long long ans = 0;
	while(x <= n) {
		ans += n / x;
		if(n / x < y) break;
		x *= y;
	}
	return ans;
}

void solve(long long n,long long m)
{
	if(m == 1) {
		cout << "inf" << endl;
		return;
	}
	factor(m);
	//cout << "fuck" << endl;
	long long ans = 1LL << 61;
	for(int i = 0; i < cnt; i ++) {
		ans = min(ans,cal(n,fac[i]) / num[i]);
	}
	cout << ans << endl;
}

int main()
{
	prime();
//	ios::sync_with_stdio(false);
	long long t,n,m;
	scanf("%I64d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%I64d%I64d",&n,&m);
		printf("Case %d: ",cas);
		solve(n,m);
	}
	return 0;
}