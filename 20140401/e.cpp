#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
char s[N];
int main()
{
	freopen("energy.in","r",stdin);
	freopen("energy.out","w",stdout);
	int n;
	while(scanf("%d",&n) != EOF) {
		long long ans = 0;
		scanf("%s",s);
		int x = 0,y = 0;
		for(int i = 0; s[i]; i ++) {
			if(s[i] == '1') {
				if(x * 2 + y < n) y ++;
				else if(x) x --,y ++;
			}
			else if(s[i] == '2') {
				if(x * 2 + y + 2 <= n) x ++;
			}
			ans += x + y;
		}
		cout << ans << endl;
	}
	return 0;
}
