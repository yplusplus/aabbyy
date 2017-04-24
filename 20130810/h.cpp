#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

const double eps = 1e-6;
struct point
{
    double x,y;
    void read() {
        scanf("%lf%lf",&x,&y);
    }
}a[5010];

double dist(point p,point q)
{
    return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

int visit[5010];
queue<int> q;

bool bfs(double mid,int m,int n)
{
    while(!q.empty()) q.pop();
    visit[0] = 1;
    for(int i = 1; i <= m; i ++) {
        if(a[i].y <= mid + eps) {
            visit[i] = 1;
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(n - a[u].y <= mid + eps) return true;
        for(int i = 1; i <= m; i ++) {
            if(visit[i]) continue;
            if(dist(a[i],a[u]) <= mid * mid + eps) {
                q.push(i);
                visit[i] = 1;
            }
        }
    }
    return false;
}
        
    

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF) {
        if(!n && !m) break;
        for(int i = 1; i <= m; i ++) a[i].read();
        double ans = 0;
        double lt = 0,rt = n,mid;
        while(lt + eps <= rt) {
            memset(visit,0,sizeof(visit));
            mid = (lt + rt) / 2;
            if(bfs(mid,m,n)) rt = mid;
            else ans = mid,lt = mid;
        }
        printf("%.3lf\n",ans);
    }   
    return 0;
}


