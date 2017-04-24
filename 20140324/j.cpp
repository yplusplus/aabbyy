#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
const int X = 12;
const double eps = 1e-8;
int sum[X][X][X][X][X];
int a[N][5];

int main()
{
    freopen("gift.in","r",stdin);
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        int n,m;
        scanf("%d%d",&n,&m);
        double b[5];
        int c[5],d[5];
        map<int,int> ma[5];
        memset(sum,0,sizeof(sum));
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < 5; j ++) {
                scanf("%lf",&b[j]);
                a[i][j] = 1000 * (b[j] + eps);
                ma[j][a[i][j]] = 1;
            }
        }
        for(int j = 0; j < 5; j ++) {
            int tot = 0;
            for(map<int,int>::iterator it = ma[j].begin(); it != ma[j].end(); it ++)
                it->second = ++ tot;
        }
        for(int i = 0; i < n; i ++) sum[ma[0][a[i][0]]][ma[1][a[i][1]]][ma[2][a[i][2]]][ma[3][a[i][3]]][ma[4][a[i][4]]] ++;
        for(int i = 0; i < X; i ++)
            for(int j = 0; j < X; j ++)
                for(int k = 0; k < X; k ++)
                    for(int r = 0; r < X; r ++)
                        for(int p = 0; p < X; p ++)
                            for(int q = 1; q < 32; q ++) {
                                int x[5];
                                x[0] = i,x[1] = j,x[2] = k,x[3] = r,x[4] = p;
                                int flag = -1;
                                bool zero = true;
                                for(int bit = 0; bit < 5; bit ++) {
                                    if(!(q & (1 << bit))) continue;
                                    x[bit] --;
                                    flag *= (-1);
                                    if(x[bit] < 0) zero = false;
                                }
                                if(!zero) continue;
                                sum[i][j][k][r][p] += flag * sum[x[0]][x[1]][x[2]][x[3]][x[4]];
                            }
        printf("Case %d:\n",cas);
        while(m --) {
            for(int j = 0; j < 5; j ++) {
                scanf("%lf",&b[j]);
                int x = (b[j] + eps) * 1000;
                c[j] = 100000;
                for(map<int,int>::iterator it = ma[j].begin(); it != ma[j].end(); it ++) {
                    if(it->first >= x) {
                        c[j] = it->second;
                        break;
                    }
                }
            }
            bool flag = false;
            for(int j = 0; j < 5; j ++) {
                scanf("%lf",&b[j]);
                int x = (b[j] + eps) * 1000;
                d[j] = -1;
                for(map<int,int>::iterator it = ma[j].begin(); it != ma[j].end(); it ++) {
                    if(it->first <= x) {
                        d[j] = it->second;
                    }
                }    
                if(d[j] < c[j]) {
                    flag = true;
                }
            }
            if(flag) {
                printf("0\n");
                continue;
            }
            int ans = 0;
            for(int i = 0; i < 32; i ++) {
                int x[5];
                for(int j = 0; j < 5; j ++) x[j] = d[j];
                int flag = 1;
                for(int j = 0; j < 5; j ++)
                    if(i & (1 << j)) {
                        flag *= (-1);
                        x[j] = c[j] - 1;
                    }
                ans += flag * sum[x[0]][x[1]][x[2]][x[3]][x[4]];
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}


