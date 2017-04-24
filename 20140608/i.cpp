#include <bits/stdc++.h>
using namespace std;

int cx[10],cy[10];
int n,m,ans;
int needs[10];
int dir[4][2] = {0,1,0,-1,1,0,-1,0};
unsigned long long one = 1;
unsigned long long mask;
int maps[10][10];
int dis[10][10];
bool check(int x,int y)
{
    return x >= 0 && x < n && y >= 0 && y < m && !(mask & (one << maps[x][y]));
}

void dfs(int x,int y,int step,int pt)
{
    if(step == n * m) {
        ans ++;
        return;
    }
    if(!check(x - 1,y) && !check(x + 1,y) && check(x,y + 1) && check(x,y - 1)) return;
    if(!check(x,y + 1) && !check(x,y - 1) && check(x - 1,y) && check(x + 1,y)) return;
    for(int i = pt; i <= 4; i ++)
        if(abs(cx[i] - x) + abs(cy[i] - y) > needs[i] - step) return;
    for(int i = 0; i < 4; i ++) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if(!check(tx,ty)) continue;
        bool flag = true;
        for(int j = pt; j <= 4; j ++) {
            if(cx[j] == tx && cy[j] == ty && step + 1 != needs[j]) {
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        mask |= (one << maps[tx][ty]);
        if(step + 1 == needs[pt]) {
            if(tx == cx[pt] && ty == cy[pt]) dfs(tx,ty,step + 1,pt + 1);
        }
        else dfs(tx,ty,step + 1,pt);
        mask ^= (one << maps[tx][ty]);
    }
}
int main()
{
	int cas = 0;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		cx[0] = cy[0] = 0;
		cx[4] = 0,cy[4] = 1;
		for(int i = 1; i <= 3; i ++)
			scanf("%d%d",&cx[i],&cy[i]);
		printf("Case %d: ",++ cas);
		if((n * m) & 1) {
			printf("0\n");
			continue;
		}
		int tot = 4;
		for(int i = 0; i <= 4; i ++) {
			needs[i] = (n * m) * i / 4;
		}
		bool flag = true;
		for(int i = 0; i <= 4; i ++)
			for(int j = i + 1; j <= 4; j ++) {
			    if(i == 0 && j == 1) continue;
				if(cx[i] == cx[j] && cy[i] == cy[j]) {
					flag = false;
				}
			}
		if(!flag) {
			printf("0\n");
			continue;
		}
		for(int i = 0; i <= 4; i ++) {
			for(int j = i + 1; j <= 4; j ++) {
				if(abs(cx[i] - cx[j]) + abs(cy[i] - cy[j]) > needs[j] - needs[i])
					flag = false;
			}
		}
		if(!flag) {
			printf("0\n");
			continue;
		}
		mask = 1;
		int step = 1;
		if(cx[0] == cx[1] && cy[0] == cy[1]) step ++;
		int cc = 0;
		for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                maps[i][j] = cc ++;
        ans = 0;
		dfs(0,0,1,step);
		printf("%d\n",ans);
	}
	return 0;
}
