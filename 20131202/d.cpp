#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
struct edge
{
    int v,next;
}e[N * 210];

bool dp[N][N];
int cnt,head[N];
void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

int main()
{
    int n,m,x,y;
    while(scanf("%d%d",&n,&m) != EOF) {
        cnt = 0;
        memset(head,-1,sizeof(head));
        memset(dp,false,sizeof(dp));        
        while(m --) {
            scanf("%d%d",&x,&y);
            addedge(y,x);
            if(x == 1) dp[1][y] = true;
        }
        int ans = 0;
        for(int k = 1; k <= n; k ++) {
            for(int i = head[k]; i != -1; i = e[i].next) {
                for(int j = e[i].v + 1; j < k; j ++)
                    if(dp[e[i].v][j]) dp[j][k] = true;
            }
            for(int i = head[k]; i != -1; i = e[i].next)
                for(int j = 1; j < e[i].v; j ++)
                    if(dp[j][e[i].v]) dp[j][k] = true;
        }
        for(int i = 1; i <= n; i ++)
            for(int j = i + 1; j <= n; j ++)
                if(dp[i][j]) ans ++;
        cout << ans << endl;
    }
    return 0;
}
/*
6 6
1 2
1 3
1 4
2 5
2 6
3 6

8 11
1 2
1 3
1 4
2 5
3 4
6 7
3 6
3 7
4 8
2 6
5 6
*/

