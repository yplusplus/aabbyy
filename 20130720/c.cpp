#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int err = 45;
int dp[6][48][1 << 10][2],dp2[6][48][1 << 10][3];
int bit[25];
int cnt[1 << 10];
int c1[48][48][1 << 10];
int c2[48][48][1 << 10];
int num[15] = {0,81,7389,676133,62563644};
struct point
{
	int flag,val,state,sum;
	point() {}
	point(int flag,int val,int state,int sum):flag(flag),val(val),state(state),sum(sum) {}
}a[100010],b[100010];

bool check(int sum1,int sum2,int digit)
{
	if(sum1 == sum2) return false;
	digit += (sum2 - sum1);
	return digit >= 1 && digit <= 9;
}
	
int cal(int n)
{
	if(n < 10) return 0;
	int len = 0;
	while(n) {
		bit[++ len] = n % 10;
		n /= 10;
	}
	int ans = 0;
	
	for(int i = 1; 2 * i < len; i ++)
		ans += num[i];
	if(len & 1) return ans;
	reverse(bit + 1,bit + len + 1);
	int half = len / 2;
	memset(dp2,0,sizeof(dp2));
	for(int i = 0; i < 10; i ++) {
		if(i == bit[half + 1]) dp2[1][i][1 << i][1] = 1;
		else if(i > bit[half + 1]) dp2[1][i][1 << i][2] = 1;
		else dp2[1][i][1 << i][0] = 1;
	}
	for(int i = 2; i <= half; i ++) {
		for(int j = 0; j <= (i - 1) * 9; j ++) {
			for(int k = 0; k < (1 << 10); k ++) {
				if(cnt[k] > half) continue;
				for(int r = 0; r < 10; r ++) {
					dp2[i][j + r][k | (1 << r)][0] += dp2[i - 1][j][k][0];
					dp2[i][j + r][k | (1 << r)][2] += dp2[i - 1][j][k][2];
					if(r == bit[i + half])
						dp2[i][j + r][k | (1 << r)][1] += dp2[i - 1][j][k][1];
					else if(r < bit[i + half])
						dp2[i][j + r][k | (1 << r)][0] += dp2[i - 1][j][k][1];
					else dp2[i][j + r][k | (1 << r)][2] += dp2[i - 1][j][k][1];
				}
			}
		}
	}
	int tot = 0;
	for(int i = 0; i <= 45; i ++)
		for(int j = 0; j < (1 << 10); j ++) {
			if(cnt[j] > half) continue;
			if(dp2[half][i][j][0]) a[++ tot] = point(0,i,j,dp2[half][i][j][0]);
			if(dp2[half][i][j][1]) a[++ tot] = point(1,i,j,dp2[half][i][j][1]);
			if(dp2[half][i][j][2]) a[++ tot] = point(2,i,j,dp2[half][i][j][2]);
		}
	
	for(int number = 1; number <= bit[1]; number ++) {
		memset(dp,0,sizeof(dp));
		dp[1][number][0][number == bit[1]] = 1;
		for(int i = 2; i <= half; i ++) 
			for(int j = 0; j <= (i - 1) * 9; j ++) {
				for(int k = 0; k < (1 << 10); k ++) {
					if(cnt[k] > half) continue;
					for(int r = 0; r < 10; r ++) {
						dp[i][j + r][k | (1 << r)][0] += dp[i - 1][j][k][0];
						if(r == bit[i]) dp[i][j + r][k | (1 << r)][1] += dp[i - 1][j][k][1];
						else if(r < bit[i]) dp[i][j + r][k | (1 << r)][0] += dp[i - 1][j][k][1];
					}
				}
			}
		for(int i = 0; i <= 45; i ++)
			for(int j = 0; j < (1 << 10); j ++) {
				if(cnt[j] > half) continue;
				if(dp[half][i][j][0]) {
					for(int k = 1; k <= tot; k ++) {
						if(c1[i][a[k].val][j]) ans += dp[half][i][j][0] * a[k].sum;
						else if(c2[i][a[k].val][a[k].state]) ans += dp[half][i][j][0] * a[k].sum;
						else if(check(i,a[k].val,number)) ans += dp[half][i][j][0] * a[k].sum;
					}
				}
				if(dp[half][i][j][1]) {
					for(int k = 1; k <= tot; k ++) {
						if(a[k].flag == 2) continue;
						if(c1[i][a[k].val][j]) ans += dp[half][i][j][1] * a[k].sum;
						else if(c2[i][a[k].val][a[k].state]) ans += dp[half][i][j][1] * a[k].sum;
						else if(check(i,a[k].val,number)) ans += dp[half][i][j][1] * a[k].sum;
					}
				}
			}


	}
	return ans;
}

int mabs(int x)
{
	return x < 0 ? (-x) : x;
}

bool check1(int sum1,int sum2,int digit)
{
	if(sum1 == sum2) return false;
	digit += (sum2 - sum1);
	return digit >= 0 && digit <= 9;
}

void init()
{
	memset(c1,0,sizeof(c1));
	memset(c2,0,sizeof(c2));
	for(int i = 0; i <= 45; i ++)
		for(int j = 0; j <= 45; j ++)
			if(mabs(i - j) > 9) continue;
			else {
				for(int k = 0; k < (1 << 10); k ++) {
					if(cnt[k] > 5) continue;
					for(int r = 0; r < 10; r ++) {
						if(k & (1 << r))
							if(check1(i,j,r)) c1[i][j][k] = 1;
					}
				}
			}
	for(int i = 0; i <= 45; i ++)
		for(int j = 0; j <= 45; j ++)
			if(mabs(i - j) > 9) continue;
			else {
				for(int k = 0; k < (1 << 10); k ++) {
					if(cnt[k] > 5) continue;
					for(int r = 0; r < 10; r ++) {
						if(k & (1 << r))
							if(check1(j,i,r)) c2[i][j][k] = 1;
					}
				}
			}
}


int main()
{
	init();
	memset(cnt,0,sizeof(cnt));
	for(int i = 0; i < (1 << 10); i ++)
		for(int j = 0; j < 10; j ++)
			if(i & (1 << j)) cnt[i] ++;
//	cout << cal(999999) << endl;
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		printf("%d\n",cal(m) - cal(n - 1));
	}
	return 0;
}

