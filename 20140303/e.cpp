#include <bits/stdc++.h>
using namespace std;

struct point
{
	int len,one;
	long long x,y;
	friend bool operator < (const point &p,const point &q) {
		if(p.len != q.len) return p.len < q.len;
		if(p.one != q.one) return p.one < q.one;
		if(p.x != q.x) return p.x < q.x;
		return p.y < q.y;
	}
	point() {}
	point(int len,int one,long long x,long long y):len(len),one(one),x(x),y(y) {}
};
set<point> st[45];
char s[45];
const long long mod1 = 1000000007;
const long long mod2 = 1600033;
const long long key1 = 131;
const long long key2 = 27;
long long a[1 << 15],b[1 << 15];
long long aa[1 << 15],bb[1 << 15];

void init()
{
	a[0] = b[0] = 1;
	for(int i = 1; i < (1 << 15); i ++) {
		a[i] = a[i - 1] * key1 % mod1;
		b[i] = b[i - 1] * key2 % mod2;
	}
	aa[1] = bb[1] = 1;
	for(int i = 2; i < (1 << 15); i ++) {
		aa[i] = (aa[i - 1] * key1 + 1) % mod1;
		bb[i] = (bb[i - 1] * key2 + 1) % mod2;
	}
}

int r,n,m;
int tot;

void dfs(int pos,int len,int one,long long val1,long long val2)
{
	if(one > m) return;
	if(len > n) return;
	if(tot > 1) return;
	if(st[pos].count(point(len,one,val1,val2))) return;
	st[pos].insert(point(len,one,val1,val2));
	if(pos >= r) {
		if(len == n && one == m) tot ++;
		return;
	}
	if(s[pos] == '0') {
		dfs(pos + 1,len + 1,one,val1 * key1 % mod1,val2 * key2 % mod2);
	}
	else {
		if(pos + 1 == r || s[pos + 1] == '0') dfs(pos + 1,len + 1,one + 1,(val1 * key1 + 1) % mod1,(val2 + key2 + 1) % mod2);
		if(pos + 2 <= r && s[pos + 1] == '1' && (pos + 2 == r || s[pos + 2] == '0')) 
			dfs(pos + 2,len + 2,one + 2,(val1 * key1 % mod1 * key1 + key1 + 1) % mod1,(val2 * key2 % mod2 * key2 + key2 + 1) % mod2);
		int bits = 1;
		for(int i = pos + 1; i <= r && bits + len <= n && bits + one <=m; i ++) {
			if(bits > i - pos && (i == r || s[i] == '0')) dfs(i,len + bits,one + bits,(val1 * a[bits] + aa[bits]) % mod1,(val2 * b[bits] + bb[bits] )% mod2);
			bits = 2 * bits + (s[i] - '0');
		}
	}
}

int main()
{
	init();
	int cas = 0;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		for(int i = 0; i < 45; i ++) st[i].clear();
		scanf("%s",s);
		r = strlen(s);
		tot = 0;
		dfs(0,0,0,0,0);
		printf("Case #%d: ",++ cas);
		if(tot == 0) printf("NO\n");
		else if(tot == 1) printf("YES\n");
		else printf("NOT UNIQUE\n");
	}
}
