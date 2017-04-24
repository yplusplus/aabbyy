#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int c[N][2];
int pre[N];
char s[N];
int visit[N];
const long long mod = 21092013;
long long ans;
int tlen;
int a[N][2];
int nxt[N][3];
int P[3];
queue<int> q;

void init()
{
	memset(nxt,-1,sizeof(nxt));
	memset(P,-1,sizeof(P));
	for(int i = tlen - 1; i >= 0; i --) {
		nxt[i][0] = P[0];
		nxt[i][1] = P[1];
		nxt[i][2] = P[2];
		if(s[i] == 'U') nxt[i][2] = P[2] = i;
		else if(s[i] == 'L') nxt[i][0] = P[0] = i;
		else nxt[i][1] = P[1] = i;
	}
	memset(a,0,sizeof(a));
	tlen = strlen(s);
	for(int i = tlen - 1; i >= 0; i --) {
		if(s[i] == 'U') {
			a[i][0] = a[i + 1][0];
			a[i][1] = a[i + 1][1];
			continue;
		}
		else if(s[i] == 'R') {
			a[i][0] = a[i + 1][0];
			a[i][1] = (a[i + 1][1] + a[i + 1][0] + 1) % mod;
		}
		else {
			a[i][0] = (a[i + 1][0] + a[i + 1][1] + 1) % mod;
			a[i][1] = a[i + 1][1];
		}
	}
}

void cal(int pos)
{
	ans += a[pos][0] + a[pos][1];
	if(ans >= mod) ans %= mod;
}

void bfs(int pos,int step)
{
	init();
	visit[pos] = 0;
	ans ++;
	while(!q.empty()) q.pop();
	q.push(pos);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		int x = visit[u];
		if(nxt[x][0] != -1) {
			if(c[u][0] != -1) {
				if(visit[c[u][0]] == -1) {
					visit[c[u][0]] = nxt[x][0] + 1;
					q.push(c[u][0]);
					ans ++;
				}
			}
			else {
				ans ++;
				cal(nxt[x][0] + 1);
			}
		}
		if(nxt[x][1] != -1) {
			if(c[u][1] != -1) {
				if(visit[c[u][1]] == -1) {
					visit[c[u][1]] = nxt[x][1] + 1;
					q.push(c[u][1]);
					ans ++;
				}
			}
			else {
				ans ++;
				cal(nxt[x][1] + 1);
			}
		}
		if(u != 1 && nxt[x][2] != -1) {
			if(visit[pre[u]] == -1) {
				visit[pre[u]] = nxt[x][2] + 1;
				q.push(pre[u]);
				ans ++;
			}
		}
		ans %= mod;
	}
}

void solve()
{
	memset(visit,-1,sizeof(visit));
	memset(pre,-1,sizeof(pre));
	memset(c,-1,sizeof(c));
	scanf("%s",s);
	int pos = 1;
	int tot = 1;
	for(int i = 0; s[i]; i ++) {
		if(s[i] == 'U') {
			if(pos == 1) continue;
			pos = pre[pos];
		}
		else if(s[i] == 'R') {
			if(c[pos][1] == -1) {
				c[pos][1] = ++ tot;
				pre[tot] = pos;
			}
			pos = c[pos][1];
		}
		else if(s[i] == 'L') {
			if(c[pos][0] == -1) {
				c[pos][0] = ++ tot;
				pre[tot] = pos;
			}
			pos = c[pos][0];
		}
	}
	ans = 0;
	scanf("%s",s);
	tlen = strlen(s);
	bfs(pos,0);
	cout << ans << endl;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case %d: ",cas);
		solve();
	}
	return 0;
}
