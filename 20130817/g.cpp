/*
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dir[4][2] = {0,1,0,-1,1,0,-1,0};
int n;
char s[15][15];
int visit[15][15],sum;

bool check(int x,int y)
{
    return x >= 0 && x < n && y >= 0 && y < n && s[x][y] == '1';
}

void dfs(int x,int y)
{
    visit[x][y] = 1;
    for(int i = 0; i < 4; i ++) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if(!check(tx,ty)) {
            sum ++;
            continue;
        }
        if(!visit[tx][ty]) dfs(tx,ty);
    }
}

int main()
{
    n = 5;
for(int m = 16; m <= 16; m ++) {
    int ans = 0;
    for(int i = 1; i < (1 << (n * n)); i ++) {
        memset(s,0,sizeof(s));
        for(int j = 0; j < n; j ++)
            for(int k = 0; k < n; k ++)
                s[j][k] = '0';
        memset(visit,0,sizeof(visit));
        int tot = 0;
        for(int j = 0; j < n * n; j ++) {
            if(i & (1 << j)) {
                int x = j / n;
                int y = j % n;
                s[x][y] = '1';
                tot ++;
            }
        }
        if(tot != m) continue;
        sum = 0;
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
                if(!visit[i][j] && s[i][j] == '1') dfs(i,j);
        if(sum > ans) ans = sum;
        if(sum == 48)
            for(int i = 0; i < n; i ++)
                cout << s[i] << endl;
        
    }
    printf("%d  %d : %d",n,m,ans);
    cout << endl;
}
return 0;
}
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long cal(long long n,long long m)
{
    if(m <= (n * n) / 2) return m * 4;
    long long x = (n * n ) / 2;
    if(m <= (n * n) / 2 + 4) return x * 4;
    long long y = ((n - 2) / 2) * 4;
    if(m - x - 4 <= y) return 4 * x - 2 * (m - x - 4);
    return 4 * x - 2 * y - 4 * (m - x - y - 4);
}


long long cal1(long long n,long long m)
{
    if(m <= (n * n + 1) / 2) return m * 4;
    long long x = (n * n + 1) / 2;
    long long y = (n / 2) * 4;
    if(m - x <= y) return 4 * x - 2 * (m - x);
    return 4 * x - 2 * y - 4 * (m - x - y);
}
 
long long cal2(long long n,long long m)
{
    if(m <= n * n / 2) return m * 4;
    if(m <= n * n / 2 + 2) return ((n * n) / 2) * 4;
    if(m <= n * n / 2 + 2 + (2 * n - 4)) return ((n * n) / 2) * 4 - 2 * (m - (n * n / 2 + 2));
    return (n * n / 2) * 4 - 2 * (2 * n - 4) - 4 * (m - (n * n / 2 + 2 + (2 * n - 4)));
}
    
int main()
{
    long long n,m;
    ios::sync_with_stdio(0);
    while(cin >> n >> m) {     
        if(!n && !m) break;
        if(m == 1) {
            cout << 4 << endl;
            continue;
        }
        if(m == 0) {
            cout << 0 << endl;
            continue;
        }   
        if(!n && !m) break;
        if(n & 1) cout << max(cal(n,m),cal1(n,m)) << endl;
        else cout << cal2(n,m) << endl;
    }
    return 0;
}


