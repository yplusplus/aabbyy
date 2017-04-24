#include <bits/stdc++.h>
using namespace std;

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
	y = tmp - a / b * y;
	return d;
}

long long ansx,ansy;
int digit1,digit2;
long long n;

void change(int d1,long long x,int d2,long long y)
{
	digit1 = d1,digit2 = d2;
	ansx = x,ansy = y;
}

void update(int d1,long long x,int d2,long long y)
{
	//cout << x << " " << d1 << " " << y << " " << d2 << endl;
	if(x + y > ansx + ansy) return;
	if(x + y < 6) {
		int ans = 0;
		for(int i = 1; i <= x; i ++) ans = ans * 10 + d1;
		for(int i = 1; i <= y; i ++) ans = ans * 10 + d2;
		if(ans == n) return;
	}
	if(x + y < ansx + ansy) change(d1,x,d2,y);
	else if(x + y == ansx + ansy) {
		if(digit1 > d1) change(d1,x,d2,y);
		else if(digit1 == d1) {
			if(x == ansx) {
				if(digit2 > d2) change(d1,x,d2,y);
			}
			else if(x > ansx) {
				if(d1 < digit2) change(d1,x,d2,y);
			}
			else {
				if(digit1 > d2) change(d1,x,d2,y);
			}
		}
	}
}

int p10[1000010];
int num[1000010][2];
int visit[100010];
void solve(long long n)
{
	long long m = n * 9;
	for(int i = 0; i <= m; i ++) p10[i] = 0;
	long long tmp = 1;
	for(int i = 0; i < 3 * m; i ++) {;
		if(i && p10[tmp] < 2) {
			num[tmp][p10[tmp] ++] = i;
		}
		tmp = 10 * tmp % m;
	}
	for(int i = 0; i < m; i ++) p10[i] = min(2,p10[i]);
	for(int i = 1; i < 10; i ++) {
		long long p = i % n;
		for(int j = 0; j < n; j ++) visit[j] = 0;
		for(int len = 1; len <= ansx + ansy; len ++) {
			if(visit[p] > 1) break;
			visit[p] ++;
			for(int b = 0; b < 10; b ++) {
				if(b == i) continue;
				long long d = ex_gcd(9 * p + b,m);
				long long mul = !b ? m : b;
				if(mul % d) continue;
				x = x % m * (mul / d) % m;
				if(x < 0) x += m;
				int step = m / d;
				y = x;
				while(x < m) {
					for(int j = 0; j < p10[x]; j ++) {
						update(i,len,b,num[x][j]);
					}
					x += step;
				}
				x = y;
				while(x >= 0) {
					for(int j = 0; j < p10[x]; j ++)
						update(i,len,b,num[x][j]);
					x -= step;
				}
			}
			p = (10 * p + i) % n;
		}
	}
}


int main()
{
	while(scanf("%lld",&n) != EOF) {
		if(!n) break;
		ansx = 1LL << 60;
		ansy = 1LL << 60;
		solve(n);
		printf("%lld: %lld %d %lld %d\n",n,ansx,digit1,ansy,digit2);
	}
	return 0;
}
