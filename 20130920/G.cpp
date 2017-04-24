#include <iostream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10010;
int a[N],b[N];
bool cmp(int x,int y)
{
	return x > y;
}

int cal(int n,int m)
{
	if(n < m) swap(n,m);
	if(m == 1) return n / 3;
	if(m == 2) return 2 * (n / 3);
	return n * m / 3;
	int ans = (n / 3) * m;
	ans += (n % 3) * (m / 3);
	return ans;
}

void solve()
{
	int n,m,p,q;
	scanf("%d%d%d%d",&n,&m,&p,&q);
	for(int i = 1; i <= p; i ++)
		scanf("%d",&a[i]);
	for(int i = 1; i <= q; i ++)
		scanf("%d",&b[i]);
	sort(a + 1,a + p + 1,cmp);
	sort(b + 1,b + q + 1,cmp);
	a[0] = b[0] = 0;
	for(int i = 2; i <= p; i ++)
		a[i] += a[i - 1];
	for(int i = 2; i <= q; i ++)
		b[i] += b[i - 1];
	int ans = 0;
	int tot = cal(n,m);
	for(int i = 0; i <= tot && i <= q; i ++) {
		ans = max(ans,b[i] + a[min(p,(n * m - 3 * i) / 2)]);
	}
	printf("%d\n",ans);
}


int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case #%d: ",cas);
		solve();
	}
	return 0;
}