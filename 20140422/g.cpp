#include <bits/stdc++.h>
using namespace std;

const int N = 50010;
int n;
int a[N],b[N];

int get_upper(int x)
{
	int lt = 1,rt = n,mid,ans = 0;
	if(a[1] > x) return n;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		if(a[mid] <= x) ans = n - mid,lt = mid + 1;
		else rt = mid - 1;
	}
	return ans;
}

int main()
{
	int t;
	int ut,m,x;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d%d",&ut,&n,&m);
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&a[i]);
			b[i] = a[i];
		}
		sort(a + 1,a + n + 1);
		printf("Case %d:\n",cas);
		while(m --) {
			scanf("%d",&x);
			if(x <= n) printf("%d\n",b[x]);
			else {
				int lt = 1,rt = ut,mid,ans = 0;
				while(lt <= rt) {
					mid = (lt + rt) >> 1;
					if(mid + get_upper(mid) >= x) ans = mid,rt = mid - 1;
					else lt = mid + 1;
				}
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
