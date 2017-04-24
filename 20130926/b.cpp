#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

const int N = 100010;
const long long key1 = 31;
const long long key2 = 131;
const int mod1 = 1000000007;
const int mod2 = 13141679;
struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.x != q.x) return p.x < q.x;
		return p.y < q.y;
	}
};
set<point> st;
int c1[N],c2[N];
char s[N];

int change(char c)
{
	return c - 'a' + 1;
}

void init(int n)
{
	while(n --) {
		scanf("%s",s);
		int ans1 = 0,ans2 = 0;
		for(int i = 0; s[i]; i ++) {
			ans1 = (1LL * ans1 * key1 % mod1 + change(s[i])) % mod1;
			ans2 = (1ll * ans2 * key2 % mod2 + change(s[i])) % mod2;
		}
		st.insert(point(ans1,ans2));
	}
	c1[0] = c2[0] = 1;
	for(int i = 1; i < N; i ++) {
		c1[i] = 1LL * c1[i - 1] * key1 % mod1;
		c2[i] = 1LL * c2[i - 1] * key2 % mod2;
	}
}


struct tree
{
	int lt,rt;
	int sum1,sum2;
}a[N * 4];

int len(int step)
{
	return a[step].rt - a[step].lt + 1;
}

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	if(lt == rt) {
		a[step].sum1 = a[step].sum2 = s[lt] - 'a' + 1;
		return;
	}
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	a[step].sum1 = (1LL * a[2 * step].sum1 * c1[len(step * 2 + 1)] % mod1 + a[2 * step + 1].sum1) % mod1;
	a[step].sum2 = (1LL * a[2 * step].sum2 * c2[len(2 * step + 1)] % mod2 + a[2 * step + 1].sum2) % mod2;
}

void query(int lt,int rt,int step,int &sum1,int &sum2)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		sum1 = a[step].sum1;
		sum2 = a[step].sum2;
		return;
	}
	if(rt <= a[2 * step].rt) query(lt,rt,2 * step,sum1,sum2);
	else if(lt > a[2 * step].rt) query(lt,rt,2 * step + 1,sum1,sum2);
	else {
		int sum11,sum12,sum21,sum22;
		query(lt,a[2 * step].rt,2 * step,sum11,sum12);
		query(a[2 * step + 1].lt,rt,2 * step + 1,sum21,sum22);
		sum1 = (1LL * sum11 * c1[rt - a[2 * step].rt] % mod1 + sum21) % mod1;
		sum2 = (1LL * sum12 * c2[rt - a[2 * step].rt] % mod2 + sum22) % mod2;
	}
}

void modify(int pos,int step,int key)
{
	if(a[step].lt == a[step].rt) {
		a[step].sum1 = a[step].sum2 = key;
		return;
	}
	if(pos <= a[2 * step].rt) modify(pos,2 * step,key);
	else modify(pos,2 * step + 1,key);
	a[step].sum1 = (1LL * a[2 * step].sum1 * c1[len(step * 2 + 1)] % mod1 + a[2 * step + 1].sum1) % mod1;
	a[step].sum2 = (1LL * a[2 * step].sum2 * c2[len(2 * step + 1)] % mod2 + a[2 * step + 1].sum2) % mod2;
}

int main()
{
	int t,n,m,x,y;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		st.clear();
		scanf("%d",&n);
		init(n);
		scanf("%s",s);
		init(0,strlen(s),1);
		scanf("%d",&m);
		printf("Case #%d:\n",cas);
		while(m --) {
			scanf("%s",s);
			if(s[0] == 'Q') {
				scanf("%d%d",&x,&y);
				int sum1,sum2;
				query(x,y,1,sum1,sum2);
				if(st.count(point(sum1,sum2))) printf("Yes\n");
				else printf("No\n");
			}
			else {
				scanf("%d%s",&x,s);
				y = change(s[0]);
				modify(x,1,y);
			}
		}
	}
	return 0;
}

