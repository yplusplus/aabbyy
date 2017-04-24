#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 2010;
const int E = 50010;
const int oo = 0x3f3f3f3f;
struct edge
{
	int v,next,dis;
}e[E * 2];

int cnt,head[N];

void addedge(int u,int v,int dis)
{
	e[cnt].dis = dis;
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int visit[N];

void dfs(int u,int mid)
{
	visit[u] = 1;
	for(int i = head[u]; i != -1; i = e[i].next)
		if(!visit[e[i].v] && e[i].dis <= mid) dfs(e[i].v,mid);
}

int dis[N];
void spfa(int n,int mid,int st,int ed)
{
	queue<int> q;
	memset(visit,0,sizeof(visit));
	for(int i = 1; i <= n; i ++) dis[i] = oo;
	dis[st] = 0;
	q.push(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		visit[u] = 0;
		for(int i = head[u]; i != -1; i = e[i].next)
			if(e[i].dis <= mid && dis[e[i].v] > dis[u] + e[i].dis) {
				dis[e[i].v] = dis[u] + e[i].dis;
				if(!visit[e[i].v]) {
					visit[e[i].v] = 1;
					q.push(e[i].v);
				}
			}
	}
	printf("%d\n",dis[ed]);
}

int main()
{
	int n,m,st,ed,x,y,z;
	while(scanf("%d%d%d%d",&n,&m,&st,&ed) != EOF) {
		cnt = 0;
		memset(head,-1,sizeof(head));
		int lt = 100000,rt = -100000,mid;
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			addedge(x,y,z);
			addedge(y,x,z);
			lt = min(lt,z);
			rt = max(rt,z);
		}
		int ans = 0;
		while(lt <= rt) {
			mid = (lt + rt) / 2;
			memset(visit,0,sizeof(visit));
			dfs(st,mid);
			if(visit[ed]) ans = mid,rt = mid - 1;
			else lt = mid + 1;
		}
		//cout << ans << endl;
		spfa(n,ans,st,ed);
	}
	return 0;
}

