#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstdlib>
using namespace std;

struct point
{
    int val,id;
    point() {}
    point(int val,int id):val(val),id(id) {}
    friend bool operator < (const point &p,const point &q) {
        return p.val < q.val;
    }
};

priority_queue<point> q[32];

struct node
{
    int val,id;
    node() {}
    node(int val,int id):val(val),id(id) {}
    friend bool operator < (const node &p,const node &q) {
        return p.val > q.val;
    }
};

priority_queue<node> p[32];

int visit[60010];

void get_ans(int m)
{
    int ans = 0;
    for(int i = 0; i < (1 << m); i ++) {
        while(!q[i].empty()) {
            if(visit[q[i].top().id]) {
                q[i].pop();
                continue;
            }
            break;
        }
        while(!p[i].empty()) {
            if(visit[p[i].top().id]) {
                p[i].pop();
                continue;
            }
            break;
        }
        if(!q[i].empty() && !p[i].empty()) ans = max(ans,abs(q[i].top().val - p[i].top().val));
    }
    printf("%d\n",ans);
    //return ans;
}
        
int main()
{
    int n,m,cd,a[10],x;
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 0; i < (1 << m); i ++) {
            while(!q[i].empty()) q[i].pop();
            while(!p[i].empty()) p[i].pop();
        }
        memset(visit,0,sizeof(visit));
        for(int k = 1; k <= n; k ++) {
            scanf("%d",&cd);
            if(cd == 1) {
                scanf("%d",&x);
                visit[x] = 1;
                get_ans(m);
            }
            else {
                for(int i = 0; i < m; i ++) {
                    scanf("%d",&a[i]);
                }
                int sum1 = 0,sum2 = 0;
                for(int i = 0; i < (1 << m); i ++) {
                    sum1 = sum2 = 0;
                    for(int j = 0; j < m; j ++)
                        if(i & (1 << j)) {
                            sum1 += a[j];
                            sum2 -= a[j];
                        }
                        else {
                            sum1 -= a[j];
                            sum2 += a[j];
                        }
                    q[i].push(point(sum1,k));
                    p[i].push(node(sum1,k));
                }
                get_ans(m);
            }
        }
    }           
    return 0;
}

