#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct point
{
    int x,y,id;
    friend bool operator < (const point &p,const point &q) {
        return p.x < q.x;
    }
}a[N];
map<int,int> ma;

int lowbit(int x) { return x & (-x); }
int dp[N],p[N],fa[N],c[N];
int query(int x,int &pre) {
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)) {
        if(ans < c[i]) {
            ans = c[i];
            pre = fa[i];
        }
    }
    return ans;
}

void insert(int x,int y,int pre)
{
    for(int i = x; i < N; i += lowbit(i)) {
        if(y > c[i]) {
            c[i] = y;
            fa[i] = pre;
        }
    }
}

int ans[N];
void solve()
{
    int n;
    scanf("%d",&n);
    memset(c,0,sizeof(c));
    memset(p,-1,sizeof(p));
    ma.clear();
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].id = i;
        ma[a[i].y] = 1;
    }
    int tot = 0; 
    for(map<int,int>::iterator it = ma.begin(); it != ma.end(); it ++) it->second = ++ tot;
    for(int i = 1; i <= n; i ++) {
        a[i].y = ma[a[i].y];
    }
    sort(a + 1,a + n + 1);
    int maxn = -1,id = -1;
    int i = 1;
    while(i <= n) {
        int j = i;
        while(j <= n && a[i].x == a[j].x) j ++;
        for(int k = i; k < j; k ++) {
            dp[a[k].id] = 1 + query(a[k].y - 1,p[a[k].id]);
            if(maxn < dp[a[k].id]) {
                maxn = dp[a[k].id];
                id = a[k].id;
            }
        }
        for(int k = i; k < j; k ++) {
            insert(a[k].y,dp[a[k].id],a[k].id);
        }
        i = j;
    }
    tot = 0;
    while(id != -1) {
        ans[++ tot] = id;
        id = p[id];
    }
    sort(ans + 1,ans + tot + 1);
    cout << tot << endl;
    for(int i = 1; i <= tot; i ++) {
        cout << ans[i];
        if(i == tot) cout << endl;
        else cout << " ";
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
        if(t) puts("");
    }
    return 0;
}
