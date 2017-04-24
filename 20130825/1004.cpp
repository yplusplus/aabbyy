#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20010;
int dp[N][4];
int pri[10010];

void prime()
{
	bool a[90010];
	memset(a,false,sizeof(a));
	for(int i =2; i <= 300; i ++)
		if(!a[i])
			for(int j = i * i; j <= 90000; j += i)
				a[j] = true;
//	int tot = 0;
	for(int i = 0, j = 2; j <= 90000; j ++) {
		if(!a[j]) {
//			if(j <= 20000) tot ++;
			pri[i ++] = j;
		}
	}
//	cout << tot << endl;
}

int main()
{
	prime();
	memset(dp,0,sizeof(dp));
	dp[0][0] = 1;
	for(int i = 0; pri[i] <= 20000; i ++) {
		for(int j = 20000; j >= pri[i]; j --) {
			for(int k = 1; k <= 3; k ++)
				dp[j][k] += dp[j - pri[i]][k - 1];
		}
	}
	int n;
	while(scanf("%d",&n) != EOF) {
		if(n % 2 == 0) printf("%d\n",dp[n][2]);
		else printf("%d\n",dp[n][3]);
	}
	return 0;
}		
