#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int st[210],ed[210];
int main()
{
	int n,m,r;
	char s[210];
	scanf("%d%d%d",&n,&m,&r);
	scanf("%s",s + 1);
	int len = strlen(s + 1);
	int pos = 0;
	int cc = 0;
	for(int i = 1; i <= n; i ++) {
		if((n - i + 1) * m > len - pos) {
			printf("No solution\n");
			return 0;
		}
		if((n - i + 1) * r < len - pos) {
			printf("No solution\n");
			return 0;
		}
		int x = min(r,len - pos - (n - i) * m);
		st[++ cc] = pos + 1;
		ed[cc] = pos + x;
		pos += x;
	}
	for(int i = 1; i <= cc; i ++) {
		for(int j = st[i]; j <= ed[i]; j ++)
			printf("%c",s[j]);
		printf("\n");
	}
	return 0;
}
		

