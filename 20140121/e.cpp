#include <bits/stdc++.h>
using namespace std;

long long fac[55];
int c[55][55];
int bit[1 << 17];

void init()
{
	for(int i = 0; i < 55; i ++) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	fac[0] = 1;
	for(long long i = 1; i < 20; i ++) fac[i] = fac[i - 1] * i;
}

int main()
{
	int t,id,n,m;
	cin >> t;
	init();
	while(t --) {
		cin >> id >> n >> m;
		long long ans = 0;
		for(int i = 0; i <= m; i ++) {
			long long tmp = c[m][i] * fac[n - i];
			if(i & 1) ans -= tmp;
			else ans += tmp;
		}
		cout << id << " " << ans << endl;
	}
	return 0;
}	
