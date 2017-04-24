#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
const int N = 500010;
struct tree
{
    int lt,rt,mix,pos;
}a[N * 4];

int c[N];

void update(int step)
{
    if(a[2 * step].mix <= a[2 * step + 1].mix)
        a[step].pos = a[2 * step].pos;
    else a[step].pos = a[2 * step + 1].pos;
    a[step].mix = min(a[2 * step].mix,a[2 * step + 1].mix);
}

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    if(lt == rt) {
        a[step].mix = c[lt];
        a[step].pos = lt;
        return;
    }
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    update(step);
}

void insert(int pos,int step)
{
    if(a[step].lt == a[step].rt) {
        a[step].mix = oo;
        c[pos] = oo;
        return;
    }
    if(pos <= a[2 * step].rt) insert(pos,2 * step);
    else insert(pos,2 * step + 1);
    update(step);
}

int query(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        return a[step].pos;
    }
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else {
        int x = query(lt,a[2 * step].rt,2 * step);
        int y = query(a[2 * step + 1].lt,rt,2 * step + 1);
        if(c[x] <= c[y]) return x;
        return y;
    }
}

int f[N],b[N * 2];
int lowbit(int x)
{
    return x & (-x);
}

void insert(int x)
{
    for(int i = x; i < N * 2; i += lowbit(i))
        b[i] ++;
}

int query(int x)
{
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        ans += b[i];
    return ans;
}

int main()
{
    int n,m,x;
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) {
        cin >> c[i];
    }
    init(1,n,1);
    memset(b,0,sizeof(b));
    long long ans = 0;
    for(int i = n; i >= 1; i --) {
        f[i] = query(c[i] - 1);
        insert(c[i]);
        ans += f[i];
    }
    cout << ans << endl;
    while(m --) {
        cin >> x;
        while(f[x]) {
            int y = query(x + 1,n,1);
            if(c[y] <= c[x]) {
                ans -= f[y];
                insert(y,1);
                f[y] = 0;
            }
            else {
                ans -= f[x];
                insert(x,1);
                f[x] = 0;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

