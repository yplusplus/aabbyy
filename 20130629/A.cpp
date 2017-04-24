#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <cmath>
using namespace std;

int a[10010];

void prime()
{
	memset(a,0,sizeof(a));
	a[0] = a[1] = 1;
	for(int i = 2; i <= 100; i ++)
		if(!a[i])
			for(int j = i * i; j <= 10000; j += i)
				a[j] = 1;
}

set<int> st1,st2;
map<string,int> ma;
int c[1010];

int change(int x)
{
	if(x == 1) return 36;
	if(x == 2) return 27;
	if(x == 3) return 18;
	return 0;
}

double getr(int n)
{
	if(n < 3) return 0;
	sort(c + 1,c + n + 1);
	return max(0.0,(c[n - 2] - 1200.0) / 100) * 1.5;
}

struct mem
{
	char s[35];
	double x;
	friend bool operator < (const mem &p,const mem &q) {
		if(fabs(p.x - q.x) > 1e-8) return p.x > q.x;
		return strcmp(p.s,q.s) < 0;
	}
}f[1010];

int main()
{
	char s[110];
	int x,y;
	int n,m,r;
	prime();
	int t;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		st1.clear();
		st2.clear();
		ma.clear();
		scanf("%d",&r);
		while(r --) {
			scanf("%d",&x);
			st1.insert(x);
		}
		scanf("%d",&r);
		while(r --) {
			scanf("%d",&x);
			st2.insert(x);
		}
		scanf("%d",&r);
		while(r --) {
			scanf("%s%d",s,&x);
			ma[s] += change(x);
		}
		int rr;
		char str[3];
		for(int i = 1; i <= n; i ++) {
			scanf("%s",f[i].s);
			f[i].x = 0;
			scanf("%s",s);
			if(ma.count(s)) f[i].x += ma[s];
			scanf("%s%d%d",str,&r,&rr);
			while(r --) {
				scanf("%d",&x);
				if(st1.count(x)) f[i].x += 2.5;
				else if(st2.count(x)) f[i].x += 1.5;
				else if(!a[x]) f[i].x += 1;
				else f[i].x += 0.3;
			}
			for(int j = 1; j <= rr; j ++)
				scanf("%d",&c[j]);
			f[i].x += getr(rr);
			if(str[0] == 'F') f[i].x += 33;
		}
		sort(f + 1,f + n + 1);
		for(int i = 1; i <= m; i ++)
			printf("%s %.3lf\n",f[i].s,f[i].x);
	}
	return 0;
}






