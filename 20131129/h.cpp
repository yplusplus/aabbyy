#include <bits/stdc++.h>
using namespace std;

vector<int> v[12][26],ve[12][26];
    
const double eps = 1e-7;
double dp[1010][12][12];
int visit[1010][12][12],times;
int out[12];
struct point
{
    int x,y;
    int dep;
    point() {}
    point(int x,int y,int dep):x(x),y(y),dep(dep) {}
};
queue<point> q;

double cal(int n)
{
    ++ times;
    while(!q.empty()) q.pop();
    double ans = 0;
    int st,ed,x,y,dep,xx,yy;
    scanf("%d%d",&st,&ed);
    dp[0][st][ed] = 1;
    q.push(point(st,ed,0));
    while(!q.empty()) {
        point u = q.front();
        q.pop();
        x = u.x,y = u.y;
        dep = u.dep;
        if(dp[dep][x][y] < eps) continue;
        if(dep > 1000) continue;
        for(int i = 0; i < 26; i ++)
            for(int j = 0; j < v[x][i].size(); j ++)
                if(v[x][i][j] == y) ans += dp[dep][x][y] / out[x];
        for(int i = 0; i < 26; i ++)
            for(int j = 0; j < v[x][i].size(); j ++) {
                if(v[x][i][j] == ed) continue;
                for(int k = 0; k < ve[y][i].size(); k ++) {
                    if(ve[y][i][k] == ed) continue;
                    if(v[x][i][j] == ve[y][i][k]) {
                        ans += dp[dep][x][y] / out[x] / out[ve[y][i][k]];
                        continue;
                    }
                    xx = v[x][i][j];
                    yy = ve[y][i][k];
                    double tmp = dp[dep][x][y] / out[x] / out[yy];
                    if(visit[dep + 1][xx][yy] != times) {
                        visit[dep + 1][xx][yy] = times;
                        dp[dep + 1][xx][yy] = tmp;
                        q.push(point(xx,yy,dep + 1));
                    }
                    else dp[dep + 1][xx][yy] += tmp;
                }
            }
    }
    return ans;
}

void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            for(int k = 0; k < 1010; k ++)
                visit[k][i][j] = 0;
    times = 0;
    int x,y;
    char s[15];
    int r;
    memset(out,0,sizeof(out));
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < 26; j ++) {
            v[i][j].clear();
            ve[i][j].clear();
        }
    }
    while(m --) {
        scanf("%d%d%s",&x,&y,s);
        out[x] ++;
        v[x][s[0] - 'A'].push_back(y);
        ve[y][s[0] - 'A'].push_back(x);
    }
    scanf("%d",&r);
    while(r --) {
        printf("%.10lf\n",cal(n));
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case %d:\n",cas);
        solve();
    }
    return 0;
}

/*
2
4 3
0 1 A
1 2 A
2 3 A
2 
0 3
2 0

5 4
1 2 B
2 3 D
2 4 A
2 0 B
2
1 3
1 0
*/

