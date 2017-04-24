#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct trie
{
	trie *next[26];
	int id;
	trie() {
		id = 0;
		for(int i = 0; i < 26; i ++) next[i] = 0;
	}
}e[6 * N];

int cnt = 0;

void init()
{
	for(int i = 0; i < cnt; i ++) {
		e[i].id = 0;
		for(int j = 0; j < 26; j ++)
			e[i].next[j] = NULL;
	}
	cnt = 0;
}

struct Trie
{
	trie *root;
	void init() {
		root = &e[cnt ++];
	}

	void insert(char *s,int id) {
		trie *p = root;
		for(int i = 0; s[i]; i ++) {
			int idx = s[i] - 'a';
			if(!p->next[idx]) p->next[idx] = &e[cnt ++];
			p = p->next[idx];
		}
		p->id = id;
	}

	int query(char *s,int x,int y) {
		trie *p = root;
		for(int i = x; i < x + y; i ++) {
			int idx = s[i] - 'a';
			if(!p->next[idx]) return 0;
			p = p->next[idx];
		}
		return p->id;
	}
}T[2];

int ans[N];
char s[N],str[N][10];
int pre[N];
int f[N];
int main()
{
	int n,flag;
	int cas = 0;
	while(scanf("%s",s) != EOF) {
		memset(ans,0,sizeof(ans));
		memset(pre,-1,sizeof(pre));
		init();
		T[0].init();
		T[1].init();
		scanf("%d",&n);
		for(int i = 1; i <= n; i ++) {
			scanf("%d%s",&flag,str[i]);
			T[flag].insert(str[i],i);
			f[i] = flag;
		}
		int len = strlen(s);
		for(int i = 0; i < len; i ++) {
			for(int j = 1; j <= 6 && i + j <= len; j ++) {
				flag = T[0].query(s,i,j);
				if(flag) ans[flag] ++;
				flag = T[1].query(s,i,j);
				if(flag) {
					if(i >= pre[flag]) {
						ans[flag] ++;
						pre[flag] = i + j;
					}
				}
			}
		}
		printf("Case %d\n",++ cas);
		for(int i = 1; i <= n; i ++) {
			flag = f[i];
			len = strlen(str[i]);
			int id = T[flag].query(str[i],0,len);
			printf("%d\n",ans[id]);
		}
		printf("\n");
	}
	return 0;
}
