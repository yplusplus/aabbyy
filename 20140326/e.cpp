#include <bits/stdc++.h>
using namespace std;

char s[110][45],ss[110][45];
void solve()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < n; i ++) {
		scanf("%s",s[i]);
		strcpy(ss[i],s[i]);
		int len = strlen(s[i]);
		if(len > 2) sort(s[i] + 1,s[i] + len - 1);
	}
	gets(s[n]);
	while(m --) {
		char c;
		char str[55];
		while(1) {
			c = getchar();
			if(c >= 'a' && c <= 'z') {
				cin.putback(c);
				scanf("%s",str);
				bool flag = false;
				int len = strlen(str);
				if(len > 2) sort(str + 1,str + len - 1);
				for(int i = 0; i < n; i ++)
					if(strcmp(s[i],str) == 0) {
						printf("%s",ss[i]);
						flag = true;
						break;
					}
			}
			else {
				printf("%c",c);
				if(c == '\n') break;
			}
		}
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case #%d:\n",cas);
		solve();
	}
	return 0;
}
