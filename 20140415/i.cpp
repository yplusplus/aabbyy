#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
struct trie
{
    bool flag;
    int id;
    trie *fail,*next[26];
    trie() {
        fail = NULL;
        for(int i = 0; i < 26; i ++) next[i] = NULL;
        flag = false;
    }
}*root,e[N],*q[N];

int cnt,m;
void init(int n)
{
    e[n].id = n;
    e[n].flag = false;
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
        assert(idx >= 0 && idx < m);
        if(!p->next[idx]) {
            init(cnt);
            p->next[idx] = &e[cnt ++];
        }
        p = p->next[idx];
    }
    p->flag = true;
}

void build_ac_automation(int m)
{
	root->fail = root;
	q[0] = root;
	int top = 0,tail = 1;
	while(top < tail) {
		trie *p = q[top ++];
		p->flag |= p->fail->flag;
		for(int i = 0; i < m; i ++) {
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

int low[N],dfn[N],instack[N],bel[N],L[N];
int c,cc,loops,sz[N],C[N];
stack<int> sta;
void init()
{
    memset(L,0,sizeof(L));
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(instack,0,sizeof(instack));
    memset(sz,0,sizeof(sz));
    memset(C,0,sizeof(C));
    loops = 0;
    c = cc = 0;
    while(!sta.empty()) sta.pop();
}

void tarjan(int u)
{   
    dfn[u] = low[u] = ++ cc;
    instack[u] = 1;
    sta.push(u);
    for(int i = 0; i < m; i ++) {
        if(e[u].next[i]->flag) continue;
        int v = e[u].next[i]->id;
        if(v == u) {
            L[u] ++;
            if(L[u] > 1) loops = 1000000000;
            continue;
        }
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v] && dfn[v] < low[u]) low[u] = dfn[v];
    }
    if(low[u] == dfn[u]) {
	    c ++;
        int v;
        do {
	       sz[c] ++;
           v = sta.top();
	       sta.pop();
           bel[v] = c;
	       instack[v] = 0;
	    }while(u != v);
        if(sz[c] > 1) loops ++;
    }
}

bool check(char *s)
{
    for(int i = 0; s[i]; i ++)
        if(s[i] - 'a' >= m) return false;
    return true;
}

void solve()
{
    int n;
    scanf("%d%d",&n,&m);
    char s[100010];
    init(0);
    cnt = 0;
    root = &e[cnt ++];
    while(n --) {
        scanf("%s",s);
        if(!check(s)) continue;
        insert(s);
    }
    build_ac_automation(m);
    init();
    tarjan(0);
    if(loops == 0) {
        printf("No\n");
        return;
    }
    if(loops >= 1000000000) {
        puts("Yes");
        return;
    }
    
    for(int i = 0; i < cnt; i ++)
        for(int j = 0; j < m; j ++)
            if(e[i].next[j]->flag == false && bel[i] == bel[e[i].next[j]->id])
                C[bel[e[i].next[j]->id]] ++;
    for(int i = 1; i <= c; i ++)
        if(sz[i] > 1 && C[i] > sz[i]) {
            puts("Yes");
            return;
        }
    puts("No");
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) solve();
    return 0;
}


