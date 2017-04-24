#include <bits/stdc++.h>
using namespace std;

double dp[1000110];
int s,a,d;
int visit[1000010];
int times;

double solve(int n)
{
    if(n == 0) return 0;
    if(n == 1) return s + a + d;
    if(visit[n] == times) return dp[n];
    visit[n] = times;
    if(n & 1) return dp[n] = d + 0.5 * s + 0.5 * a + 0.5 * (solve(n / 2) + solve((n + 1) / 2));
    else return dp[n] = d + solve(n / 2);
}

int main()
{
    memset(visit,0,sizeof(visit));
    times = 0;
    int n;
    int t;
    scanf("%d",&t);
    while(t --) {
        ++ times;
        scanf("%d%d%d%d",&n,&d,&s,&a);;
        printf("%.3lf\n",solve(n));
    }
    return 0;
}

