#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010;
struct edge
{
	int v,p,next;
}e[N * 2];

int head[N],cnt;

void addedge(int u,int v,int p)
{
	e[cnt].v = v;
	e[cnt].p = p;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

queue<int> q;
int dis[N],pre[N],visit[N];
double p[N];

void spfa(int st,int ed,int n)
{
	for(int i = 1; i <= n; i ++) p[i] = 0,pre[i] = 0,dis[i] = 1000000000,visit[i] = 0;
	while(!q.empty()) q.pop();
	q.push(st);
	dis[st] = 1;
	p[st] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		visit[u] = 0;
		for(int i = head[u]; i != -1; i = e[i].next)
			if(dis[e[i].v] > dis[u] + 1) {
				dis[e[i].v] = dis[u] + 1;
				pre[e[i].v] = u;
				p[e[i].v] = p[u] * (1 - e[i].p / 100.0);
				if(!visit[e[i].v]) {
					visit[e[i].v] = 1;
					q.push(e[i].v);
				}
			}
			else if(dis[e[i].v] == dis[u] + 1 && p[e[i].v] < p[u] * (1 - e[i].p / 100.0)) {
				dis[e[i].v] = dis[u] + 1;
				pre[e[i].v] = u;
				p[e[i].v] = p[u] * (1 - e[i].p / 100.0);
				if(!visit[e[i].v]) {
					visit[e[i].v] = 1;
					q.push(e[i].v);
				}
			}
	}
}

int ans[100010];

void output(int n,bool flag)
{
	/*
	if(pre[n]) output(pre[n],false);
	printf("%d",n);
	if(flag) printf("\n");
	else printf(" ");*/
	int ct = 0;
	ans[++ ct] = n;
	while(pre[n]) {
		ans[++ ct] = pre[n];
		n = pre[n];
	}
	for(int i = ct; i >= 1; i --) {
		printf("%d",ans[i]);
		if(i == 1) printf("\n");
		else printf(" ");
	}
}

int main()
{
	int n,m,st,ed,x,y,z;
	scanf("%d%d%d%d",&n,&m,&st,&ed);
	memset(head,-1,sizeof(head));
	cnt = 0;
	while(m --) {
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z);
		addedge(y,x,z);
	}
	spfa(st,ed,n);
	printf("%d %.20lf\n",dis[ed],1 - p[ed]);
	output(ed,1);
	return 0;
}


