#pragma comment(linker,"/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int visit[1 << 21];
int n;
int a[1 << 22];
bool flag;
void dfs(int pos,int x,int tot)
{
	if(flag) return;
	if(tot == (1 << n)) {
		flag = true;
		for(int i = 0; i < pos; i ++)
			printf("%d",a[i]);
		printf("\n");
		return;
	}
	if(!visit[(x << 1) | 1]) {
		visit[(x << 1) | 1] = 1;
		a[pos] = 1;
		dfs(pos + 1,((x << 1) | 1) & ((1 << (n - 1)) - 1),tot + 1);
		visit[(x << 1) | 1] = 0;
	}
	if(!visit[x << 1]) {
		visit[x << 1] = 1;
		a[pos] = 0;
		dfs(pos + 1,(x << 1) & ((1 << (n - 1)) - 1),tot + 1);
		visit[x << 1] = 0;
	}
}

int main()
{
	scanf("%d",&n);
	if(n == 1) {
		printf("10\n");
		return 0;
	}
	memset(visit,0,sizeof(visit));
	for(int i = 0; i < n; i ++) {
		a[i] = 1;
	}
	for(int i = 0; i < n; i ++)
		a[i + n] = 0;
	for(int i = n - 1; i < 2 * n; i ++) {
		int ans = 0;
		for(int j = 0; j < n; j ++) {
			if(a[i - j]) ans += (1 << j);
		}
		visit[ans] = 1;
	}
	flag = false;
	dfs(2 * n,0,n + 1);
	return 0;
}
