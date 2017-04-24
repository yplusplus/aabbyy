#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
int dp[35][110][1010];
int f[110][110][1010];

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
}a[110];

int c[110][110];

void init()
{
	memset(c,0,sizeof(c));
	for(int i = 0; i < 110; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}

void add(int &x,int y)
{
	x += y;
	x = (x % mod + mod) % mod;
}

void solve()
{
	int visit[1010];
	int n,m,x;
	scanf("%d%d",&n,&m);
	memset(visit,0,sizeof(visit));
	for(int i = 1; i <= n; i ++) {
		scanf("%d",&x);
		visit[x] ++;
	}
	int ct = 0;
	for(int i = 1; i <= m; i ++)
		if(visit[i]) a[++ ct] = point(i,visit[i]);
	for(int i = 0; i <= ct && i <= 31; i ++)
		for(int j = 0; j <= n; j ++)
			for(int k = 0; k <= m; k ++) 
				dp[i][j][k] = 0;
	for(int i = 0; i <= ct + 1; i ++)
		for(int j = 0; j <= n; j ++)
			for(int k = 0; k <= m; k ++) f[i][j][k] = 0;
	dp[0][0][0] = 1;
	int sum = 0,tot = 0,V = 0,Sum[110];
	memset(Sum,0,sizeof(Sum));
	Sum[0] = 1;
	for(int i = 0; i < ct && sum <= m; i ++) {
		for(int j = 0; j < a[i + 1].y; j ++) {
			if(j * a[i + 1].x + sum > m) break;
			add(dp[i + 1][tot + j][sum + j * a[i + 1].x],Sum[i] * c[tot + j][j]);
		}
		if(sum + a[i + 1].x * a[i + 1].y > m) Sum[i + 1] = 0;
		else Sum[i + 1] = Sum[i] * c[tot + a[i + 1].y][tot] % mod;
		sum += a[i + 1].x * a[i + 1].y;
		tot += a[i + 1].y;
	}
	tot = 0;
	f[ct + 1][0][0] = 1;
	for(int i = ct + 1; i >= 1; i --) {
		for(int j = 0; j <= tot; j ++) {
			for(int k = 0; k <= m; k ++) {
				if(!f[i][j][k]) continue;
				for(int r = 0; r <= a[i - 1].y; r ++) {
					if(r * a[i - 1].x + k > m) break;
					add(f[i - 1][j + r][k + r * a[i - 1].x],f[i][j][k] * c[j + r][r]);
				}
			}
		}
		tot += a[i - 1].y;
	}
	for(int i = 1; i <= ct + 1; i ++) {
		for(int j = 0; j <= n; j ++) {
			for(int k = 1; k <= m; k ++) {
				f[i][j][k] += f[i][j][k - 1];
				if(f[i][j][k] >= mod) f[i][j][k] -= mod;
			}
		}
	}
	int ans = Sum[ct];
	for(int i = 1; i <= ct && i <= 31; i ++) 
		for(int j = 0; j <= n; j ++)
			for(int k = 0; k <= m; k ++) {
				if(dp[i][j][k] == 0) continue;
				for(int r = 0; r + j <= n; r ++) {
					int st = m - k - a[i].x;
					int ed = m - k;
					int x = f[i + 1][r][ed];
					if(st >= 0) x -= f[i + 1][r][st];
					//cout << k << " " << r << " " <<  x << " " << st << " " << ed << " " << f[2][0][0] << " " if[2][0][1] << endl;
					add(ans,dp[i][j][k] * x % mod * c[j + r][r]);
				}
			}
	cout << ans << endl;
}

int main()
{
	init();
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case %d: ",cas);
		solve();
	}
	return 0;
}
