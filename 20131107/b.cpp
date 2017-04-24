#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

const int N = 210;
struct edge
{
	int v,next;
}e[N * N];

int low[N],dfn[N],bel[N],cc,ct;
int head[N],cnt,instack[N];
stack<int> sta;
int belong[N];
void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

void init()
{
	while(!sta.empty()) sta.pop();
	memset(head,-1,sizeof(head));
	cnt = cc = ct = 0;
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(bel,0,sizeof(bel));
	memset(instack,0,sizeof(instack));
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ ct;
	sta.push(u);
	instack[u] = 1;
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(!dfn[e[i].v]) {
			tarjan(e[i].v);
			if(low[e[i].v] < low[u]) low[u] = low[e[i].v];
		}
		else if(instack[e[i].v] && dfn[e[i].v] < low[u]) low[u] = dfn[e[i].v];
	}
	if(dfn[u] == low[u]) {
		int v;
		cc ++;
		do {
			v = sta.top();
			sta.pop();
			instack[v] = 0;
			bel[cc] ++;
			belong[v] = cc;
		}while(u != v);
	}
}

bool flag[N][N];
int visit[N],n;
void dfs(int u)
{
	visit[u] = 1;
	for(int i = 1; i <= n; i ++)
		if(!visit[i] && flag[u][i]) dfs(i);
}

int main()
{
	int x;	
	while(scanf("%d",&n) != EOF) {
		init();
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				scanf("%d",&x);
				if(x) addedge(i,j);
			//	if(x) flag[i][j] = flag[j][i] = true;
			}
		}
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= n; i ++)
			if(!dfn[i]) tarjan(i);
		int ans = 0;
		for(int i = 1; i <= cc; i ++)
			if(bel[i] > 1) ans += bel[i];
		/*
		for(int i = 1; i <= n; i ++) 
			cout << belong[i] << " ";
		cout << endl;
		*/
		
		//int ind[N];
		//memset(ind,0,sizeof(ind));
		memset(flag,false,sizeof(flag));
		for(int i = 1; i <= n; i ++)
			for(int j = head[i]; j != -1; j = e[j].next)
				if(belong[i] != belong[e[j].v]) flag[belong[i]][belong[e[j].v]] = true;
		for(int k = 1; k <= cc; k ++)
			for(int i = 1; i <= cc; i  ++)
				for(int j = 1; j <= cc; j ++) {
					if(flag[i][j] && flag[i][k] && flag[k][j]) {
						flag[i][j] = false;
						//cout << i << " " << j << endl;
					}
				}
		for(int i = 1; i <= cc; i ++)
			for(int j = 1; j <= cc; j ++)
				if(flag[i][j]) ans ++;
		printf("%d\n",ans);
	}
	return 0;
}
