#include <bits/stdc++.h>
using namespace std;

long long ans[20000010];
long long p10[20];
int pri[4000010];
bool a[16000010];

void prime()
{
	memset(a,0,sizeof(a));
	for(int i = 2; i <= 2000; i ++)
		if(!a[i])
			for(int j = i * i; j <= 4000000; j += i)
				a[j] = 1;
	for(int i = 0, j = 2; j <= 4000000; j ++)
		if(!a[j]) pri[i ++] = j;
}

long long fac[55],num[55];
int cnt;
void factor(long long n)
{
	cnt = 0;
	for(int i = 0; (long long)pri[i] * pri[i] <= n; i ++) {
		if(n % pri[i]) continue;
		num[cnt] = 0;
		fac[cnt] = pri[i];
		while(n % pri[i] == 0) n /= pri[i],num[cnt] ++;
		cnt ++;
	}
	if(n > 1) {
		num[cnt] = 1;
		fac[cnt ++] = n;
	}
}

int tot;
void dfs(int pos,long long x)
{
	if(pos == cnt) {
		ans[++tot] =x;
		return;
	}
	long long y = 1;
	for(int i = 0; i <= num[pos]; i ++) {
		dfs(pos + 1,x * y);
		y *= fac[pos];
	}
}

int main()
{
	prime();
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	p10[0] = 1;
	for(int i = 1; i < 20; i ++) p10[i] = p10[i - 1] * 10;
	int visit[25];
	char s[25];
	int n,t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%s",s);
		long long gcd = 0;
		n = strlen(s);
		memset(visit,0,sizeof(visit));
		cnt = tot = 0;
		bool found = false;
		int maxn = 0;
		for(int i = 0; i < n; i ++) {
			if(visit[i]) continue;
			long long sum = 0;
			int t = 0;
			for(int j = i; j < n; j ++) {
				if(s[i] != s[j]) continue;
				t++;
				visit[j] = 1;
				sum += p10[n - 1 - j];
			}
			if (t % 3 != 1) found = true;
			maxn = max(maxn,t);
			cnt++;
			gcd = __gcd(sum, gcd);
		}
		if (cnt == 10 && !found) {
			gcd = 9;
			if(maxn == 4) gcd = 3;
		}
		factor(gcd);
		tot = 0;		
		dfs(0,1);
		sort(ans + 1,ans + tot + 1);
		printf("Case %d:",cas);
		for(int i = 1; i <= tot; i ++) {
		    printf(" %I64d",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
