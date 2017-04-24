#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct tree
{
	int lt,rt;
	long long mix;
}a[N * 4];

long long f[N],b[N],c[N];
void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	if(lt == rt) {
		a[step].mix = c[lt];
		return;
	}
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	a[step].mix = min(a[2 * step].mix,a[2 * step + 1].mix);
}

long long query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step].mix;
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
	else return min(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

int main()
{
	int t;
	int n,m,x,y;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i ++) {
			scanf("%lld%lld",&b[i],&f[i]);
			c[i] = f[i] * b[i];
		}
		init(1,n,1);
		while(m --) {
			scanf("%d",&x);
			if(x == 0) {
				cout << 0 << endl;
				continue;
			}
			int lt = 1,rt = n,mid,ans = n;
			while(lt <= rt) {
				mid = (lt + rt) / 2;
				if(b[mid] <= x) {
					ans = mid;
					lt = mid + 1;
				}
				else rt = mid - 1;
			}
			long long sum = f[ans] * x;
			if(ans < n) sum = min(sum,query(ans + 1,n,1));
			printf("%lld\n",sum);
		}
	}
	return 0;
}
