#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

struct trie
{
    int id;
    trie *next[26];
}*root,e[15010 * 15];

int cnt = 0;
queue<int> q[15010];
int cc = 0;
void insert(char *s)
{
    trie *p = root;
    for(int i = 0; s[i]; i ++) {
        int idx = s[i] - 'a';
        if(!p->next[idx]) {
            p->next[idx] = &e[cnt ++];
            p->next[idx]->id = 0;
        }
        p = p->next[idx];
    }
    p->id = ++ cc;
}

struct point
{
    char s[18];
    int val;
    friend bool operator < (const point &p,const point &q) {
        if(p.val != q.val) return p.val > q.val;
        return strcmp(p.s,q.s) < 0;
    }
    void read() {
        scanf("%s%d",s,&val);
    }
}a[100010];

int c[15010];

void query(char *s,int id)
{
    trie *p = root;
    for(int i = 0; s[i]; i ++) {
        int idx = s[i] - 'a';
        if(!p->next[idx]) return;
        p = p->next[idx];
        if(p->id && c[p->id] < 10) {
            c[p->id] ++;
            q[p->id].push(id);
        }
    }
}

int getid(char *s)
{
    trie *p = root;
    for(int i = 0; s[i]; i ++) {
        int idx = s[i] - 'a';
        p = p->next[idx];
    }
    return p->id;
}

char s[15010][25];
int main()
{
    root = &e[cnt ++];
    root->id = 0;
    int n,m;
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++) a[i].read();
    sort(a + 1,a + n + 1);
    scanf("%d",&m);
    for(int i = 1; i <= m; i ++) {
        scanf("%s",s[i]);
        insert(s[i]);
    }
    for(int i = 1; i <= n; i ++) {
        query(a[i].s,i);
    }
    int ans[15];
    for(int i = 1; i <= m; i ++) {
        int id = getid(s[i]);
        int ct = 0;
        while(!q[id].empty()) {
            ans[ct ++] = q[id].front();
            q[id].pop();
            printf("%s\n",a[ans[ct - 1]].s);
        }
        for(int j = 0; j < ct; j ++)
            q[id].push(ans[j]);
        if(i < m) printf("\n");
    }
    return 0;
}

