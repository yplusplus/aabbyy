#include <bits/stdc++.h>
using namespace std;

const int N = 110;
struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.x - p.y != q.x - q.y) return p.x - p.y > q.x - q.y;
		return p.x > q.x;
	}
};

int sum[N],dp[N];
int A[N],M[N],G[N];
vector<int> v[N];
bool cmp(const point &a, const point &b) {
	int t1 = max(a.x, a.y + b.x);
	int t2 = max(b.x, b.y + a.x);
	return t1 < t2;
}

void dfs(int u,int pre)
{
	point a[N];
	int tot = 0,cnt = 0;
	for(int i = 0; i < v[u].size(); i ++) {
		int x = v[u][i];
		if(x == pre) continue;
		dfs(x,u);
		a[++ cnt] = point(dp[x],sum[x]);
		tot += sum[x];
	}
	if(cnt == 0) {
		dp[u] = sum[u] = M[u] + G[u];
		dp[u] = max(dp[u],A[u]);
		return;
	}
	sort(a + 1,a + cnt + 1, cmp);
	int tmp,lt = max(A[u],tot + M[u] + G[u]),rt = 1000000,mid;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		bool flag = true;
		mid -= M[u] + G[u];
		for(int i = 1; i <= cnt; i ++) {
			if(mid < a[i].x) {
				flag = false;
				break;
			}
			mid -= a[i].y;
		}
		mid = (lt + rt) >> 1;
		if(flag) tmp = mid,rt = mid - 1;
		else lt = mid + 1;
	}
	dp[u] = tmp;
	sum[u] = M[u] + G[u] + tot;
}

int main()
{
	int cas = 0;
	int n;
	while(scanf("%d",&n) != EOF) {
		if(!n) break;
		for(int i = 1; i <= n; i ++) {
			scanf("%d%d%d",&A[i],&M[i],&G[i]);
			v[i].clear();
		}
		int x,y;
		for(int i = 1; i < n; i ++) {
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		int ans = 0x7fffffff;
		for(int i = 1; i <= n; i ++) {
			memset(sum,0,sizeof(sum));
			dfs(i,0);
			ans = min(ans,dp[i]);
		}
		printf("Case %d: %d\n",++ cas,ans);
	}
	return 0;
}
