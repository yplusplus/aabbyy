#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int sg[35][35][35];

int dfs(int x,int y,int z)
{
	if(sg[x][y][z] != -1) return sg[x][y][z];
	bool visit[300];
	memset(visit,0,sizeof(visit));
	if(x < 1 || y < 1 || z < 1) return sg[x][y][z] = 0;
	for(int i = 1; i <= x; i ++) {
		for(int j = 1; j <= y; j ++) {
			for(int k = 1; k <= z; k ++) {
				int tmp = dfs(x - i,y,z) ^ dfs(x,y - j,z) ^ dfs(x,y,z - k);
				tmp = tmp ^ dfs(x - i,y - j,z) ^ dfs(x - i,y,z - k);
				tmp = tmp ^ dfs(x,y - j,z - k) ^ dfs(x - i,y - j,z - k);
				if(tmp < 300) visit[tmp] = true;		
			}
		}
	}
	for(int i = 0; ; i ++)
		if(!visit[i]) return sg[x][y][z] = i;
}

int main()
{
	memset(sg,-1,sizeof(sg));
	int maxn = 0;
	/*
	for(int i = 1; i < 32; i ++)
		for(int k = 1; k < 32; k ++)
			for(int j = 1; j < 32; j ++)
				maxn = max(maxn,dfs(i,j,k));*/
	int t,n,m,x,y,z;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		int ans = 0;
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			ans ^= dfs(x,y,z);
		}
		if(ans) printf("DD\n");
		else printf("Lanrete\n");
	}
	return 0;
}
