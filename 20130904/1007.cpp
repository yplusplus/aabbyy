#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int oo = 1000000000;
int pre[20];
int visit[20];
vector<int> v[20];

int find(int x)
{
    for(int i = 0; i < v[x].size(); i ++) {
        if(!visit[v[x][i]]) {
            visit[v[x][i]] = 1;
            int tmp = pre[v[x][i]];
            pre[v[x][i]] = x;
            if(tmp == -1 || find(tmp)) return 1;
            pre[v[x][i]] = tmp;
        }
    }
    return 0;
}

int dp[25][25][2],cost[25][25][3];// 0 上下，1左右，2混合
int c[25][25];

void get_cost(int m,int &x,int &y,int &z,int p,int q)
{
    x = y = z = 0;
    for(int i = 0; i < 20; i ++) v[i].clear();
    memset(pre,-1,sizeof(pre));
    for(int i = 1; i <= m; i ++) {
        for(int j = 1; j <= m; j ++) {
            scanf("%d",&c[i][j]);
            if(c[i][j]) {
                v[i].push_back(j);
            }
        }
    }
    for(int i = 1; i <= m; i ++) {
        int flag = 0;
        for(int j = 1; j <= m; j ++) {
            if(c[j][i]) flag = 1;
        }
        x += flag;
        flag = 0;
        for(int j = 1; j <= m; j ++) {
            if(c[i][j]) flag = 1;
        }
        y += flag;
    }
    for(int i = 1; i <= m; i ++) {
        memset(visit,0,sizeof(visit));
        z += find(i);
    }
    x *= p,y *= p,z *= p;
    z += q;
}
    
void update(int &x,int y)
{
    x = min(x,y);
}

int main()
{
    int n,m,p,q;
    while(scanf("%d%d%d%d",&n,&m,&p,&q) != EOF) {
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                get_cost(m,cost[i][j][0],cost[i][j][1],cost[i][j][2],p,q);
            }
        }
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++)
                for(int k = 0; k < 2; k ++)
                    dp[i][j][k] = oo;
        /*
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++) {
                cout << i << " " << j << " : " << cost[i][j][0] << " " << cost[i][j][1] << " " << cost[i][j][2] << endl;
            }*/
        dp[1][1][0] = min(cost[1][1][0],cost[1][1][2]);
        dp[1][1][1] = min(cost[1][1][1],cost[1][1][2]);
        // 0 上下，1左右，2混合
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                if(i == n && j == n) continue;
                if(i + 1 <= n) {
                    update(dp[i + 1][j][0],dp[i][j][1] + q + cost[i + 1][j][0]);
                    update(dp[i + 1][j][1],dp[i][j][1] + cost[i + 1][j][1]);
                    update(dp[i + 1][j][0],dp[i][j][1] + cost[i + 1][j][2]);
                    
                    update(dp[i + 1][j][1],dp[i][j][0] + q + cost[i + 1][j][1]);
                    update(dp[i + 1][j][0],dp[i][j][0] + q + q + cost[i + 1][j][0]);
                    update(dp[i + 1][j][0],dp[i][j][0] + q + cost[i + 1][j][2]);
                }
                
                if(j + 1 <= n) {
                    update(dp[i][j + 1][0],dp[i][j][0] + cost[i][j + 1][0]);
                    update(dp[i][j + 1][1],dp[i][j][0] + q + cost[i][j + 1][1]);
                    update(dp[i][j + 1][1],dp[i][j][0] + cost[i][j + 1][2]);
                    
                    update(dp[i][j + 1][0],dp[i][j][1] + q + cost[i][j + 1][0]);
                    update(dp[i][j + 1][1],dp[i][j][1] + q + q + cost[i][j + 1][1]);
                    update(dp[i][j + 1][1],dp[i][j][1] + q + cost[i][j + 1][2]);
                }
            }
        }
        printf("%d\n",min(dp[n][n][0],dp[n][n][1]));
    }
    return 0;
}
		