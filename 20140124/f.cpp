#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

long long dp[55][110];

int get_phi(int n)
{
	int ans = n;
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		ans = ans / i * (i - 1);
		while(n % i == 0) n /= i;
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans;
}

long long pow(long long a,long long b,long long c)
{
	long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % c;
		a = a * a % c;
		b /= 2;
	}
	return ans;
}

void add(long long &x,long long y,long long mod)
{
	x = x + y;
	x %= mod;
}

char s[100010],str[100010];
int main()
{
	int a[55];
	int n,c;
	int mod = 1234567;
	while(scanf("%d%s%d",&n,str,&c) != EOF) {
		memset(dp,0,sizeof(dp));
		dp[0][1] = 1;
		for(int i = 1; i <= n; i ++)\
			scanf("%d",&a[i]);
		if(c == 1) {
			cout << 0 << endl;
			continue;
		}
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < c; j ++) {
				dp[i + 1][j] = dp[i][j];
			}
			for(int j = 0; j < c; j ++) {
				add(dp[i + 1][(j * a[i + 1]) % c],dp[i][j],mod);
			}
		}
		memset(s,0,sizeof(s));
		for(int i = 0; str[i]; i ++) {
			if(str[i] == '0') continue;
			int cc = 0;
			for(int j = i; str[j]; j ++)
				s[cc ++] = str[j];
			break;
		}
		long long p;
		if(strlen(s) > 8) sscanf(s,"%lld",&p);
		else {
			p = 0;
			int phi = get_phi(c);
			for(int i = 0; s[i]; i ++)
				p = (10 * p + (s[i] - '0')) % phi;
			p += phi;
		}
		long long ans = 0;
		dp[n][1] --;
		if(dp[n][1] < 0) dp[n][1] += mod;
		for(int i = 1; i < c; i ++) {
			if(!dp[n][i]) continue;
			ans = (ans + dp[n][i] * pow(i,p,c)) % mod;
		}
		cout << ans << endl;
	}
	return 0;
}
