#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int a[N][N];

int gauss(int n,int m)
{
    int r,c;
    for(r = c = 0; r < n && c < m; r ++,c ++) {
        int idx = r;
        for(idx = r; idx < n; idx ++) {
            if(a[idx][c]) break;
        }
        if(idx == n) {
            r --;
            continue;
        }
        for(int i = c; i <= m; i ++) swap(a[r][i],a[idx][i]);
        for(int i = r + 1; i < n; i ++) {
            if(!a[i][c]) continue;
            for(int j = c; j <= m; j ++)
                a[i][j] ^= a[r][j];
        }
    }
    for(int i = r; i < n; i ++)
        if(a[i][m]) return -1;
    return m - r;
}

int pri[N];
bool check(int x)
{
    for(int i = 2; i < x; i ++)
        if(x % i == 0) return false;
    return true;
}

void solve()
{
    int n,m,x;
    scanf("%d%d",&m,&n);
    memset(a,0,sizeof(a));
    for(int i = 0; i < n; i ++) {
        scanf("%d",&x);
        for(int j = 0; j < m; j ++) {
            while(x % pri[j] == 0) {
                x /= pri[j];
                a[j][i] ^= 1;
            }
        }
    }
    int free = gauss(m,n);
    if(free == -1) cout << 0 << endl;
    else {
        int ans[35];
        memset(ans,0,sizeof(ans));
        ans[0] = 1;
        while(free --) {
            for(int i = 0; i < 35; i ++) ans[i] *= 2;
            for(int i = 0; i < 34; i ++) {
                ans[i + 1] += ans[i] / 10;
                ans[i] %= 10;
            }
        }
        ans[0] --;
        int i = 34;
        for(i; i >= 0; i --) {
            if(ans[i]) break;
        }
        if(i == -1) i ++;
        for(i ; i >= 0; i --)
            printf("%d",ans[i]);
        cout << endl;
    }
}
            
            
int main()
{
    for(int i = 2,j = 0; j < 105; i ++)
        if(check(i)) pri[j ++] = i;
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
        if(t) puts("");
    }
    return 0;
}
