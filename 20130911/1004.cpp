#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010;
const long long oo = 1LL << 60;
struct tree
{
    int lt,rt;
    long long val;
}a[N * 4];

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    a[step].val = -oo;
    if(lt == rt) return;
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
}

long long query(int lt,int rt,int step)
{
    if(lt > rt) return -oo;
    if(a[step].lt == lt && a[step].rt == rt) return a[step].val;
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else {
        long long val = query(lt,a[2 * step].rt,2 * step);
        long long vall = query(a[2 * step + 1].lt,rt,2 * step + 1);
        return max(val,vall);
    }
}

void insert(int pos,int step,long long val)
{
    if(a[step].lt == a[step].rt) {
        a[step].val = val;
        return;
    }
    if(pos <= a[2 * step].rt) insert(pos,2 * step,val);
    else insert(pos,2 * step + 1,val);
    a[step].val = max(a[2 * step].val,a[2 * step + 1].val);
}

struct point
{
    int pos;
    long long val;
    point() {}
    point(long long val,int pos):val(val),pos(pos) {}
    friend bool operator < (const point &p,const point &q) {
        return p.val < q.val;
    }
};

priority_queue<point> q[N];
long long aa[N];
long long dp[N];

long long sqr(long long x)
{
    return x * x;
}

void solve(int n,int m)
{
    for(int i = 0; i <= n; i ++) dp[i] = -oo;
    for(int i = 0; i < N; i ++) {
        while(!q[i].empty()) q[i].pop();
    }
    init(0,100001,1);
    dp[1] = sqr(aa[1]);
//    cout << "yes" << endl;
//    cout << aa[1] << endl;
    q[aa[1]].push(point(dp[1] - aa[1],1));
//    cout << "push" << endl;
    insert(aa[1],1,dp[1] - aa[1]);
//    cout << "no" << endl;
    for(int i = 2; i <= n; i ++) {
        if(i > m + 1) {
            long long ht = aa[i - m - 1];
            insert(ht,1,-oo);
            while(!q[ht].empty() && q[ht].top().pos <= i - m) q[ht].pop();
            if(!q[ht].empty()) {
                insert(ht,1,q[ht].top().val);
            }
        }
        dp[i] = query(1,aa[i] - 1,1) + aa[i] * aa[i];
        if(i <= m) dp[i] = max(dp[i],sqr(aa[i]));
        if(dp[i] < 0) dp[i] = -oo;
        q[aa[i]].push(point(dp[i] - aa[i],i));
        insert(aa[i],1,q[aa[i]].top().val);
        //cout << i << " " << dp[i] << endl;
    }
    if(dp[n] < 0) printf("No solution\n");
    else printf("%I64d\n",dp[n]);
}
    
int main()
{
    int t,n,m;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d%d",&n,&m);
        for(int i = 1; i <= n; i ++)
            scanf("%I64d",&aa[i]);
        printf("Case #%d: ",cas);//solve(n,m));
        solve(n,m);
    }
    return 0;
}


