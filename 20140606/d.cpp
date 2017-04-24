#include <bits/stdc++.h>
using namespace std;

long long c[65][65];
int pri[110];
long long fac[110][110];
long long ans;
void dfs(int pos,int lim,int m,long long x,long long n,int id)
{
	if(x >= ans) return;
	if(!m) {
		if(n == 1) {
			ans = x;
		//	cout << id << " " << pos << " " << lim << " " << m << " " << x << endl;
		}
		return;
	}
	long long ut = ans / x,mul = 1;
	for(int i = 1; i <= m && i <= lim; i ++) {
		if(ans / x < pri[pos]) break;
		x *= pri[pos];
		if(n % c[m][i]) continue;
		//if(id == 15) cout << pos << " " << i << " " << x << endl;
		dfs(pos + 1,i,m - i,x,n / c[m][i],id);
	}
}

int main()
{
	for(int i = 2,j = 0; j <= 100; i ++) {
		bool flag = true;
		for(int k = 2; k < i; k ++) {
			if(i % k == 0) flag = false;
		}
		if(flag) {
			pri[j ++] = i;
		}
	}
	for(int i = 0; i < 65; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	long long n;
	while(scanf("%lld",&n) != EOF) {
		ans = (1ULL << 63) - 1;
		for(int i = 1; i <= 62; i ++) {
			dfs(0,i,i,1,n,i);
		}
		printf("%lld %lld\n",n,ans);
	}
	return 0;
}
