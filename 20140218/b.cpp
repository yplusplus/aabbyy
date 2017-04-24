#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
string ans,path[25][25];
int dp[25][25];
struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
};
queue<point> q;
char s[25][25];

bool match(int x,int y,int r)
{
	int len = strlen(s[x]);
	len --;
	for(int i = r - 1; i >= 0 && len >= 0; i --,len --) {
		if(s[y][i] != s[x][len]) return false;
	}
	return true;
}

int visit[25][25];
void update(int x,int y,int xx,int yy,int cost,string tmp)
{
	if(dp[x][y] > dp[xx][yy] + cost) {
		dp[x][y] = dp[xx][yy] + cost;
		path[x][y] = tmp + path[xx][yy];
		if(!visit[x][y]) visit[x][y] = 1,q.push(point(x,y));
	}
	else if(dp[x][y] == dp[xx][yy] + cost) {
		if(path[x][y] > tmp + path[xx][yy]) {
			path[x][y] = tmp + path[xx][yy];
			if(!visit[x][y]) visit[x][y] = 1,q.push(point(x,y));
		}
	}
}

void bfs(int n)
{
	for(int i = 1; i <= n; i ++)
		scanf("%s",s[i]);
	for(int i = 0 ; i < 25; i ++) 
		for(int j = 0; j < 25; j ++) {
			path[i][j] =  "";
			dp[i][j] = oo;
		}
	while(!q.empty()) q.pop();
	ans = "";
	memset(visit,0,sizeof(visit));
	for(int i = 1; i <= n; i ++) {
		q.push(point(i,strlen(s[i])));
		dp[i][strlen(s[i])] = strlen(s[i]);
		path[i][strlen(s[i])] = s[i];
		visit[i][strlen(s[i])] = 1;
	}
	while(!q.empty()) {
		point u = q.front();
		q.pop();
		visit[u.x][u.y] = 0;
		for(int i = 1; i <= n; i ++) {
			if(i == u.x && strlen(s[i]) == u.y) continue;
			if(match(i,u.x,u.y)) {
				if(strlen(s[i]) == u.y) {
					if(ans == "" || ans.length() > path[u.x][u.y].length() || (ans.length() == path[u.x][u.y].length() && ans > path[u.x][u.y])) {
						ans = path[u.x][u.y];
						continue;
					}
				}
				else if(strlen(s[i]) > u.y) {
					string tmp;
					int x = strlen(s[i]) - u.y;
					for(int j = 0; j < x; j ++) tmp += s[i][j];
					update(i,strlen(s[i]) - u.y,u.x,u.y,strlen(s[i]) - u.y,tmp);
				}
				else update(u.x,u.y - strlen(s[i]),u.x,u.y,0,"");
			}
		}
	}
}

int main()
{
	int cas = 0;
	int n;
	while(scanf("%d",&n), n != 0) {
		bfs(n);
		printf("Code %d: %d bits\n",++ cas,(int)ans.length());
		for(int i = 0; i < ans.length(); i += 20) {
			for(int j = 0; i + j < ans.length() && j < 20; j ++)
				cout << ans[i + j];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
