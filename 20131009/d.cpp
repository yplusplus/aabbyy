#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5010;
const int mod = 1000000007;
int c[N],a[N];
long long fac[N],rev[N];

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

int com(int n,int m)
{
	if(n < m) return 0;
	return fac[n] * rev[n - m] % mod * rev[m] % mod;
}

int main()
{
	fac[0] = rev[0] = 1;
	for(int i = 1; i < N;i ++) {
		fac[i] = fac[i - 1] * i % mod;
		rev[i] = rev[i - 1] * pow(i,mod - 2) % mod;
	}
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&a[i]);
	int x = 0,y = 0,z = 0;
	int xx,yy;
	scanf("%d%d",&xx,&yy);
	for(int i = 1; i <= n; i ++)
		if(a[i] < a[xx]) x ++;
		else if(a[i] > a[xx]) z ++;
		else y ++;
	y --;
	//cout << x << " " << y << " " << z << endl;
	long long ans = 0;
	for(int i = 0; i <= x && i < yy; i ++)
		for(int j = 0; j <= z; j ++)
			if(i + j + 1 <= m) {
				long long tmp = com(x,i) * 1LL * com(z,j) % mod;
				int ly = m - i - j - 1;
				ly = min(ly,y);
				if(ly + i + j + 1 != m) continue;
				if(i + ly >= yy - 1) {
					tmp = tmp * com(y,ly) % mod;
			   		ans += tmp;
					ans %= mod;
				//	cout << i << " " << j << " " << ly << " " << tmp << endl;
				}
			}
	cout << ans << endl;
	return 0;
}	

