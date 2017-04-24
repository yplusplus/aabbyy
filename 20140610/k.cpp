#include <bits/stdc++.h>
using namespace std;

const long long oo = 1LL << 60;
const int N = 210;
long long dp[25][N][N];
int id[N][N];
char s[N][N];
map<string,int> ma;
int edges[N][N];
int rev[N * 25];
int L[N];

int main()
{
	int cas = 0;
	int n;
	while(scanf("%s",s[0]) != EOF) {
	    if(s[0][0] == '.') break;
	    scanf("%s",s[1]);
	    scanf("%d",&n);
		ma.clear();
		memset(edges,0,sizeof(edges));
		for(int i = 1; i <= n; i ++) {
			scanf("%s%s",s[2 * i],s[2 * i + 1]);
		}
		int cc = 0;
		for(int i = 0; i <= 2 * n + 1; i ++)
			if(!ma.count(s[i])) ma[s[i]] = ++ cc;
		for(int i = 0; i <= 2 * n + 1; i ++) {
			char str[25];
			int m = strlen(s[i]);
			for(int j = 0; j < m; j ++) {
				int len = 0;
				for(int k = j; k < m; k ++) {
					str[len ++] = s[i][k];
				}
				str[len] = 0;
				if(!ma.count(str)) ma[str] = ++ cc;
				id[i][j] = ma[str];
			}
			L[i] = strlen(s[i]);
		}
		for(int i = 1; i <= n; i ++)
			edges[ma[s[2 * i]]][ma[s[2 * i + 1]]] = 1;
		int m = strlen(s[0]);
		int pos[25];
		memset(pos,0,sizeof(pos));
		for(map<string,int>::iterator it = ma.begin(); it != ma.end(); it ++) {
			int len = it->first.length();
			++ pos[len];
			rev[it->second] = pos[len];
		}
		for(int i = 0; i <= 20; i ++) {
			for(int j = 0; j < N; j ++) {
				for(int k = 0; k < N; k ++)
					dp[i][j][k] = oo;
				dp[i][j][j] = 0;
			}
		}
		for(int len = 1; len <= m; len ++) {
			for(int i = 0; i <= 2 * n + 1; i ++) {
				if(L[i] < len) continue;
				for(int j = 0; j <= 2 * n + 1; j ++) {
					if(L[j] < len) continue;
					int x = L[i] - len,y = L[j] - len;
					int xx = id[i][x],yy = id[j][y];
					if(xx < N && yy < N && edges[xx][yy])
					    dp[len][rev[xx]][rev[yy]] = min(dp[len][rev[xx]][rev[yy]],1LL);
					xx = rev[xx],yy = rev[yy];
					if(x + 1 < L[i] && y + 1 < L[j] && s[i][x] == s[j][y]) {
						int id1 = id[i][x + 1],id2 = id[j][y + 1];
						id1 = rev[id1];
						id2 = rev[id2];
						dp[len][xx][yy] = min(dp[len][xx][yy],dp[len - 1][id1][id2]);
					}
				}
			}
			for(int k = 1; k <= pos[len]; k ++)
				for(int i = 1; i <= pos[len]; i ++)
					for(int j = 1; j <= pos[len]; j ++)
						dp[len][i][j] = min(dp[len][i][j],dp[len][i][k] + dp[len][k][j]);
		}
		printf("Case %d: ",++ cas);
		int x = rev[ma[s[0]]],y = rev[ma[s[1]]];
		if(dp[m][x][y] == oo) printf("No solution\n");
		else printf("%lld\n",dp[m][x][y]);
	}
	return 0;
}
