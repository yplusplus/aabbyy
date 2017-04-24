#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
long long lowbit(long long x)
{
    return x & (-x);
}

struct point
{
    long long x;
    int id;
    point() {}
    point(long long x,int id):x(x),id(id) {}
    friend bool operator < (const point &p,const point &q) {
        if(p.x != q.x) return p.x < q.x;
        return p.id < q.id;
    }
}a[N],b[N];
set<point> st;
vector<point> v[70];
bool visit[N];
int ans[N][2];
int zero_id[N];

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i].x;
        a[i].id = i;
    }
    int zero = 0;
    for(int i = 1; i <= n; i ++) {
        if(!a[i].x) zero_id[zero ++] = a[i].id;
    }
    sort(a + 1,a + n + 1);
    int tot = 0;
    for(int i = 1; i <= n; i ++)
        if(a[i].x != 0) {
            st.insert(a[i]);
            b[++ tot] = a[i];
        }
    sort(b + 1,b + tot + 1);
    int cnt = 0;
    for(int i = tot; i >= 1; i --) {
        if(visit[b[i].id]) continue;
        if(lowbit(b[i].x) == b[i].x) continue;
        st.erase(b[i]);
        for(int j = 62; j >= 0; j --) {
            if((1LL << j) < b[i].x) break;
            long long x = (1LL << j) - b[i].x;
            set<point>::iterator it = st.lower_bound(point(x,-1));
            if(it == st.end()) continue;
            if((*it).x != x) continue;
            else if(visit[(*it).id]) continue;
            else {
                visit[b[i].id] = 1;
                visit[(*it).id] = 1;
                ans[++ cnt][0] = b[i].id;
                ans[cnt][1] = (*it).id;
                st.erase(it);
                break;
            }
        }
        if(!visit[b[i].id]) st.insert(b[i]);
    }
    for(int i = 1; i <= tot; i ++) {
        if(visit[b[i].id]) continue;
        for(int j = 0; j < 62; j ++) {
            if((1LL << j) == b[i].x) v[j].push_back(b[i]);
        }
    }
    for(int i = 0; i < 63; i ++) {
        if(v[i].size() & 1) {
            if(zero) {
                zero --;
                ans[++ cnt][0] = zero_id[zero];
                ans[cnt][1] = v[i].back().id;
                v[i].pop_back();
                continue;
            }
        }
    }
    for(int i = 0; i < 63; i ++) {
        while(zero && v[i].size()) {
            zero --;
            ans[++ cnt][0] = zero_id[zero];
            ans[cnt][1] = v[i].back().id;
            v[i].pop_back();
        }
        for(int j = 1; j < v[i].size(); j += 2) {
            ans[++ cnt][0] = v[i][j - 1].id;
            ans[cnt][1] = v[i][j].id;
        }
    }
    cout << cnt << endl;
    for(int i = 1; i <= cnt; i ++)
        cout << ans[i][0] << " " << ans[i][1] << endl;
    return 0;
}
