#include <bits/stdc++.h>
using namespace std;

int m[2][2] = {0,0,0,1};
int nim_mult_power(int x,int y)
{
	if(x < 2) return m[x][y];
	int a = 0;
	for(; ; a ++)
		if(x >= (1 << (1 << a)) && x < (1 << (1 << (a + 1)))) break;
	int m = 1 << (1 << a);
	int p = x / m,s = y / m,t = y % m;
	int d1 = nim_mult_power(p,s);
	int d2 = nim_mult_power(p,t);
	return (m * (d1 ^ d2)) ^ nim_mult_power(m / 2,d1);
}

int nim_mult(int x,int y)
{
	if(x < y) swap(x,y);
	if(x < 2) return m[x][y];
	int a = 0;
	for(; ; a ++)
		if(x >= (1 << (1 << a)) && x < (1 << (1 << (a + 1)))) break;
	int m = (1 << (1 << a));
	int p = x / m,q = x % m,s = y / m,t = y % m;
	int c1 = nim_mult(p,s);
	int c2 = nim_mult(p,t) ^ nim_mult(q,s);
	int c3 = nim_mult(q,t);
	return (m * (c1 ^ c2)) ^ c3 ^ nim_mult_power(m / 2,c1);
}

int nim[55][55];

void init()
{
	for(int i = 1; i <= 50; i ++)
		for(int j = 1; j <= 50; j ++)
			nim[i][j] = nim_mult(i,j);
}

int main()
{
	freopen("coins.in","r",stdin);
	freopen("coins.out","w",stdout);
	init();
	int n,m;
	scanf("%d%d",&n,&m);
	int a[55][55];
	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		char s[55];
		scanf("%s",s + 1);
		for(int j = 1; j <= m; j ++) {
			a[i][j] = s[j] - '0';
			if(a[i][j]) ans ^= nim[i][j];
		}
	}
	if(!ans) {
		cout << "Betty" << endl;
		return 0;
	}
	cout << "Ann" << endl;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			int tmp = ans;
			if(!a[i][j]) continue;
			for(int k = 0; k < i; k ++) {
				for(int r = 0; r < j; r ++) {
					tmp = ans ^ nim[i][j];
					if(k && r) tmp ^= nim[k][r];
					if(k) tmp ^= nim[k][j];
					if(r) tmp ^= nim[i][r];
					if(!tmp) {
						printf("%d %d\n",i,j);
						printf("%d %d\n",k,r);
						return 0;
					}
				}
			}
		}
	}
	return 0;
}
