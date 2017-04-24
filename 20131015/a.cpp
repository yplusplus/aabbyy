#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int sg[55][55];

int dfs(int n,int m)
{
	if(n == 1 && m == 1) return 0;
	if(sg[n][m] != -1) return sg[n][m];
	int visit[55 * 55];
	memset(visit,0,sizeof(visit));
	for(int i = 1; i < n; i ++)
		visit[dfs(i,m) ^ dfs(n - i,m)] = 1;
	for(int i = 1; i < m; i ++)
		visit[dfs(n,i) ^ dfs(n,m - i)] = 1;
	for(int i = 0;; i ++)
		if(!visit[i]) return sg[n][m] = i;
}

int main()
{
	memset(sg,-1,sizeof(sg));
	int n,m;
	cin >> n >> m;
	if(dfs(n,m)) cout << "[:=[first]" << endl;
	else cout << "[second]=:]" << endl;
	return 0;
}

