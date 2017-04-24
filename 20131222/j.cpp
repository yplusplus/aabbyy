#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int dim;
struct matrix
{
    double a[105][105];
    void init() {
        for(int i = 0; i <= dim; i ++)
            for(int j = 0; j <= dim; j ++)
                a[i][j] = 0;
    }
    
    matrix operator * (const matrix &p) {
        matrix c;
        c.init();
        for(int i = 1; i <= dim; i ++)
            for(int j = 1; j <= dim; j ++)
                for(int k = 1; k <= dim; k ++)
                    c.a[i][j] += a[i][k] * p.a[k][j];
        return c;
    }
};

matrix pow(int n,matrix t)
{
    matrix b;
    b.init();
    for(int i = 1; i <= dim; i ++) b.a[i][i] = 1;
    while(n) {
        if(n & 1) b = b * t;
        t = t * t;
        n /= 2;
    }
    return b;
}

bool cmp(int x,int y)
{
    return x > y;
}

double dp[5010][110];
void solve()
{
    int n,m;
    double a[110];
    double b[110];
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i ++)
        scanf("%lf",&a[i]);
    sort(a + 1,a + n + 1,cmp);
    int lt = (n + 1) / 2,rt = lt + 1;
    for(int i = 1; i <= n; i ++)
        if(i & 1) b[lt --] = a[i];
        else b[rt ++] = a[i];
    if(n <= 2) {
        double ans = 0;
        for(int i = 1; i <= n; i ++)
            ans += a[i];
        printf("%.6lf\n",ans);
        return;
    }
    matrix c;
    dim = n;
    c.init();
    //for(int i = 1; i <= n; i ++) cout << b[i] << " ";
    //cout << endl;
    double p = 0;
    double pp[110];
    memset(pp,0,sizeof(pp));
    for(int i = 1; i < n; i ++)
        for(int j = i + 1; j <= n; j ++)
            for(int k = i; k <= j; k ++)
                pp[k] ++;
    p = n * (n - 1) / 2; 
    //for(int i = 1; i <= n; i ++)
        //cout << pp[i] << " ";
    //cout << endl;
    for(int i = 1; i < n; i ++) {
        for(int j = i + 1; j <= n; j ++) {
            for(int k = i; k <= j; k ++) {
                c.a[j - (k - i)][k] += 1.0 / p;
                //cout << j - (k - i) << " " << k << " " << 1.0 / p << endl;
            }
        }
    }
    for(int i = 1; i <= n; i ++) c.a[i][i] += (p - pp[i]) / p;
    //for(int i = 1; i  <= n; i ++) {
        //for(int j = 1; j <= n; j ++)
            //cout << c.a[i][j] << " ";
        //cout << endl;
    //}
    if(m) {
        for(int i = 1; i <= n; i ++) dp[0][i] = b[i];
        for(int i = 1; i <= m; i ++) {
            bool flag = true;
            for(int j = 1; j <= n; j ++)
                dp[i][j] = 0;
            for(int j = 1; j <= n; j ++)
                for(int k = 1; k <= n; k ++)
                    dp[i][j] += c.a[j][k] * dp[i - 1][k];
            for(int j = 1; j <= n && flag; j ++)
                    if(fabs(dp[i][j] - dp[i - 1][j]) > 1e-6) {
                        flag = false;
                        break;
                    }
            if(flag || i == m) {
                for(int j = 1; j <= n; j ++) a[j] = dp[i][j];
                break;
            }
        }
        /*
        c = pow(m,c);
        for(int i = 1; i <= n; i ++) {
            a[i] = 0;
            for(int j = 1; j <= n; j ++)
                a[i] += c.a[i][j] * b[j];
        }*/
    }
    else {
        for(int i = 1; i <= n; i ++) a[i] = b[i];
    }
    //cout << endl;
    //for(int i = 1; i  <= n; i ++) {
        //for(int j = 1; j <= n; j ++)
            //cout << c.a[i][j] << " ";
        //cout << endl;
    //}    
    //for(int i = 1; i <= n; i ++) cout << a[i] << " ";
    //cout << endl;
    double ans = 0;
    a[0] = 0;
    for(int i = 2; i <= n; i ++) a[i] += a[i - 1];
    for(int i = 1; i <= n; i ++)
        for(int j = i + 1; j <= n; j ++)
            ans += a[j] - a[i - 1];
    p = n * (n - 1) / 2;
    ans /= p;
    printf("%.6lf\n",ans);
}

int main()
{
    //freopen("1.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t --) solve();
    return 0;
}

