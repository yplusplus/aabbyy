#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
struct trie
{
    trie *next[2];
}*root,e[3000010];
 
int cnt = 0;
 
void init()
{
    for(int i = 0; i < cnt; i ++)
        e[i].next[0] = e[i].next[1] = NULL;
    cnt = 0;
    root = &e[cnt ++];
}
 
void insert(int x)
{
    trie *p = root;
    for(int i = 29; i >= 0; i --) {
        int idx = ((x & (1 << i)) != 0);
        if(!p->next[idx]) p->next[idx] = &e[cnt ++];
        p = p->next[idx];
    }
}
 
int query(int &x)
{
    int ans = 0;
    trie *p = root;
    for(int i = 29; i >= 0; i --) {
        int idx = (x & (1 << i)) != 0;
        if(!p->next[1 - idx]) {
            p = p->next[idx];
        }
        else {
            ans ^= (1 << i);
            p = p->next[1 - idx];
        }
    }
    return ans;
}
 
int main()
{
    int n,m,x;
    while(scanf("%d%d",&n,&m) != EOF) {
        init();
        int ans = 0;
        while(n --) {
            scanf("%d",&x);
            if(ans > m) continue;
            if(cnt != 1) ans = max(ans,query(x));
            insert(x);
        }
        if(ans > m) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

