#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 2510;
long double dp[55][N],f[55][N];
int s[55][N];
long double sum[N],a[N];
long double S[N];
long double get_cost(int x,int y)
{
	if(x > y) return 0;
	int n = y - x + 1;
	long double ave = 1.0 * (sum[y] - sum[x - 1]) / n;
	return n * ave * ave - 2 * ave * (sum[y] - sum[x - 1]) + S[y] - S[x - 1];
}

int main()
{
	int n,m,r;
	int t;
    int tot = 0;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d%d",&n,&m,&r);
		int ct = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++) {
                //a[++ ct] = rand();
                double x;
                scanf("%lf",&x);
				a[++ ct] = x;
			}
		sort(a + 1,a + ct + 1);
		n = n * m;
		sum[0] = 0;
		S[0] = 0;
		for(int i = 1; i <= n; i ++) {
			sum[i] = sum[i - 1] + a[i];
			S[i] = S[i - 1] + 1.0 * a[i] * a[i];
		}
		r = min(r,n);
		for(int i = 1; i <= n; i ++) {
			s[1][i] = 0;
			f[1][i] = dp[1][i] = get_cost(1,i);
		}
		for(int i = 2; i <= r; i ++) {
			for(int j = n; j >= i; j --) {
				int st = s[i - 1][j],ed = s[i][j + 1];
				if(j == n) {
					st = i - 1,ed = n;
				}
                else if(i == j) {
                    st = ed = i - 1;
                }
                st = max(st,i - 1);
                ed = min(ed,j - 1);
				dp[i][j] = 1e40;
				for(int k = st; k <= ed; k ++) 
					if(dp[i][j] > dp[i - 1][k] + get_cost(k + 1,j)) {
						dp[i][j] = dp[i - 1][k] + get_cost(k + 1,j);
						s[i][j] = k;
					}
			}
		}
        long double mix = 1e40;
        for(int i = 1; i <= r; i ++)
            mix = min(mix,dp[i][n]);
        dp[r][n] = mix;
		printf("%.2lf\n",(double)fabs(dp[r][n]));
	return 0;
}
