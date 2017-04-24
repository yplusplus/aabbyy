#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


int fac[1300][12000];
int pri[10010];
int map[10010],tot = 0;
void prime()
{
	int a[10010];
	memset(a,0,sizeof(a));
	for(int i = 2; i <= 100; i ++)
		if(!a[i])
			for(int j = i * i; j <= 10000; j += i)
				a[j] = 1;
	for(int i = 2; i <= 10000; i ++)
		if(!a[i]) {
			pri[++ tot] = i;
			map[i] = tot;
		//	cout << tot << endl;
		}
}

int pow(int a,int b,int p)
{
	int ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % p;
		a = a * a % p;
		b /= 2;
	}
	return ans;
}

void init()
{
	for(int i = 1; i <= tot; i ++) {
		int prime = pri[i];
		fac[i][0] = 1;
		for(int j = 1; j < prime; j ++)
			fac[i][j] = fac[i][j - 1] * j % prime;
	}
}

int com(int n,int m,int p)
{
	int id = map[p];
	return fac[id][n] * pow(fac[id][m],p - 2,p) % p * pow(fac[id][n - m],p - 2,p) % p;
}

int cal(int n,int m,int p)
{
	if(2 * m > n) m = n - m;
	int ans = 1;
	int sum = n - m;
	n ++;
	//cout << n << " " << m << " " << sum << endl;
	while(m) {
		int x = n % p;
		int y = m % p;
		if(x < y) return sum % p;
		ans = ans * com(x,y,p) % p;
		n /= p,m /= p;
	}
	return (ans + sum) % p;
}

int main()
{
	prime();
	init();
	int cas = 0;
	int n,m,p;
	while(scanf("%d%d%d",&n,&m,&p) != EOF) {
		printf("Case #%d: %d\n",++ cas,cal(n,m,p));
	}
	//cout << tot << endl;
	return 0;
}