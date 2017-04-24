#include <bits/stdc++.h>
using namespace std;

int dir[4][2] = {0,1,0,-1,1,0,-1,0};
const int N = 1010;
char s[N][N];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i] + 1);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++) {
				bool flag = false;
				if(s[i][j] != '+') continue;
				for(int k = 0; k < 4; k ++) {
					int tx = i + dir[k][0];
					int ty = j + dir[k][1];
					if(s[tx][ty] == '-' && tx >= 1 && tx <= n && ty >= 1 && ty <= m) flag = true;
				}
				if(flag) ans ++;
			}

		printf("%d\n",ans);
	}
	return 0;
}
