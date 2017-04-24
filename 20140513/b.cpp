#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int SIZE = 50;
const int mod = 1000000;
struct bignum
{
	long long a[55];
	bignum() {
		memset(a,0,sizeof(a));
	}
	
	bignum operator + (const bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++)
			c.a[i] = a[i] + p.a[i];
		for(int i = 0; i < SIZE; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		return c;
	}

	bignum operator * (const bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++)
			for(int j = 0; i + j < SIZE; j ++)
				c.a[i + j] += a[i] * p.a[j];
		for(int i = 0; i < SIZE; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] += c.a[i] / mod;
				c.a[i] %= mod;
			}
		return c;
	}

	void output() {
		int i = SIZE - 1;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		if(i == -1) i ++;
		cout << a[i];
		for(i = i - 1; i >= 0; i --)
			printf("%06d",(int)a[i]);
		printf("\n");
	}
}c[N][N];

vector<int> v[N];
int lc[N],rc[N];
bignum ans;
int sz[N],ind[N];

void dfs(int u)
{
	if(lc[u]) {
		dfs(lc[u]);
		sz[u] += sz[lc[u]];
	}
	if(rc[u]) {
		dfs(rc[u]);
		sz[u] += sz[rc[u]];
	}
	sz[u] ++;
	if(lc[u]) ans = ans * c[sz[u] - 1][sz[lc[u]]];
	else if(rc[u]) ans = ans * c[sz[u] - 1][sz[rc[u]]];
}

int main()
{
	freopen("cartesian.in","r",stdin);
	freopen("cartesian.out","w",stdout);
	for(int i = 0; i < N; i ++) {
		c[i][0].a[0] = c[i][i].a[0] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d%d",&x,&y);
		lc[i] = x,rc[i] = y;
		ind[x] ++,ind[y] ++;
	}
	ans.a[0] = 1;
	for(int i = 1; i <= n; i ++)
		if(!ind[i]) dfs(i);
	ans.output();
	return 0;
}
