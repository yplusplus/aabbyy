#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int a[100010];

void dfs(int step)
{
	if(step == n) {
		for(int i = 0; i < n; i ++)
			printf("%c",'a' + a[i]);
		printf("\n");
		return;
	}
	for(int i = 0; i < 3; i ++)
		if(i != a[step - 1] && i != a[step - 2]) {
			a[step] = i;
			dfs(step + 1);
		}
}

int main()
{
	scanf("%d",&n);
	if(n == 1) {
		printf("a\n");
		printf("b\n");
		printf("c\n");
		return 0;
	}
	if(6 * n > 100000) {
		printf("TOO LONG\n");
		return 0;
	}
	for(int i = 0; i < 3; i ++)
		for(int j = 0; j < 3; j ++)
			if(i == j) continue;
			else {
				a[0] = i,a[1] = j;
				dfs(2);
			}

	return 0;
}

