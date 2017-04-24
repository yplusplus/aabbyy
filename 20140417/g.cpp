#include <bits/stdc++.h>
using namespace std;

int a[35][15];
int bit[1 << 12];
vector<int> v[25];
int stk[25];
int pre[25][35];
int times[25][35];
int c[25][25];
double dp[1 << 12];
int f[1 << 12];
int has[25][25];
int adj[25][25];

void output(int state,int flag)
{
	if(!state) return;
	output(state ^ (1 << f[state]),0);
	printf("%d",f[state] + 1);
	if(flag == 0) printf(" ");
	else printf("\n");
}

int main()
{
	freopen("musical.in","r",stdin);
	freopen("musical.out","w",stdout);
	for(int i = 1; i < (1 << 12); i ++)
		for(int j = 0; j < 12; j ++)
			if(i & (1 << j)) bit[i] ++;
	int n,m,r;
	scanf("%d%d%d",&n,&m,&r);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < 3; j ++)
			scanf("%d",&a[i][j]);
	int x,y;
	while(m --) {
		scanf("%d%d",&x,&y);
		x --,y --;
		stk[x] |= (1 << y);
		stk[y] |= (1 << x);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i = 1; i <= r; i ++) {
		for(int j = 1; j <= n; j ++) {
			scanf("%d",&c[i][j]);
			c[i][j] --;
		}
	}
	memset(pre,0,sizeof(pre));
	memset(times,0,sizeof(times));
	for(int T = 1; T <= n; T ++) {
		for(int i = 1; i <= r; i ++) {
			for(int j = 1; j < T; j ++) {
				if(c[i][j] != -1) pre[T][i] |= (1 << c[i][j]);
			}
		}
	}
	for(int T = 1; T <= n; T ++) {
		for(int i = 0; i < n; i ++) {
			for(int j = 1; j <= r; j ++) {
				if(c[j][T] == i) has[T][i] ++;
			}
		}
	}
	for(int T = 1; T <= n; T ++)
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				if(i == j || stk[i] & (1 << j))
					adj[T][i] += has[T][j];
	memset(f,-1,sizeof(f));
	for(int i = 0; i < (1 << n); i ++) dp[i] = -1;
	dp[0] = 0;
	for(int i = 0; i < (1 << n) - 1; i ++) {
		for(int j = 0; j < n; j ++) {
			if(i & (1 << j)) continue;
			int T = bit[i] + 1;
			double cost = 0;
			//type 1
			cost += a[j][1] * 1.0 / (has[T][j] + 1);
			//type 2
			cost += a[j][2] * 1.0 / (adj[T][j] + 1);
			for(int k = 0; k < n; k ++)
				if(stk[j] & (1 << k))
					cost += a[k][2] * 1.0 / (adj[T][k] + 1);
			cost *= 7;
			//type 0
			int maxn = bit[i & stk[j]],cnt = 1;
			for(int k = 1; k <= r; k ++)
				if(c[k][T] != j) continue;
				else if(bit[pre[T][k] & stk[j]] == maxn) cnt ++;
				else if(bit[pre[T][k] & stk[j]] > maxn) {
					cnt = 1;
					maxn = bit[pre[T][k] & stk[j]];
				}
			if(maxn == bit[i & stk[j]]) cost += a[j][0] * 1.0 / cnt;
			if(dp[i | (1 << j)] < dp[i] + cost) {
				dp[i | (1 << j)] = dp[i] + cost;
				f[i | (1 << j)] = j;
			}
		}
	}
	printf("%.16lf\n",dp[(1 << n) - 1]);
	output((1 << n) - 1,1);	
	return 0;
}
