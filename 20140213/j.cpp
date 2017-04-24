#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
char s[N];

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%s",s + 1);
		int n = strlen(s + 1);
		int ans = 0;
		for(int i = 1; i <= n; i ++) {
			int mask = 0;
			for(int j = i; j <= n; j ++) {
				mask ^= (1 << (s[j] - 'a'));
				if(mask == 0 || (mask == (mask & (-mask)))) ans ++;
			}
		}
		printf("Case %d: %d\n",cas,ans);
	}
	return 0;
}
