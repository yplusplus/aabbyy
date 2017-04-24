#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct point
{
	int times;
	int n,id;
	int a[15];
	void read() {
		scanf("%d%d",&n,&times);
		for(int i = 0; i < n; i ++)
			scanf("%d",&a[i]);
	}
	friend bool operator < (const point &p,const point &q) {
		return p.times < q.times;
	}
}a[35];

int pre[35],dp[35];
int re[35],ct,ans,n,w,res[35];
int visit[210];

void get(int u)
{
	if(pre[u] != -1) get(pre[u]);
	re[ct ++] = a[u].id;
}

bool check(int u)
{
	int cnt = 0;
	for(int i = 0; i < a[u].n; i ++)
		if(!visit[a[u].a[i]]) cnt ++;
	return cnt >= 3;
}

void dfs(int u,int step)
{
	if(step > ans) {
		ans = step;
		for(int i = 0; i < step; i ++)
			re[i] = res[i];
	}
	if(step + n - u + 1 <= ans) return;
	if(u > n) return;
	if(step && a[res[step - 1]].times + w < a[u].times) return; 
	if(check(u)) {
		for(int i = 0; i < a[u].n; i ++)
			visit[a[u].a[i]] ++;
		res[step] = u;
		dfs(u + 1,step + 1);
		for(int i = 0; i < a[u].n; i ++)
			visit[a[u].a[i]] --;
	}
	dfs(u + 1,step);
}

int main()
{
	int t,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d%d",&n,&m,&w);
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= n; i ++) {
			a[i].read();
			a[i].id = i;
		}
		sort(a + 1,a + n + 1);
		ans = 0;
		dfs(1,0);
		printf("%d\n",ans);
		for(int i = 0; i < ans; i ++)
			re[i] = a[re[i]].id;
		sort(re,re + ans);
		for(int i = 0; i < ans; i ++) {
			printf("%d",re[i]);
			if(i == ans - 1) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}


