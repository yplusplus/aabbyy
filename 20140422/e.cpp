#include <bits/stdc++.h>
using namespace std;

char s[][35] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
int maps[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};

long long dp[25][30];

void init()
{
	for(int i = 0; i < 26; i ++) dp[0][i] = 1;
	for(int i = 1; i <= 20; i ++) {
		for(int j = 0; j < 26; j ++) {
			int x = maps[j];
			char str[35];
			strcpy(str,s[x]);
			for(int k = 0; str[k]; k ++) {
				dp[i][j] += dp[i - 1][str[k] - 'a'];
			}
		}
	}
}

void dfs(int dep,int kth,int cr)
{
	if(!dep) {
		char ans = cr + 'A';
		cout << ans << endl;
		return;
	}
	int x = maps[cr];
	char str[35];
	strcpy(str,s[x]);
	for(int k = 0; str[k]; k ++) {
		if(dp[dep - 1][str[k] - 'a'] >= kth) {
			dfs(dep - 1,kth,str[k] - 'a');
			return;
		}
		else kth -= dp[dep - 1][str[k] - 'a'];
	}
}

int main()
{
	init();
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		char s[110];
		cin >> s;
		int dep,kth;
		cin >> dep >> kth;
		printf("Case %d: ",cas);
		for(int i = 0; s[i]; i ++) {
			int x = s[i] - 'A';
			if(dp[dep][x] >= kth) {
				dfs(dep,kth,x);
				break;
			}
			else kth -= dp[dep][x];
		}
	}
	return 0;
}
