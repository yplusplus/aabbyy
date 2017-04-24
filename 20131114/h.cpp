#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
char s[N],str[N];
char tmp[N];
int main()
{
	scanf("%s",s);
	scanf("%s",str);
	int n = strlen(s);
	int m = strlen(str);
	int visit[26];
	memset(visit,0,sizeof(visit));
	for(int i = 0; i < m; i ++) visit[str[i] - 'a'] ++;
	for(int i = 25; i >= 0; i --) {
		int pos = n;
		int tot = 0;
		if(!visit[i]) continue;
		if(!n) {
			visit[i] %= 2;
			if(visit[i]) s[n ++] = i + 'a';
			continue;
		}
		for(int j = 0; j < n; j ++) {
			if(s[j] - 'a' < i) continue;
			if(s[j] - 'a' == i) tot ++;
			else {
				pos = j;
				break;
			}
		}
		if(pos == n) {
			int ct = 0;
			for(int j = 0; j < n; j ++) {
				if(s[j] - 'a' == i) {
					if(visit[i]) {
						visit[i] --;
						continue;
					}
					else tmp[ct ++] = s[j];
				}
				else tmp[ct ++] = s[j];
			}
			visit[i] %= 2;
			while(visit[i] --) tmp[ct ++] = i + 'a';
			n = ct;
		}
		else {
			while(pos >= 1 && s[pos - 1] - 'a' >= i) pos --;
			int ct = 0;
			for(int j = 0; j < pos; j ++) {
				if(s[j] - 'a' == i) {
					if(visit[i]) {
						visit[i] --;
						continue;
					}
					else tmp[ct ++] = s[j];
				}
				else tmp[ct ++] = s[j];
			}
			while(visit[i] --) tmp[ct ++] = i + 'a';
			for(int j = pos; j < n; j ++)
				tmp[ct ++] = s[j];
			n = ct;
		}
		for(int j = 0; j < n; j ++)
			s[j] = tmp[j];
	}
	for(int i = 0; i < n; i ++)
		printf("%c",s[i]);
	printf("\n");
	return 0;
}


