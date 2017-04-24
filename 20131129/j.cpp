#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
struct tree
{
	int lt,rt;
	long long mix;
}a[N * 4];

long long sum[N];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	if(lt == rt) {
		a[step].mix = sum[lt];
		return;
	}
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	a[step].mix = min(a[2 * step].mix,a[2 * step + 1].mix);
}

int query(int lt,int rt,int step,long long val)
{
	if(a[step].mix > val) return -1;
	if(a[step].lt == lt && a[step].rt == rt) {
		if(a[step].mix > val) return -1;
	}
	if(a[step].lt == a[step].rt) return a[step].lt;
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step,val);
	if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1,val);
	int y = query(a[2 * step + 1].lt,rt,2 * step + 1,val);
	if(y != -1 && sum[y] <= val) return y;
	int x = query(lt,a[2 * step].rt,2 * step,val);
	return x;
}

int c[N];
int main()
{
	int t,n,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		sum[0] = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&c[i]);
			sum[i] = sum[i - 1] + c[i];
		}
		init(0,n,1);
		int ans = -1;
		for(int i = 1; i <= n; i ++) {
			int x = query(0,i - 1,1,sum[i] - m);
			if(sum[x] <= sum[i] - m) {
				if(ans == -1) ans = i - x;
				else ans = min(ans,i - x);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
