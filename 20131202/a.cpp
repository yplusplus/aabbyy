#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
using namespace std;

vector<int> v[10010];
int pre[10010],visit[10010];
char a[110][110];
int n;
stack<int> sta;
set<int> st[10010];

int find(int u)
{
    for(int i = 0; i < v[u].size(); i ++) {
        if(!visit[v[u][i]]) {
            visit[v[u][i]] = 1;
            sta.push(v[u][i]);
            int tmp = pre[v[u][i]];
            pre[v[u][i]] = u;
            if(tmp == -1 || find(tmp)) return 1;
            pre[v[u][i]] = tmp;
        }
    }
    return 0;
}

int r[110][110],c[110][110];
int build_graph()
{
    memset(a,0,sizeof(a));
    int x,y,rr;
    for(int i = 1; i <= n; i ++)
        scanf("%s",a[i] + 1);
    int c1 = 0,c2 = 0;
    memset(r,0,sizeof(r));
    memset(c,0,sizeof(c));
    for(int i = 0; i < 10010; i ++) v[i].clear(),st[i].clear();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(a[i][j] == '.' && r[i][j] == 0) {
                c1 ++;
                for(int k = j; k <= n; k ++) {
                    if(a[i][k] == 'X') break;
                    r[i][k] = c1;
                }
               for(int k = j; k >= 1; k --) {
                  if(a[i][k] == 'X') break;
                  r[i][k] = c1;
               }
            }
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(a[i][j] == '.' && c[i][j] == 0) {
                c2 ++;
                for(int k = i; k >= 1; k --) {
                    if(a[k][j] == 'X') break;
                    c[k][j] = c2;
                }
                for(int k = i; k <= n; k ++) {
                    if(a[k][j] == 'X') break;
                    c[k][j] = c2;
                }
            }
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(a[i][j] == '.') {
                if(!st[r[i][j]].count(c[i][j])) {
                    v[r[i][j]].push_back(c[i][j]);
                    st[r[i][j]].insert(c[i][j]);
                }
            }
    memset(pre,-1,sizeof(pre));
    memset(visit,0,sizeof(visit));
    int ans = 0;
    while(!sta.empty()) sta.pop();
    for(int i = 1; i <= c1; i ++) {
        ans += find(i);
        while(!sta.empty()) {
            int u = sta.top();
            sta.pop();
            visit[u] = 0;
        }
    }
    return ans;
}

int main()
{
    while(scanf("%d",&n) != EOF) {
        int ans = build_graph();
        printf("%d\n",ans);
    }
    return 0;
}

