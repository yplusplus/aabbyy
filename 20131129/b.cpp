#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000000;
int pri[1000010],a[1000010],mapp[1000010];

void prime()
{
	memset(a,0,sizeof(a));
	for(int i = 2; i * i < 1000010; i ++)
		if(!a[i])
			for(int j = i * i; j < 1000010; j += i)
				a[j] = 1;
	for(int i = 0, j = 2; j <= 1000000; j ++)
		if(!a[j]) {
			pri[i ++] = j;
			mapp[j] = i - 1;
		}
}

int cal(int n,int m)
{
	int ans = 0;
	long long mul = m;
	while(mul <= n) {
		ans += n / mul;
		mul *= m;
	}
	return ans;
}

/*
struct bignum
{
	long long a[5];
	void init() {
		for(int i = 0; i < 5; i ++) a[i] = 0;
		a[0] = 1;
	}
	void mul(int x) {
		for(int i = 0; i < 5; i ++) {
			a[i] *= x;
		}
		for(int i = 0; i < 4; i ++) {
			a[i + 1] += a[i] % mod;
			a[i] /= 10;
		}
	}
};
*/

long long f[100010];
int main()
{
	prime();
	int n,m;
	/*
	long long tot = 0;
	for(int i = 0; pri[i] <= 100000; i ++)
		tot += cal(100000,pri[i]);
	cout << tot << endl;
	*/
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		long long ans1 = 1,ans2 = 1;
		for(int i = 0; i <= n; i ++) f[i] = 1;
		for(int i = 0; ; i ++) {
			if(pri[i] <= n) {
				int x = cal(n,pri[i]);
				for(int j = m; j <= x; j ++) {
					f[j] *= (x / j + 1);
				}
			}
			else break;
		}
		long long ans = 0;
		long long sum = 0;
		for(int i = n; i >= m; i --) {
			f[i] -= sum;
			sum += f[i];
		}
		for(int i = m; i <= n; i ++) {
			long long x = f[i],y = f[i] - 1;
			if(x & 1LL) y /= 2;
			else x /= 2;
			ans += x * y;
		}
		cout << ans << endl;
	}
	return 0;
}
