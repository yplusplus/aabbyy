#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
char s[N];
map<int,int> ma;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int tot = 0,x = -1,y = -1;
	int n;
	scanf("%d",&n);
	scanf("%s",s + 1);
	for(int i = 1; i <= n; i ++)
		if(s[i] == '*') tot ++;
	int sum = 0;
	int ans = tot;
	ma[0] = 0;
	for(int i = 1; i <= n; i ++) {
		if(s[i] == '*') sum ++;
		else sum --;
		int maxn = sum - (ma.begin())->first;
		//if(i == 9) cout << maxn << " " << sum << " " << ma.begin()->first << " " << tot << endl;
		if(tot + 2 - maxn < ans) {
			ans = tot + 2 - maxn;
			y = i;
			x = ma.begin()->second + 1;
		}
		if(!ma.count(sum)) ma[sum] = i;
	}
	
	if(x == -1) {
		printf("%d\n",tot);
		bool flag = false;
		for(int  i = 1; i <= n; i ++) {
			if(s[i] == '*') {
				if(flag) printf("Ctrl+%d\n",i);
				else printf("%d\n",i);
				flag = true;
			}
		}
	}
	else {
		printf("%d\n",ans);
		printf("%d\n",x);
		printf("Shift+%d\n",y);
		for(int i = x; i <= y; i ++)
			if(s[i] == '*') s[i] = '.';
			else s[i] = '*';
		for(int i = 1; i <= n; i ++)
			if(s[i] == '*') printf("Ctrl+%d\n",i);
	}
	return 0;
}
