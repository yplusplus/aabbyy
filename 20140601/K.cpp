#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct tree
{
    long long lt,rt,mix,val;
    tree() { }
    tree(long long lt,long long rt,long long mix,long long val):lt(lt),rt(rt),mix(mix),val(val) {}
}a[N << 2];

long long K;
long long b[N],c[N];
tree update(tree p,tree q)
{
    tree ans;
    ans.lt = p.lt,ans.rt = q.rt;
    long long dec = (q.lt - p.rt) * K;
    long long has = p.val - dec; 
    if(has < q.mix) {
        ans.mix = p.mix + q.mix - has;
        ans.val = q.val;
    }
    else {
        ans.mix = p.mix;
        ans.val = has - q.mix + q.val;
    }
    return ans;
}

void init(int lt,int rt,int step)
{
    if(lt == rt) {
        a[step].lt = b[lt];
        a[step].rt = b[lt];
        a[step].mix = 0;
        a[step].val = c[lt];
        return;
    }
    int mid = (lt + rt) >> 1;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    a[step] = update(a[2 * step],a[2 * step + 1]);
}

tree query(int L,int R,int step)
{
    if(a[step].rt < L) return tree(-1,-1,-1,-1);
    if(a[step].lt > R) return tree(-1,-1,-1,-1);
    if(L <= a[step].lt && R >= a[step].rt) return a[step];
    tree x = query(L,R,2 * step);
    tree y = query(L,R,2 * step + 1);
    if(x.lt == -1) return y;
    if(y.lt == -1) return x;
    return update(x,y);
}

int main()
{
    int n,m;
    long long x,y,z;
    while(scanf("%d%d%I64d",&n,&m,&K) != EOF) {
        for(int i = 1; i <= n; i ++) scanf("%I64d%I64d",&b[i],&c[i]);
        init(1,n,1);
        while(m --) {
            scanf("%I64d%I64d%I64d",&x,&y,&z);
            long long ans = 0;
            tree tmp = query(x,y,1);
            if(tmp.lt == -1) ans = z - (y - x) * K;
            else {
                z -= K * (tmp.lt - x);
                ans = tmp.val + max(0LL,z - tmp.mix);
                ans -= K * (y - tmp.rt);
            }
            if(ans < 0) ans = 0;
            printf("%I64d\n",ans);
        }
    }    
    return 0;
}
    
