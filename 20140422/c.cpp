#include <bits/stdc++.h>
using namespace std;

const long long oo = 1LL << 50;
const int N = 20010;
long long dp[510][N];
int s[510][N];
long long cost[N], sum[N];
int pos[256];
char str[N];
char str2[N];
int n, m, q[N];

void init() {
	for (int i = 1; i <= 26; i++) {
		pos[str2[i]] = i - 1;
	}
	cost[0] = sum[0] = 0;
	for (int i = 1; i <= n; i++) {
		cost[i] = cost[i - 1] + (i - pos[str[i]]) * pos[str[i]];
		sum[i] = sum[i - 1] + pos[str[i]];
	}
}

long long get_cost(int i, int j) {
	if (i > j) return 0;
	return cost[j] - cost[i - 1] - (sum[j] - sum[i - 1]) * i;
}

long long get_val(int dep,int a,int b)
{
    return (dp[dep][a] - dp[dep][b]) + (cost[b] - cost[a]) + (sum[a] * (a + 1) - sum[b] * (b + 1));
}

void solve()
{
	scanf("%s%d", str2 + 1, &m);
	scanf("%s",str + 1);
	n = strlen(str + 1);
	init();
    for(int i = 1; i <= n; i ++) dp[1][i] = get_cost(1,i);
    for(int i = 2; i <= m; i ++) {
        int top = 0,tail = 0;
        q[tail ++] = i - 1;
        for(int j = i; j <= n; j ++) {
            while(top + 1 < tail && dp[i - 1][q[top]] + get_cost(q[top] + 1,j) >= dp[i - 1][q[top + 1]] + get_cost(q[top + 1] + 1,j)) top ++;
            dp[i][j] = dp[i - 1][q[top]] + get_cost(q[top] + 1,j);
            while(top + 1 < tail && get_val(i - 1,q[tail - 1],q[tail - 2]) * (j - q[tail - 1]) >= get_val(i - 1,j,q[tail - 1]) * (q[tail - 1] - q[tail - 2])) tail --;
            q[tail ++] = j;
        }
    }
	printf("%lld\n",dp[m][n]);
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case %d: ",cas);
		solve();
	}
	return 0;
}


