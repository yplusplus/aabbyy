#include <bits/stdc++.h>
using namespace std;

const int N = 110;
struct point
{
	int x,y;
	void read() {
		scanf("%d%d",&x,&y);
	}
	friend bool operator < (const point &p,const point &q) {
		return p.x < q.x;
	}
}a[N];
int prex[N][N][N],prey[N][N][N];
double dp[N][N][N],dist[N][N];
int sqr(int x)
{
	return x * x;
}

double dis(point p,point q)
{
	return sqrt(1.0 * (sqr(p.x - q.x) + sqr(p.y - q.y)));
}

int ansx[N],ansy[N],c1,c2;

void output(int step,int n,int m)
{
	if(step > 1) output(step - 1,prex[step][n][m],prey[step][n][m]);
	ansx[++ c1] = n,ansy[++ c2] = m;
}

int main()
{
	int n,x,y;
	int cas = 0;
	while(scanf("%d%d%d",&n,&x,&y) != EOF) {
		if(!n && !x && !y) break;
		for(int i = 1; i <= n; i ++) a[i].read();
		x ++,y ++;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				dist[i][j] = dis(a[i],a[j]);
		for(int i = 0; i <= n; i ++)
			for(int j = 0; j <= n; j ++)
				for(int k = 0; k <= n; k ++)
					dp[i][j][k] = 1e20;
		dp[1][1][1] = 0;
		for(int i = 2; i <= n; i ++) {
			if(i == x) {
				for(int j = 1; j < i; j ++) {
					for(int k = 1; k < i; k ++) {
						if(dp[i - 1][j][k] + dist[j][i] < dp[i][i][k]) {
							dp[i][i][k] = dp[i - 1][j][k] + dist[j][i];
							prex[i][i][k] = j;
							prey[i][i][k] = k;
						}
					}
				}
			}
			else if(i == y) {
				for(int j = 1; j < i; j ++)
					for(int k = 1; k < i; k ++)
						if(dp[i - 1][j][k] + dist[k][i] < dp[i][j][i]) {
							dp[i][j][i] = dp[i - 1][j][k] + dist[k][i];
							prex[i][j][i] = j;
							prey[i][j][i] = k;
						}
			}
			else if(i == n) {
				for(int j = 1; j < i; j ++)
					for(int k = 1; k < i; k ++)
						if(dp[i - 1][j][k] + dist[j][n] + dist[k][n] < dp[n][n][n]) {
							dp[n][n][n] = dp[i - 1][j][k] + dist[j][n] + dist[k][n];
							prex[n][n][n] = j;
							prey[n][n][n] = k;
						}
			}
			else {
				for(int j = 1; j < i; j ++)
					for(int k = 1; k < i; k ++) {
						if(dp[i - 1][j][k] + dist[j][i] < dp[i][i][k]) {
							dp[i][i][k] = dp[i - 1][j][k] + dist[j][i];
							prex[i][i][k] = j;
							prey[i][i][k] = k;
						}
						if(dp[i - 1][j][k] + dist[k][i] < dp[i][j][i]) {
							dp[i][j][i] = dp[i - 1][j][k] + dist[k][i];
							prex[i][j][i] = j;
							prey[i][j][i] = k;
						}
					}
			}
		}
		c1 = c2 = 0;
		output(n,n,n);
		int t1 = 0,t2 = 0;
		for(int i = 1; i <= c1; i ++)
			if(i == 1 || ansx[i] != ansx[i - 1]) ansx[++ t1] = ansx[i];
		for(int i = 1; i <= c2; i ++)
			if(i == 1 || ansy[i] != ansy[i - 1]) ansy[++ t2] = ansy[i];
		printf("Case %d: %.2lf\n",++ cas,dp[n][n][n]);
		if(ansx[2] == 2) {
			for(int i = 1; i <= t1; i ++) {
				printf("%d",ansx[i] - 1);
				if(i < t1) printf(" ");
			}
			for(int i = t2 - 1; i >= 1; i --) {
				printf(" %d",ansy[i] - 1);
			}
			printf("\n");
		}
		else {
			for(int i = 1; i <= t2; i ++) {
				printf("%d",ansy[i] - 1);
				if(i < t2) printf(" ");
			}
			for(int i = t1 - 1; i >= 1; i --) {
				printf(" %d",ansx[i] - 1);
			}
			printf("\n");
		}
	}
	return 0;
}
