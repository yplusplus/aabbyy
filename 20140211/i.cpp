#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int dir[8][2] = {0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};
char s[N][N];
int tot;
int n,m;
bool check(int x,int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
bool visit[N][N];
bool killed[N][N];

void init() {
	memset(visit, false, sizeof(visit));
	memset(killed, true, sizeof(killed));
	queue<int> que;
	for (int i = 1; i <= n; i++) {
		if (!visit[i][1]) {
			visit[i][1] = true;
			que.push(i);
			que.push(1);
		}
		if (!visit[i][m]) {
			visit[i][m] = true;
			que.push(i);
			que.push(m);
		}
	}
	for (int j = 1; j <= m; j++) {
		if (!visit[1][j]) {
			visit[1][j] = true;
			que.push(1);
			que.push(j);
		}
		if (!visit[n][j]) {
			visit[n][j] = true;
			que.push(n);
			que.push(j);
		}
	}
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		//if (x == 5 && y == 6) cout << 123 << endl;
		killed[x][y] = false;
		if (s[x][y] == 'P') continue;
		for (int i = 0; i < 4; i++) {
			int nx = dir[i][0] + x, ny = dir[i][1] + y;
			if (!check(nx, ny)) continue;
			if (!visit[nx][ny]) {
				visit[nx][ny] = true;
				que.push(nx);
				que.push(ny);
			}
		}
	}
}

void bfs(int x,int y)
{
	queue<int> q;
	//while(!q.empty()) q.pop();
	q.push(x);
	q.push(y);	
	visit[x][y] = true;
	while(!q.empty()) {
		x = q.front();
		q.pop();
		y = q.front();
		q.pop();
		tot ++;
		for(int i = 0; i < 8; i ++) {
			int tx = x + dir[i][0];
			int ty = y + dir[i][1];
			if(!check(tx,ty)) continue;
			if(!visit[tx][ty] && s[tx][ty] == 'P') {
				visit[tx][ty] = true;
				q.push(tx);
				q.push(ty);
			}
		}
	}
}

int main()
{
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i] + 1);
		int ans = 0;
		init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (killed[i][j]) s[i][j] = '.';
			}
		}
		//for (int i = 1; i <= n; i++) {
			//for (int j = 1; j <= m; j++) {
				//putchar(s[i][j]);
			//}
			//cout << endl;
		//}
		memset(visit, false, sizeof(visit));
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(s[i][j] == 'P' && !visit[i][j]) {
					tot = 0;
					bfs(i,j);
					ans = max(ans,tot);
				}
		printf("%d\n",ans);
	}
	return 0;
}
