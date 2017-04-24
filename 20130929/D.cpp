#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 410;
int dp[N][N * 2];
int sum[N][N * 2];

void update(int &x,int y)
{
	if(x < y) x = y;
}

int main()
{
	int cas = 0,n;
	while(scanf("%d",&n),n != 0) {
		for(int i = 0; i <= n + 5; i ++)
			sum[i][0] = 0;
		int ans = -2100000000;
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j < 2 * i; j ++) {
				scanf("%d",&sum[i][j]);
				sum[i][j] += sum[i][j - 1];
			}
		}
		/*
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j < 2 * i; j ++) {
				printf("%d ",sum[i][j]);
			}
			printf("\n");
		}*/
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j < 2 * i; j += 2) {
				int s = 0;
				for(int k = 0; i + k <= n; k ++) {
					s += sum[i + k][j + 2 * k] - sum[i + k][j - 1];
					update(ans,s);
				//	if(i == 2 && j == 3) printf("%d %d %d %d\n",i,j,k,s);
				}
			}
		}
		for(int i = 1; i <= n; i ++) {
			for(int j = 2; j < 2 * i; j += 2) {
				int s = 0;
				for(int k = 0; i - k >= 1; k ++) {
					if(j - 2 * k - 1 < 0) break;
					if(2 * (i - k) - 1 < j) break;
					s += sum[i - k][j] - sum[i - k][j - 2 * k - 1];
					update(ans,s);
				}
			}
		}
		printf("%d. %d\n",++ cas,ans);
	}
	return 0;
}

