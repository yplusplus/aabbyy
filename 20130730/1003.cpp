#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int dp[1728010][20];
int mod;
vector<int> v[35];
int pri[] = {2,3,5,7,11,13,17,19,23,29};
bool a[35][35];
//1 17 19 23
//2 4 8 16
//6 12 18 24
//3 9 27
int bit[25];

void decode(int state,int n)
{
    for(int i = n; i >= 0; i --) {
        bit[i] = state % (v[i].size() + 1);
        state /= (v[i].size() + 1);
    }
}

int encode(int n)
{
    int state = 0;
    for(int i = 0; i <= n; i ++) {
        state = (v[i].size() + 1) * state + bit[i];
    }
    return state;
}

void solve(int n)
{
    int tot = 1;
    memset(a,false,sizeof(a));
    for(int i = 0; i <= n; i ++) {
        tot *= (v[i].size() + 1);
        for(int j = 0; j <= n; j ++) {
            if(i == j) continue;
            if(__gcd(v[i][0],v[j][0]) == 1) a[i][j] = true;
        }
    }
    a[0][0] = true;
    memset(dp,0,sizeof(dp));
    memset(bit,0,sizeof(bit));
    for(int i = 0; i <= n; i ++) {
        bit[i] = 1;
        dp[encode(n)][i] = v[i].size() % mod;
        bit[i] = 0;
    }
    for(int i = 0; i < tot; i ++) {
        for(int j = 0; j <= n; j ++) {
           if(!dp[i][j]) continue;
           decode(i,n);
           for(int k = 0; k <= n; k ++) {
               if(!a[j][k]) continue;
               if(bit[k] == v[k].size()) continue;
               bit[k] ++;
               int x = encode(n);
               dp[x][k] += (v[k].size() - bit[k] + 1) * dp[i][j];
               if(dp[x][k] >= mod) dp[x][k] %= mod;
               bit[k] --;
           }
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i ++)
        ans += dp[tot - 1][i];
    cout << ans % mod << endl;
}
        
int main()
{
    int n,t;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        scanf("%d",&mod);
        int visit[35];
        memset(visit,0,sizeof(visit));
        int ct = 0;
        for(int i = 0; i < 20; i ++) v[i].clear();
        for(int i = 0; i < 20; i ++) v[i].clear();
        v[0].push_back(1);
        visit[1] = 1;
        for(int i = n / 2 + 1; i <= n; i ++) {
            bool flag = false;
            for(int j = 0; pri[j] <= i; j ++) {
                if(i == pri[j]) {
                    visit[pri[j]] = 1;
                    v[ct].push_back(pri[j]);
                }
            }
        }
        for(int i = 2; i <= n; i ++) {
            if(visit[i]) continue;
            ++ ct;
            for(int j = i; j <= n; j ++) {
                if(visit[j]) continue;
                bool flag = true;
                for(int k = 0; pri[k] <= j; k ++) {
                    if(j % pri[k] && i % pri[k]) continue;
                    int cc = 0;
                    if(j % pri[k] == 0) cc ++;
                    if(i % pri[k] == 0) cc ++;
                    if(cc == 1) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    v[ct].push_back(j);
                    visit[j] = 1;
                }
            }
        }
        solve(ct);
        /*
        printf("%d\n",ct);
        int ans = 1;
        for(int i = 1; i <= ct; i ++) {
            for(int j = 0; j < v[i].size(); j ++) {
                printf("%d ",v[i][j]);
            }
            printf("\n");
            ans *= (v[i].size() + 1);
        }
        printf("tot state = %d\n",ans);
        */
    }
    return 0;
}



