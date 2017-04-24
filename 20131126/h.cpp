#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
int visit[N * 2],a[N],b[N],c[N * 2];
bool flag[N * 2];

int find(int x,int n)
{
    int lt = 1,rt = n,mid;
    while(lt <= rt) {
        mid = (lt + rt) / 2;
        if(c[mid] == x) return mid;
        if(c[mid] > x) rt = mid - 1;
        else lt = mid + 1;
    }
}

void solve()
{
    long long ans = 0;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i =1 ; i <= n; i ++) { 
        scanf("%d",&a[i]);
        c[i] = a[i];
    }
    for(int i = 1; i <= m; i ++) {
        scanf("%d",&b[i]);
        c[i + n] = b[i];
    }
    if(n < m) {
        cout << 0 << endl;
        return;
    }
    sort(c + 1,c + n + m + 1);
    int cnt = 1;
    for(int i = 1; i <= n + m; i ++) {
        if(c[i] != c[cnt]) c[++ cnt] = c[i];
    }
    for(int i = 1; i <= n; i ++) a[i] = find(a[i],cnt);
    memset(visit,0,sizeof(visit));
    memset(flag,false,sizeof(flag));
    for(int i = 1; i <= m; i ++) {
        b[i] = find(b[i],cnt);
        flag[b[i]] = true;
    }
    int sum = 0,tot = 0;
    for(int i = 1; i <= m; i ++) {
        visit[b[i]] ++;
    }
    for(int i = 1; i <= cnt; i ++)
        if(flag[i]) tot ++;
    for(int i = 1; i <= m; i ++) {
        visit[a[i]] --;
        if(flag[a[i]] && visit[a[i]] == 0) sum ++;
        else if(flag[a[i]] && visit[a[i]] == -1) sum --;
    }
    if(sum == tot) ans ++;
    for(int i = m + 1; i <= n; i ++) {
        visit[a[i - m]] ++;
        if(flag[a[i - m]] && visit[a[i - m]] == 0) sum ++;
        else if(flag[a[i - m]] && visit[a[i - m]] == 1) sum --;
        
        visit[a[i]] --;
        if(flag[a[i]] && visit[a[i]] == 0) sum ++;
        else if(flag[a[i]] && visit[a[i]] == -1) sum --;   
        
        if(sum == tot) ans += (i - m + 1) * (i - m + 1);
    }
    cout << ans << endl;
}
        
        
int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
    }
    return 0;
}


