#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[10010];
int pri[90010];

void prime()
{
	int visit[90010];
	memset(visit,0,sizeof(visit));
	for(int i = 2; i * i <= 90000; i ++)
		if(!visit[i])
			for(int j = i * i; j <= 90000; j += i)
				visit[j] = 1;
	for(int i = 0, j = 2; j <= 90000; j ++)
		if(!visit[j]) pri[i ++] = j;
}

int fac[55],cnt;

void factor(int n)
{
	cnt = 0;
	for(int i = 0; pri[i] * pri[i] <= n; i ++) {
		while(n % pri[i] == 0) n /= pri[i],fac[++ cnt] = pri[i];
	}
	if(n > 1) fac[++ cnt] = n;
}

bool check(int n,int x)
{
	factor(x);
	return fac[1] > a[n - 1];
}

int main()
{
	prime();
	int t,n;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d",&n);
		for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
		sort(a + 1,a + n + 1);
		printf("Case #%d: ",cas);
		if(a[n] == 1 || n == 1) {
			printf("Good Function\n");
			continue;
		}
		if(n > 1 && a[n - 1] == 1) {
			printf("Good Function\n");
			continue;
		}
		for(int i = a[n] + 1; ; i ++)
			if(check(n,i)) {
				printf("%d\n",i);
				break;
			}
	}
	return 0;
}


