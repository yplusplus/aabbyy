#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 200010;
int a[N],c[N];

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
		int i = 1,ans = 0,cnt = 0;
		while(i <= n) {
			int j = i;
			while(j <= n && a[j] == a[i]) j ++;
			ans += (j - i - 1);
			if(j - i - 1) c[++ cnt] = j - i - 1;
			if(j - i - 1 > n - (j - i)) {
				ans = -1;
				break;
			}
			i = j;
		}
		if(ans == -1) {
			printf("-1\n");
			continue;
		}
		int sum = *max_element(c + 1,c + cnt + 1);
		sum = ans - sum;
		if(*max_element(c + 1,c + cnt + 1) > sum) {
			printf("%d\n",*max_element(c + 1,c + cnt + 1));
		}
		else printf("%d\n",(ans + 1) / 2);
	}
	return 0;
}

