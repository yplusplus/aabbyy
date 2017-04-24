#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
struct poly
{
    long double a[N];
    poly() {
        memset(a,0,sizeof(a));
    }
    
    poly operator + (poly &p) {
        poly c;
        for(int i = 0; i < N; i ++)
            c.a[i] = a[i] + p.a[i];
        return c;
    }
    
    poly operator * (poly &p) {
        poly c;
        for(int i = 0; i < N / 2; i ++)
            for(int j = 0; j < N / 2; j ++)
                c.a[i + j] += a[i] * p.a[j];
        return c;
    }
    
    poly operator - (poly &p) {
        poly c;
        for(int i = 0; i < N; i ++)
            c.a[i] = a[i] - p.a[i];
        return c;
    }
};

char s[110];
int pos;

poly dfs()
{
    if(s[pos] == 'x') {
        poly ans;
        ans.a[1] = 1.0;
        pos ++;
        return ans;
    }
    char opt = s[pos ++];
    poly L = dfs();
    poly R = dfs();
    if(opt == 'm') {
        poly tmp = L + R;
        poly temp = L * R;
        return tmp - temp;
    }//return (L + R) - (L * R);
    else return L * R;
}

void solve()
{
    scanf("%s",s);
    pos = 0;
    poly ans = dfs();
    long double sum = 0;
    for(int i = 1; i < N; i ++)
        sum += ans.a[i] * i / (i + 1);
    printf("%.20Lf\n",sum);
    //cout << sum << endl;
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
