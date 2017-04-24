#include <bits/stdc++.h>
#include <map>
using namespace std;

map<int,int> ma;
int main()
{
	int a[10010];
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++) 
		scanf("%d",&a[i]);
	bool flag = true;
	for(int i = 1; i <= n; i ++) {
		if(a[i] != 1) {
			flag = false;
		}
	}
	if(flag) {
		printf("0\n");
		return 0;
	}
	for(int i = 1; i <= n; i ++) {
		for(int j = 2; j * j <= a[i]; j ++) {
			if(a[i] % j) continue;
			while(a[i] % j == 0) a[i] /= j;
			ma[j] ++;
		}
		if(a[i] > 1) ma[a[i]] ++;
	}
	int ans = 1;
	for(map<int,int>::iterator it = ma.begin(); it != ma.end(); it ++)
		ans = max(ans,it->second);
	if(ans > 2) printf("infinity\n");
	else printf("%d\n",ans);
}
