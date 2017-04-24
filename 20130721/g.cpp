#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 1000000000;
const int N = 100010;

struct trie
{
	int mix;
	trie *fail,*next[26];
	trie() {
		fail = NULL;
		for(int i = 0; i < 26; i ++) next[i] = NULL;
		mix = oo;
	}
}*root,e[N],*q[N];

int cnt = 0;

void init(int n)
{
	e[n].mix = oo;
	e[n].fail = NULL;
	for(int i = 0; i < 26; i ++) e[n].next[i] = NULL;
}

int change(char c)
{
	return c - 'a';
}

void insert(char *s)
{
	trie *p = root;
	int i = 0,idx;
	while(s[i]) {
		idx = change(s[i ++]);
		if(!p->next[idx]) {
			init(cnt);
			p->next[idx] = &e[cnt ++];
		}
		p = p->next[idx];
	}
	p->mix = i;
}

void build_ac_automation()
{
	root->fail = root;
	q[0] = root;
	int top = 0,tail = 1;
	while(top < tail) {
		trie *p = q[top ++];
		p->mix = min(p->mix,p->fail->mix);
		for(int i = 0; i < 26; i ++) {
			if(!p->next[i]) {
				if(p == root) p->next[i] = root;
				else p->next[i] = p->fail->next[i];
			}
			else {
				if(p == root) p->next[i]->fail = root;
				else p->next[i]->fail = p->fail->next[i];
				q[tail ++] = p->next[i];
			}
		}
	}
}

char s[N * 10],str[N];

int main()
{
	int t,n;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%s",s + 1);
		init(0);
		cnt = 0;
		root = &e[cnt ++];
		scanf("%d",&n);
		while(n --) {
			scanf("%s",str);
			insert(str);
		}
		build_ac_automation();
		trie *p = root;
		long long ans = 0;
		int last = 0;
		for(int i = 1; s[i]; i ++) {
			p = p->next[change(s[i])];
			if(p->mix == oo) {
				ans += i - last;
			}
			else {
				last = max(last,i - p->mix + 1);
				ans += i - last;
			}
		//	printf("%d : %d\n",last,i);
		}
		printf("Case #%d: %lld\n",cas,ans);
	}
	return 0;
}


