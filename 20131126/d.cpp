#include <bits/stdc++.h>
using namespace std;

int n,m,r,q;
bool check(int x,int y,int xx,int yy)
{
    return x >= 0 && x < xx && y >= 0 && y < yy;
}

int a[110][110],b[15][15],ans[110][110];

int main()
{
    int t;
    cin >> t;
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d%d",&n,&m);
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                scanf("%d",&a[i][j]);
                ans[i][j] = a[i][j];
            }
        }
        scanf("%d%d",&r,&q);
        for(int i = 0; i < r; i ++) {
            for(int j = 0; j < q; j ++) {
                scanf("%d",&b[i][j]);
            }
        }
        int x = r / 2,y = q / 2;
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                if(a[i][j]) {
                    for(int k = -r; k < r; k ++)
                        for(int p = -q; p < q; p ++)
                            if(check(i + k,j + p,n,m) && check(x + k,y + p,r,q)) ans[i + k][j + p] |= b[x + k][y + p];
                }
        printf("Case %d:",cas);
        cout << endl;
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                printf("%d",ans[i][j]);
                if(j == m - 1) cout << endl;
                else printf(" ");
            }
        }
    }
    return 0;
}

