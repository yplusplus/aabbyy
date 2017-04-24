#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5010;
bool dp[N][26];
int pre[N][26];

void output(int n,int m)
{
	if(n > 1) output(n - 1,pre[n][m]);
	printf("%c",m + 'a');
}

int main()
{
	int n;
	char s[5010];
	scanf("%d",&n);
	scanf("%s",s + 1);
	memset(dp,false,sizeof(dp));
	memset(pre,-1,sizeof(pre));
	for(int i = 0; i < n; i ++)
		dp[1][i] = true;
	int m = strlen(s + 1);
	for(int i = 1; i <= m; i ++) {
		for(int j = 0; j < n; j ++) {
			if(!dp[i][j]) continue;
			for(int k = 0; k < n; k ++) {
				if(s[i] == '=' && j != k) continue;
				if(s[i] == '>' && j <= k) continue;
				if(s[i] == '<' && j >= k) continue;
				dp[i + 1][k] = true;
				pre[i + 1][k] = j;
			}
		}
	}
	bool flag = false;
	for(int i = 0; i < n; i ++) 
		if(dp[m + 1][i]) {
			flag = true;
			output(m + 1,i);
			printf("\n");
			break;
		}
	if(!flag) printf("-1\n");
	return 0;
}

