#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

struct point
{
	char s[55];
	friend bool operator < (const point &p,const point &q) {
		return strcmp(p.s,q.s) < 0;
	}
}a[10010];

int main() {
	int n;
	while(scanf("%d",&n) != EOF) {
		for(int i = 0; i < n; i ++)
			scanf("%s",a[i].s);
		sort(a,a + n);
		int ans = 2 * strlen(a[0].s);
		int mlen = strlen(a[0].s);
		for(int i = 1; i < n; i ++) {
			int pre = 0;
			for(int j = 0; a[i - 1].s[j] && a[i].s[j]; j ++) {
				if(a[i - 1].s[j] == a[i].s[j]) pre ++;
				else break;
			}
			ans += 2 * (strlen(a[i].s) - pre);
			mlen = max(mlen,(int)strlen(a[i].s));
		}
		printf("%d\n",n + ans - mlen);
	}
	return 0;
}