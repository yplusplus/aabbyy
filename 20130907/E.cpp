#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int oo = 1000000000;
int dp[110][110][2],a[110][110];
int f[110][110][110][2];

int solve(int n,int m)
{
	dp[1][1][0] = dp[1][1][1] = a[1][1];
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= m; j ++)
			for(int k = 0; k <= 100; k ++)
				f[i][j][k][0] = f[i][j][k][1] = -oo;
	f[1][1][abs(a[1][1])][0] = a[1][1];
	f[1][1][abs(a[1][1])][1] = a[1][1];
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			if(i == 1 && j == 1) continue;
			int mi = -oo;
			for(int k = abs(a[i][j]) + 1; k <= 100; k ++) {
			    mi = max(mi,max(f[i][j - 1][k][1],f[i - 1][j][k][1]));
			}
            if(mi == -oo) mi = 0;
			dp[i][j][0] = a[i][j] - mi;
			mi = -oo;
			for(int k = abs(a[i][j]) + 1; k <= 100; k ++) {
				mi = max(mi,max(f[i][j - 1][k][0],f[i - 1][j][k][0]));
			}
            if(mi == -oo) mi = 0;
			dp[i][j][1] = a[i][j] - mi;
			f[i][j][abs(a[i][j])][1] = max(dp[i][j][1],max(f[i - 1][j][abs(a[i][j])][1],f[i][j - 1][abs(a[i][j])][1]));
			f[i][j][abs(a[i][j])][0] = max(dp[i][j][0],max(f[i - 1][j][abs(a[i][j])][0],f[i][j - 1][abs(a[i][j])][0]));
			for(int k = 0; k <= 100; k ++) {
				if(k == abs(a[i][j])) continue;
				f[i][j][k][0] = max(f[i - 1][j][k][0],f[i][j - 1][k][0]);
				f[i][j][k][1] = max(f[i - 1][j][k][1],f[i][j - 1][k][1]);
			}
		}
	}
	
	int ans = -oo;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			ans = max(ans,dp[i][j][0]);
	return ans;
}

void read(int &x) {
    char c;
    while(1) {
        c = getchar();
        if(isdigit(c) || c == '-') break;
    }
    int flag = 1;
    if(c == '-') x = 0,flag = -1;
    else x = c -'0';
    while(1) {
        c = getchar();
        if(isdigit(c)) x = 10 * x + (c - '0');
        else break;
    }
    x *= flag;
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				read(a[i][j]);
		printf("%d\n",solve(n,m));
	}
	return 0;
}
