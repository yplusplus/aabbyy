#include <bits/stdc++.h>
using namespace std;

const int N = 43;
int sum[N][N],lt[N],rt[N];
char s[N][N],str[N][N];
int n1,n2,m1,m2;

void solve()
{
	int rr,cc;
	int mx = -1,ansx1 = -1,ansy1 = -1,ansx2 = -1,ansy2 = -1;
	for(int i = -n2; i <= n1; i ++) {
		for(int j = -m2; j <= m1; j ++) {
			memset(sum,0,sizeof(sum));
			for(int k = 1; k <= n2; k ++) {
				for(int r = 1; r <= m2; r ++) {
					if(i + k >= 1 && i + k <= n1 && j + r >= 1 && j + r <= m1) {
						if(str[k][r] == s[i + k][j + r]) sum[k][r] = 1;
					}
				}
			}
			for(int k = 1; k <= n2; k ++) {
				for(int r = 1; r <= m2; r ++) {
					if(sum[k][r]) sum[k][r] += sum[k - 1][r];
				}
				sum[k][0] = sum[k][m2 + 1] = -1;
				for(int r = 1; r <= m2; r ++) {
					lt[r] = r;
					while(sum[k][r] <= sum[k][lt[r] - 1]) lt[r] = lt[lt[r] - 1];
				}
				for(int r = m2; r >= 1; r --) {
					rt[r] = r;
					while(sum[k][r] <= sum[k][rt[r] + 1]) rt[r] = rt[rt[r] + 1];
				}
				for(int r = 1; r <= m2; r ++) {
					if(sum[k][r] * (rt[r] - lt[r] + 1) > mx) {
						mx = sum[k][r] * (rt[r] - lt[r] + 1);
						ansx2 = k - sum[k][r] + 1;
						ansy2 = lt[r];
						ansx1 = ansx2 + i;
						ansy1 = ansy2 + j;
						rr = sum[k][r];
						cc = rt[r] - lt[r] + 1;
					}
				}
			}
		}
	}
	if(mx == 0) printf("0 0\n");
	else {
		printf("%d %d\n",rr,cc);
		printf("%d %d\n",ansx1,ansy1);
		printf("%d %d\n",ansx2,ansy2);
	}
}
		
int main()
{
	while(scanf("%d%d",&n1,&m1) != EOF) {
		for(int i = 1; i <= n1; i ++)
			scanf("%s",s[i] + 1);
		scanf("%d%d",&n2,&m2);
		for(int i = 1; i <= n2; i ++)
			scanf("%s",str[i] + 1);
		solve();
	}
	return 0;
}
