#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
const int N = 100010;
char s[3][N];

long long pow(long long a,long long b)
{
	long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return ans;
}

long long fac[N],rev[N];

void init()
{
	fac[0] = rev[0] = 1;
	for(int i = 1; i < N;i ++) {
		fac[i] = fac[i - 1] * i % mod;
		rev[i] = rev[i - 1] * pow(i,mod - 2) % mod;
	}
}

long long com(int n,int m)
{
	if(n < m) return 0;
	return fac[n] * rev[m] % mod * rev[n - m] % mod;
}

int judge(int n)
{
	char tmp;
	int ans = 0;
	for(int i = 0; i < (1 << n); i ++) {
		int c1 = 0,c2 = 0,c3 = 0;
		for(int j = 0; j < n; j ++) {
			if(i & (1 << j)) tmp = '1';
			else tmp = '0';
			if(s[0][j] != tmp) c1 ++;
			if(s[1][j] != tmp) c2 ++;
			if(s[2][j] != tmp) c3 ++;
		}
//		cout << c1 << " " << c2 << " " << c3 << endl;
		
		if(c1 == c2 && c2 == c3) ans ++;
		
	}
	return ans;
}

int main()
{
	init();
	for(int i = 0; i < 3; i ++)
		scanf("%s",s[i]);
	int n = strlen(s[0]);
//	cout << judge(n) << endl;
	int tot = 0;
	int x = 0,y = 0,z = 0;
	for(int i = 0; i < n; i ++)
		if(s[0][i] == s[1][i] && s[1][i] == s[2][i]) tot ++;
		else if(s[0][i] == s[1][i]) x ++;
		else if(s[0][i] == s[2][i]) y ++;
		else z ++;
	int ans = 1;
	while(tot --) ans = ans * 2 % mod;
	long long sum = 0;
	for(int i = 0; i <= x; i ++) {
		int k = (x + z) - 2 * i;
		if(k % 2 || k < 0) continue;
		k /= 2;
		int j = y + z - 2 * k;
		if(j < 0 || j % 2) continue;
		j /= 2;
		sum = (sum + com(x,i) * com(y,j) % mod * com(z,k)) % mod;
	}
	cout << ans * sum % mod << endl;
	return 0;
}