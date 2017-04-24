#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010;
int pre[N];

struct point
{
	int v,id,st,ed;
	point() {}
	point(int v,int id,int st,int ed):v(v),id(id),st(st),ed(ed) {}
	friend bool operator < (const point &p,const point &q) {
		return p.st > q.st;
	}
};

vector<point> v[N];
int sid,tid,_stime,etime;
int pos[N];

struct que
{
	int v,time,eid;
	que() {}
	que(int v,int time,int eid):v(v),time(time),eid(eid) {}
};

queue<que> q;
int stk[N],cnt;

void get_ans(int tid)
{
	cnt = 0;
	while(tid > 0) {
		stk[++ cnt] = tid;
		tid = pre[tid];
	}
	printf("%d\n",cnt);
	for(int i = cnt; i >= 1; i --) {
		printf("%d",stk[i]);
		if(i == 1) printf("\n");
		else printf(" ");
	}
}

void bfs(int n,int m)
{
	q.push(que(sid,_stime,0));
	while(!q.empty()) {
		que u = q.front();
		q.pop();
		if(u.v == tid && u.time <= etime) {
			if(u.eid == 0) {
				printf("0\n");
				return;
			}
			get_ans(u.eid);

			return;
		}
		for(int i = pos[u.v]; i < v[u.v].size(); i ++) {
			if(v[u.v][i].st < u.time) break;
			pos[u.v] ++;
			pre[v[u.v][i].id] = u.eid;
			q.push(que(v[u.v][i].v,v[u.v][i].ed,v[u.v][i].id));
		}
	}
	printf("Impossible\n");
}

int main()
{
	int n,m,x,y,st,ed;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d%d",&x,&y,&st,&ed);
		v[x].push_back(point(y,i,st,ed));
	}
	memset(pos,0,sizeof(pos));
	for(int i = 1; i <= n; i ++) 
		sort(v[i].begin(),v[i].end());
	memset(pre,-1,sizeof(pre));
	scanf("%d%d%d%d",&sid,&tid,&_stime,&etime);
	bfs(n,m);
	return 0;
}

