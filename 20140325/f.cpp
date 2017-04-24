#include <bits/stdc++.h>
using namespace std;

int main()
{
	char s[10010];
	int n;
	gets(s);
	sscanf(s,"%d",&n);
	while(n --) {
		gets(s);
		int visit[26];
		memset(visit,0,sizeof(visit));
		for(int i = 0; s[i]; i ++)
			if(s[i] >= 'A' && s[i] <= 'Z') {
				visit[s[i] - 'A'] ++;
			}
		int maxn = 0,id = -1,cnt = 10;
		for(int i = 0; i < 26; i ++)
			if(visit[i] > maxn) {
				cnt = 1;
				id = i;
				maxn = visit[i];
			}
			else if(visit[i] == maxn) {
				cnt ++;
			}
		if(cnt > 1) {
			printf("NOT POSSIBLE\n");
		}
		else {
			id = 4 - id;
			if(id < 0) id += 26;
			printf("%d ",(26 - id) % 26);
			for(int i = 0; s[i]; i ++)
				if(s[i] >= 'A' && s[i] <= 'Z') {
					char x = (s[i] - 'A' + id) % 26 + 'A';
					printf("%c",x);
				}
				else printf("%c",s[i]);
			printf("\n");
		}
	}
	return 0;
}

