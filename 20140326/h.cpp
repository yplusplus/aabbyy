#include <bits/stdc++.h>
using namespace std;

struct point
{
	int x,y,z;
	void read() {
		scanf("%d%d%d",&x,&y,&z);
	}
	friend bool operator < (const point &p,const point &q) {
		return p.x < q.x;
	}
}a[35];
bool dp[35][35][350];

bool check(point a,point b,point c)
{
	if(c.x == b.x) return false;
	if(c.x > b.y + 1) return false;
	if(c.y <= b.y) return false;
	return c.x > a.y + 1;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		int n,m,r,x,y;
		scanf("%d%d%d",&n,&m,&r);
		for(int i = 1; i <= m; i ++) a[i].read();
		sort(a + 1,a + m + 1);
		memset(dp,false,sizeof(dp));
		for(int i = 1; i <= m; i ++) {
			if(a[i].x != 1) continue;
			if(a[i].y == n) continue;
			for(int k = i + 1; k <= m; k ++) {
				if(a[k].x != a[i].x && a[k].x <= a[i].y + 1 && a[i].y < a[k].y) {
					dp[i][k][a[i].z + a[k].z] = true;
//					cout << i << " " << k << endl;
				}
			}
		}
		for(int i = 1; i <= m; i ++)
			for(int j = i + 1; j <= m; j ++)
				for(int cost = 0; cost <= 300; cost ++) {
					if(!dp[i][j][cost]) continue;
					for(int k = j + 1; k <= m; k ++) {
						if(check(a[i],a[j],a[k]))
							dp[j][k][a[k].z + cost] = true;
					}
				}
		bool flag[350];
		memset(flag,false,sizeof(flag));
		for(int i = 1; i <= m; i ++)
			if(a[i].x == 1 && a[i].y == n) flag[a[i].z] = true;
		for(int i = 1; i <= m; i ++)
			for(int j = i + 1; j <= m; j ++)
				for(int k = 0; k <= 300; k ++)
					flag[k] |= dp[i][j][k];
//		for(int i = 1; i <= 300; i ++)
//			if(flag[i]) cout << i << " ";
//		cout << endl;
		long long ans = 0;
		while(r --) {
			scanf("%d%d",&x,&y);
			for(int i = 300; i >= 1 && x <= y; i --) {
				if(y < i) continue;
				if(!flag[i]) continue;
				//cout << "enter " << i << endl;
				long long tmp = min(y - i + 1,y - x + 1);
				ans += tmp * i;
				y -= tmp;
			}
		}
		printf("Case #%d: %lld\n",cas,ans);
	}
	return 0;
}
