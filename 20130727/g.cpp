#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct edge
{
	int v,next;
}e[1000010];

int cnt,head[2555];

void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int visit[55 * 55 + 5];
int pre[55 * 55 + 5];
int n,m;
int dir[4][2] = {0,1,0,-1,1,0,-1,0};
char s[55][55];
bool sure(int x,int y)
{
	return x >= 1  && x <= n && y >= 1 && y <= m && s[x][y] != 'X';
}

int change(int x,int y)
{
	return (x - 1) * m + y;
}

int find(int u)
{
	for(int i = head[u]; i != -1; i = e[i].next)
		if(!visit[e[i].v]) {
			visit[e[i].v] = 1;
			int tmp = pre[e[i].v];
			pre[e[i].v] = u;
			if(tmp == -1 || find(tmp)) return 1;
			pre[e[i].v] = tmp;
		}
	return 0;
}

int main()
{
	while(scanf("%d%d",&n,&m) != EOF) {
		cnt = 0;
		memset(head,-1,sizeof(head));
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i] + 1);
		bool flag = false;
		int sum = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++) {
				if(s[i][j] == 'X') continue;
				flag = true;
				sum ++;
				if(i % 2 != j % 2) continue;
				for(int k = 0; k < 4; k ++) {
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if(!sure(x,y)) continue;
					addedge(change(i,j),change(x,y));
				}
			}
		if(!flag) {
			printf("2\n");
			continue;
		}
		memset(pre,-1,sizeof(pre));
		int tot = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(i % 2 == j % 2) {
					memset(visit,0,sizeof(visit));
					tot += find(change(i,j));
				}
		if(tot * 2 == sum) printf("2\n");
		else printf("1\n");
	}
	return 0;
}



