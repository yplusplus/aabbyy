#include <bits/stdc++.h>
using namespace std;

const int N = 510;
struct point
{
    long long val,pos;
    friend bool operator < (const point &p,const point &q) {
        if(p.val != q.val) return p.val < q.val;
        return p.pos < q.pos;
    }
    point() {}
    point(long long val,long long pos):val(val),pos(pos) {}
};
set<point> st[N];
point del[N];
int path[N][N];
void add(int len,int val,int pos)
{
    if(st[len].empty()) {
        st[len].insert(point(val,pos));
        return;
    }
    set<point>::iterator it = st[len].upper_bound(point(val - 1,0x7fffffff));
    int cnt = 0;
    while(it != st[len].end()) {
        if(it->pos >= pos) {
            del[cnt ++] = *it;
            it ++;
        }
        else break;
    }
    for(int i = 0; i < cnt; i ++) st[len].erase(del[i]);
    if(st[len].empty()) {
        st[len].insert(point(val,pos));
        return;
    }        
    it = st[len].lower_bound(point(val,pos));
    if(it == st[len].begin()) {
        st[len].insert(point(val,pos));
    }
    else {
        it --;
        if(it->pos <= pos) return;
        else st[len].insert(point(val,pos));
    }
}

long long a[N],b[N];
int pp[N];

void solve()
{
    int n,m;
    scanf("%d",&n);
    memset(path,-1,sizeof(path));
    for(int i = 0; i < N; i ++) st[i].clear();
    for(int i = 1; i <= n; i ++) scanf("%lld",&a[i]);
    scanf("%d",&m);
    for(int i = 1; i <= m; i ++) scanf("%lld",&b[i]);
    int max_len = 0;
    for(int i = 1; i <= n; i ++) {
        int pre = 0;
        for(int j = 1; j <= m; j ++) {
            if(a[i] != b[j]) continue;
            if(!max_len) {
                pre = 1;
                max_len ++;
                add(1,a[i],j);
                path[i][1] = j;
                continue;
            }
            int lt = max(1,pre),rt = max_len,mid,ans = 0;
            while(lt <= rt) {
                mid = (lt + rt) >> 1;
                set<point>::iterator it = st[mid].lower_bound(point(a[i] - 1,j));
                if(it != st[mid].begin()) it --;
                else {
                    rt = mid - 1;
                    continue;
                }
                if(it->pos < j) ans = mid,lt = mid + 1;
                else rt = mid - 1;
            }
            if(ans == max_len) {
                max_len ++;
                path[i][max_len] = j;
                st[max_len].insert(point(a[i],j));
                pre = max_len;
            }
            else if(ans >= pre) {
                pre = ans + 1;
                add(ans + 1,a[i],j);
                path[i][pre] = j;
            }
        }
    }
    cout << max_len << endl;
    if(!max_len) return;
    int i,j,pre = -1;
    for(i = n; i >= 1; i --) {
        if(path[i][max_len] != -1) {
            pp[max_len] = a[i];
            pre = i;
            break;
        }
    }
    int tt = max_len - 1;
    while(tt) {
        for(i = i - 1; i >= 1 && tt; i --) {
            if(a[i] < pp[tt + 1] && path[i][tt] < path[pre][tt + 1] && path[i][tt] != -1) {
                pre = i;
                pp[tt --] = a[i];
                break;
            }
        }
    }
    for(i = 1; i <= max_len; i ++) {
        printf("%d",pp[i]);
        if(i == max_len) printf("\n");
        else printf(" ");
    }
}
    
                        
int main()
{
    int t;
    scanf("%d",&t);
    bool flag = false;
    while(t --) {
        if(flag) printf("\n");
        flag = true;
        solve();
    }
    return 0;
}
    

