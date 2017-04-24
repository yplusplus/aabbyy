#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

bool visit[1010][1 << 12];
int n,m,r,tot;
char s[110][110];
int HPI,HPMAX;
int cost[128];
char cd[1010][3];
int len[1010];
char map[1010];
int P,val[1010];
int mapx[1010],mapy[1010];
int rev_map[1 << 12];
int lowbit(int x)
{
	return x & (-x);
}

int dir[4][2] = {1,0,-1,0,0,1,0,-1};

int get_dir(char c)
{
	if(c == 'U') return 1;
	if(c == 'D') return 0;
	if(c == 'R') return 2;
	return 3;
}

short int dp[1010][1 << 12];
struct point
{
	short int x,state;
	point() {}
	point(short int x,short int state):x(x),state(state) {}
};

queue<point> q;
bool bfs()
{
	for(int i = 0; i < 12; i ++)
		rev_map[1 << i] = i;
	scanf("%d",&P);
	for(int i = 0; i <P; i ++)
		scanf("%d",&val[i]);
	for(int i = 0; i <= tot; i ++)
		for(int j = 0; j < (1 << P); j ++) {
			visit[i][j] = false;
			dp[i][j] = 0;
		}
	while(!q.empty()) q.pop();
	dp[0][(1 << P) - 1] = HPI;
	int ct = 0;
	q.push(point(0,(1 << P) - 1));
	for(int i = 1; i <= r; i ++) {
		for(int j = 1; j <= len[i]; j ++)
			map[++ ct] = cd[i][0];
	}
	mapx[0] = 1;
	mapy[0] = 1;
	while(!q.empty()) {
		point u = q.front();
		q.pop();
		visit[u.x][u.state] = false;
		if(u.x == tot) return true;
		int dirt = get_dir(map[u.x + 1]);
		int x = mapx[u.x] + dir[dirt][0];
		int y = mapy[u.x] + dir[dirt][1];
		mapx[u.x + 1] = x;
		mapy[u.x + 1] = y;
		for(int i = 0; i < P && dp[u.x][u.state] - cost[s[x][y]] <= 0; i ++) {
			if(u.state & (1 << i)) {
				if(min(dp[u.x][u.state] + val[i],(int)HPMAX) > dp[u.x][u.state ^ (1 << i)]) {
					dp[u.x][u.state ^ (1 << i)] = min(dp[u.x][u.state] + val[i],(int)HPMAX);
					if(!visit[u.x][u.state ^ (1 << i)]) {
						q.push(point(u.x,u.state ^ (1 << i)));
						visit[u.x][u.state ^ (1 << i)] = true;
					}
				}
			}
		}
		/*
		int dirt = get_dir(map[u + 1]);
		int x = mapx[u] + dir[dirt][0];
		int y = mapy[u] + dir[dirt][1];
		mapx[u + 1] = x;
		mapy[u + 1] = y;*/
		if(dp[u.x + 1][u.state] < dp[u.x][u.state] - cost[s[x][y]]) {
			dp[u.x + 1][u.state] = dp[u.x][u.state] - cost[s[x][y]];
			if(!visit[u.x + 1][u.state]) {
				visit[u.x + 1][u.state] = true;
				q.push(point(u.x + 1,u.state));
			}
		}
	}
	return false;
}

int main()
{
	while(scanf("%d%d",&HPI,&HPMAX) != EOF) {
		if(!HPI && !HPMAX) break;
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i ++) scanf("%s",s[i] + 1);
		char str[15];
		int x;
		scanf("%d",&r);
		while(r --) {
			scanf("%s%d",str,&x);
			cost[str[0]] = x;
		}
		scanf("%d",&r);
		tot = 0;
		for(int i = 1; i <= r; i ++) {
			scanf("%s%d",cd[i],&len[i]);
			tot += len[i];
		}
		if(bfs()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

