#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int visit[25][25][25];
int dir[6][3] = {1,0,0,-1,0,0,0,1,0,0,-1,0,0,0,1,0,0,-1};

int change(char *s)
{
	int ans = 0;
	if(s[1] == 'x') ans = 0;
	else if(s[1] == 'y') ans = 1;
	else ans = 2;
	ans *= 2;
	if(s[0] == '-') ans ++;
	return ans;
}

int ans;
int n,m,r;

bool check(int x,int y,int z)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && z >= 1 && z <= r && !visit[x][y][z];
}

bool check(int tx[],int ty[],int tz[])
{
	for(int i = 0; i < 4; i ++)
		if(!check(tx[i],ty[i],tz[i])) return false;
	return true;
}

void set(int tx[],int ty[],int tz[])
{
	for(int i = 0; i < 4; i ++)
		visit[tx[i]][ty[i]][tz[i]] = 1;
}

void del(int tx[],int ty[],int tz[])
{
	for(int i = 0; i < 4; i ++)
		visit[tx[i]][ty[i]][tz[i]] = 0;
}

int stx,sty,stz,edx,edy,edz;
char s0[15],s1[15];
void dfs(int x,int y,int z,int step,int dd)
{
	if(step  + 1 >= ans) return;
	int tx[5],ty[5],tz[5];
	for(int i = dd; i <= dd; i ++) {
		for(int j = 0; j < 6; j ++) {
			if(i / 2 == j / 2) continue;
			tx[0] = 0,ty[0] = 0,tz[0] = 0;
			tx[1] = dir[i][0],ty[1] = dir[i][1],tz[1] = dir[i][2];
			for(int k = 2; k <= 4; k ++) {
				tx[k] = tx[k - 1] + dir[j][0];
				ty[k] = ty[k - 1] + dir[j][1];
				tz[k] = tz[k - 1] + dir[j][2];
			}
			for(int k = 0; k <= 4; k ++) {
				tx[k] += x,ty[k] += y,tz[k] += z;
			}
			if(!check(tx,ty,tz)) continue;
			if(tx[3] == edx && ty[3] == edy && tz[3] == edz && check(edx,edy,edz) && j == change(s1)) {
				ans = step + 1;
				return;
			}
			set(tx,ty,tz);
			dfs(tx[4],ty[4],tz[4],step + 1,j);
			del(tx,ty,tz);
		}
		for(int j = 0; j < 6; j ++) {
			if(i / 2 == j / 2) continue;
			tx[0] = 0,ty[0] = 0,tz[0] = 0;
			tx[1] = dir[i][0],ty[1] = dir[i][1],tz[1] = dir[i][2];
			tx[2] = dir[i][0] * 2,ty[2] = dir[i][1] * 2,tz[2] = dir[i][2] * 2;
			for(int k = 3; k <= 4; k ++) {
				tx[k] = tx[k - 1] + dir[j][0];
				ty[k] = ty[k - 1] + dir[j][1];
				tz[k] = tz[k - 1] + dir[j][2];
			}
			for(int k = 0; k <= 4; k ++)
				tx[k] += x,ty[k] += y,tz[k] += z;
			if(!check(tx,ty,tz)) continue;
			if(tx[3] == edx && ty[3] == edy && tz[3] == edz && check(edx,edy,edz) && j == change(s1)) {
				ans = step + 1;
				return;
			}
			set(tx,ty,tz);
			dfs(tx[4],ty[4],tz[4],step + 1,j);
			del(tx,ty,tz);
		}
	}
}

int main()
{
	int cas = 0;
	while(scanf("%d",&n), n != 0) {
		scanf("%d%d",&m,&r);
		scanf("%d%d%d%s",&stx,&sty,&stz,s0);
		scanf("%d%d%d%s",&edx,&edy,&edz,s1);
		ans = 7;
		memset(visit,0,sizeof(visit));
		dfs(stx,sty,stz,0,change(s0));
		printf("Case %d: ",++ cas);
		if(ans > 6) printf("Impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
