#include <bits/stdc++.h>
using namespace std;

int get_id(char c)
{
	if(c >= '6' && c <= '9') return c - '6';
	if(c == 'T') return 4;
	if(c == 'J') return 5;
	if(c == 'Q') return 6;
	if(c == 'K') return 7;
	return 8;
}

bool cmp(char *s,char *str,char c)
{
	if(str[1] == c) {
		if(s[1] != c) return true;
		return get_id(s[0]) < get_id(str[0]);
	}
	else {
		if(s[1] != str[1]) return false;
		return get_id(s[0]) < get_id(str[0]);
	}
}

int main()
{
	char s[45][10],str[45][10];
	char ss[10];
	int n;
	while(scanf("%d",&n) != EOF) {
		scanf("%s",ss);
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i]);
		int number = 0;
		bool cover = false;
		for(int i = 1; i <= n; i ++)
			scanf("%s",str[i]);
		for(int i = 1; i <= n; i ++)
			if(s[i][2] == '*') number = get_id(s[i][0]);
		for(int state = 0; state < (1 << 9); state ++) {
			if(!(state & (1 << number))) continue;
			bool flag = false;
			bool visit[10];
			bool used1[45],used2[45];
			memset(used1,0,sizeof(used1));
			memset(visit,0,sizeof(visit));
			memset(used2,0,sizeof(used2));
			visit[number] = 1;
			while(1) {
				int id = -1;
				for(int i = 1; i <= n; i ++) {
					if(used1[i]) continue;
					if(!visit[get_id(s[i][0])]) continue;
					id = i;
					break;
				}
				if(id == -1) break;
				used1[id] = true;
				char find[10];
				int id2 = -1;
				find[0] = 0;
				for(int i = 1; i <= n; i ++) {
					if(used2[i]) continue;
					if(!(state & (1 << get_id(str[i][0])))) continue;
					if(cmp(s[id],str[i],ss[0])) {
						if(find[0] == 0 || cmp(str[i],find,ss[0])) {
							id2 = i;
							strcpy(find,str[i]);
						}
					}
				}
				if(id2 == -1) {
					flag = true;
					break;
				}
				else used2[id2] = true,visit[get_id(str[id2][0])] = true;
			}
			if(!flag) {
				cover = true;
				break;
			}
		}
		if(!cover) puts("TAKE");
		else puts("COVER");
		puts("");
	}
	return 0;
}
