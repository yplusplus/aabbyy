#include <bits/stdc++.h>
using namespace std;

const long long oo = 1LL << 60;
const int N = 100010;
struct tree
{
	int lt,rt,flag;
}a[N * 4];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].flag = 0;
	if(lt == rt) return;
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void down(int step)
{
	if(!a[step].flag) return;
	a[2 * step].flag = a[step].flag;
	a[2 * step + 1].flag = a[step].flag;
	a[step].flag = 0;
}

void insert(int lt,int rt,int step,int val)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		a[step].flag = val;
		return;
	}
	down(step);
	if(rt <= a[2 * step].rt) insert(lt,rt,2 * step,val);
	else if(lt > a[2 * step].rt) insert(lt,rt,2 * step + 1,val);
	else {
		insert(lt,a[2 * step].rt,2 * step,val);
		insert(a[2 * step + 1].lt,rt,2 * step + 1,val);
	}
}

int query(int pos,int step)
{
	if(a[step].lt == a[step].rt) {
		return a[step].flag;
	}
	down(step);
	if(pos <= a[2 * step].rt) return query(pos,2 * step);
	else return query(pos,2 * step + 1);
}

struct point
{
	int x,y;
	void read() {
		scanf("%d%d",&x,&y);
	}
}c[N];

long long dp[N][2];
int next[N][2];

void update(long long &x,long long y)
{
	x = min(x,y);
}

int main()
{
	int n,m,r;
	scanf("%d%d%d",&m,&r,&n);
	for(int i = 1; i <= n; i ++)
		c[i].read();
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j < 2; j ++)
			dp[i][j] = oo;
	init(1,m,1);
	memset(next,0,sizeof(next));
	for(int i = n; i >= 1; i --) {
		if(c[i].x > 1) next[i][0] = query(c[i].x - 1,1);
		if(c[i].y < m) next[i][1] = query(c[i].y + 1,1);
		insert(c[i].x,c[i].y,1,i);
	}
	int id = query(r,1);
	if(!id) {
		printf("0\n");
		return 0;
	}
//	cout << "fuck " << id << endl;
	if(c[id].x > 1) dp[id][0] = abs(r - c[id].x + 1);
	if(c[id].y < m) dp[id][1] = abs(c[id].y + 1 - r);
	long long ans = oo;
//	for(int i = 1; i <= n; i ++)
//		cout << next[i][0] << " " << next[i][1] << endl;

	for(int i = 1; i <= n; i ++) {
		if(next[i][0] == 0) ans = min(ans,dp[i][0]);
		if(next[i][1] == 0) ans = min(ans,dp[i][1]);
		if(next[i][0]) {
			id = next[i][0];
			r = c[i].x - 1;
			if(c[id].x > 1) update(dp[id][0],dp[i][0] + abs(r - c[id].x + 1));
			if(c[id].y < m) update(dp[id][1],dp[i][0] + abs(c[id].y + 1 - r));
		}
		if(next[i][1]) {
			id = next[i][1];
			r = c[i].y + 1;
			if(c[id].x > 1) update(dp[id][0],dp[i][1] + abs(r - c[id].x + 1));
			if(c[id].y < m) update(dp[id][1],dp[i][1] + abs(c[id].y + 1 - r));
		}
	}
	cout << ans << endl;
	return 0;
}
