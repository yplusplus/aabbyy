#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int visit[10000010];
char s[1000020];

int main()
{
	memset(visit,0,sizeof(visit));
	scanf("%s",s);
	int n = strlen(s);
	for(int i = 0; i < n; i ++) {
		int x = 0;
		for(int j = 0; i + j < n && j < 7; j ++) {
			x = 10 * x + (s[i + j] - '0');
		//	cout << i << " " << j << " " << n << " " << x << endl;
			visit[x] = 1;
		}
	}
	for(int i = 1; ; i ++)
		if(!visit[i]) {
			printf("%d\n",i);
			return 0;
		}
	return 0;
}
