#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
map<int,int> ma;
int a[N];

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) {
		ma.clear();
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&a[i]);
			ma[a[i] - (i - 1)] ++;
		}
		int idx = -1,maxn = -1;
		for(map<int,int>::iterator it = ma.begin(); it != ma.end(); it ++)
			if(it->second > maxn) {
				maxn = it->second;
				idx = it->first;
			}
		printf("%d\n",n - maxn);
		for(int i = 0; i < n; i ++) {
			printf("%d",idx + i);
			if(i == n - 1) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}

