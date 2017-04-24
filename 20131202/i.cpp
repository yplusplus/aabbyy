#include <bits/stdc++.h>
using namespace std;

struct point
{
    long long dep,val;
    point() {}
    point(long long dep,long long val):dep(dep),val(val) {}
    friend bool operator < (const point &p,const point &q) {
        if(p.dep != q.dep) return p.dep < q.dep;
        return p.val > q.val;
    }
};
priority_queue<point> q;

bool solve()
{
    int n;
    if(scanf("%d",&n) == EOF) return false;
    long long a[55],dep[110];
    for(int i = 1; i <= n; i ++) scanf("%lld",&a[i]);
    sort(a + 1,a + n + 1);
    long long ans = 0;
    memset(dep,0,sizeof(dep));
    while(!q.empty()) q.pop();
    for(int i = 1; i <= n; i ++)
        if(a[i] == a[n]) {
            q.push(point(a[i],1));
            dep[a[i]] = 1;
            ans ++;
        }
        else q.push(point(a[i],0));
    while(!q.empty()) {
        point u = q.top();
        q.pop();
        if(q.empty()) break;
        point v = q.top();
        q.pop();
        if(!u.val) {
            u.val = dep[u.dep + 1];
            ans += u.val;
        }
        if(!v.val) {
            v.val = dep[v.dep + 1];
            ans += v.val;
        }
        dep[v.dep - 1] = max(dep[v.dep - 1],u.val + v.val);
        q.push(point(v.dep - 1,u.val + v.val));
    }
    cout << ans << endl;
    return true;
}

int main()
{
    while(solve()); 
    return 0;
}

