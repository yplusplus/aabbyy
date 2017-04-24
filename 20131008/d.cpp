#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
using namespace std;
int n;
map<int,long long> ma[2];

int get(int r)
{
	if(r == 0) return 2 * n - 1;
	if(r <= n) return 2 * n - 1 + 2 * r;
	int maxn = 2 * n - 1 + 2 * n;
	return maxn - (r - n - 1) * 2;
}

void dfs(int st1,int st2,int c,long long sum,int row)
{
	if(c >= get(row)) {
		if(st1 == (1 << get(row)) - 1) {
			ma[row & 1][st2] += sum;
		}
		return;
	}
	if(st1 & (1 << c)) {
		dfs(st1,st2,c + 1,sum,row);
		return;
	}
	int tot = get(row);
	if(c + 1 < tot) {
		if(!(st1 & (1 << c)) && !(st1 & (1 << (c + 1))))
			dfs(st1 | (1 << c) | (1 << (c + 1)),st2,c + 2,sum,row);
	}
	if(row == n) {
		if(!(c & 1))
			dfs(st1 | (1 << c),st2 | (1 << c),c + 1,sum,row);
		return;
	}
	if(row <= n) {
		if(!(c & 1))
			dfs(st1 | (1 << c),st2 | (1 << (c + 1)),c + 1,sum,row);
	}
	else {
		if(c & 1) {
			dfs(st1 | (1 << c),st2 | (1 << (c - 1)),c + 1,sum,row);
		}
	}
}

int main()
{
	long long ans[10];
	memset(ans,0,sizeof(ans));
	for(int k = 1; k <= 7; k ++) {
		n = k;
		ma[0].clear();
		ma[0][0] = 1;
		for(int i = 1; i <= 2 * n; i ++) {
			ma[i & 1].clear();
			for(map<int,long long>::iterator it = ma[(i & 1) ^ 1].begin(); it != ma[(i & 1) ^ 1].end(); it ++) {
				dfs(it->first,0,0,it->second,i);
			}
		}
		for(map<int,long long>::iterator it = ma[0].begin(); it != ma[0].end(); it ++) {
			if(it->first == 0) {
				ans[k] = it->second;
				break;
			}
		}
	}
	bool flag = false;
	while(scanf("%d",&n) != EOF) {
		if(flag) printf("\n");
		flag = true;
		printf("%lld\n",ans[n]);
	}
	return 0;
}

