#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int sg[510];

int dfs(int u)
{
    if(sg[u] != -1) return sg[u];
    int visit[1100];
    memset(visit,0,sizeof(visit));
    for(int i = 2; i <= u; i ++)
        visit[dfs(i - 2) ^ dfs(u - i)] = 1;
    for(int i = 0; ; i ++)
        if(!visit[i]) return sg[u] = i;
}

int main()
{
    memset(sg,-1,sizeof(sg));
    sg[1] = 0;
    sg[2] = 1;
    sg[0] = 0;
    for(int i = 3; i <= 500; i ++)
        dfs(i);
    int a[] = {15,17,22,35,51};
    
    for(int i = 1; i <= 500; i ++) {
        //printf("%d : %d\n",i,sg[i]);
        //if(i % 10 == 0) printf("\n");
        //if(i > 34 && sg[i] != sg[i - 34]) printf("fuck : %d\n",i - 34);
    }
    int t,n,x;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        int ans = 0;
        while(n --) {
            scanf("%d",&x);
            while(!x) printf("fuck\n");
            if(x <= 68) ans ^= sg[x];
            else {
                x %= 68;
                x += 68;;
                ans ^= sg[x];
            }
        }
        if(ans) printf("Carol\n");
        else printf("Dave\n");
    }
    return 0;
}

