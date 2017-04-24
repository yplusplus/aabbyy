#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
int sg[N][N];
int n,m;
int times = 0;
int dfs(int u)
{
	if(u < m) return 0;
	if(sg[m][u] != -1) return sg[m][u];
	int visit[1010];
	memset(visit,0,sizeof(visit));
	for(int i = 0; i + m <= u; i ++)
		visit[dfs(i) ^ dfs(u - m - i)] = 1;
	for(int i = 0;; i ++)
		if(!visit[i]) return sg[m][u] = i;
}

int main()
{
//	memset(visit,-1,sizeof(Visit));
	memset(sg,-1,sizeof(sg));
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		printf("Case #%d: ",cas);
		if(n < m) {
			printf("abcdxyzk\n");
			continue;
		}
		++ times;
		if(dfs(n - m)) printf("abcdxyzk\n");
		else printf("aekdycoin\n");
	}
	return 0;
}

