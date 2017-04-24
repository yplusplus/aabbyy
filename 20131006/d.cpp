#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	char s[25],str[25];
	int t;
	scanf("%d",&t);
	while(t --) {
		scanf("%s",s);
		bool flag = true;
		for(int i = 0; s[i]; i ++) {
			for(int j = i; s[j]; j ++) {
				int ct = 0;
				for(int k = i; k <= j; k ++)
					str[ct ++] = s[k];
				str[ct] = 0;
				reverse(str,str + ct);
				if(!strstr(s,str)) flag = false;
			}
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

