#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const long long mod = 100000000;
const int N = 155;
const int SIZE = 35;
struct bignum
{
    long long a[SIZE];
    int len;
    bool visit;
    
    void init() {
        memset(a,0,sizeof(a));
        visit = false;
    }
    
    void set() {
        visit = true;
    }
    bignum () {
        memset(a,0,sizeof(a));
        visit = false;
    }
    
    int get_len() {
        for(int i = SIZE - 1;i >= 0; i --) {
            if(a[i]) return i;
        }
        return -1;
    }
            
    void adjust() {
        for(int i = 0; i < SIZE; i ++) {
            if(a[i] >= mod) {
                a[i + 1] += a[i] / mod;
                a[i] %= mod;
            }
        }
    }
    
    bignum operator + (const bignum &p) {
        bignum c;
        for(int i = 0; i < SIZE; i ++) c.a[i] = a[i] + p.a[i];
        c.adjust();
        return c;
    }
    
    bignum operator * (bignum &p) {
        bignum c;
        int len1 = this->get_len();
        int len2 = p.get_len();
        for(int i = 0; i <= len1; i ++)
            for(int j = 0; j <= len2; j ++)
                c.a[i + j] += a[i] * p.a[j];
        c.adjust();
        return c;
    }
    
    bool zero() {
        for(int i = 0; i < SIZE; i ++)
            if(a[i]) return false;
        return true;
    }
    
    void output() {
        int i = SIZE - 1;
        for(i; i >= 0; i --) {
            if(a[i]) break;
        }
        if(i == -1) i ++;
        
        char c = '"';
        cout << c;
        printf("%I64d",a[i]);
        for(i = i - 1; i >= 0; i --) printf("%08I64d",a[i]);
        cout << c << ", ";

    }
    
}dp[N][N],sum[N][N],c[N][N];
bignum f[N][N];

void solve(int n,int m)
{
    if(m == 1) {
        dp[n][m].a[0] = 1;
        return;
    }
    if(n - 1 < m) return;
    for(int i = 0; i <= m; i ++)
        for(int j = 0; j <= n; j ++)
            f[i][j].init();
    f[0][0].a[0] = 1;
    for(int i = 1; i <= m; i ++) {
        for(int j = i; j + (m - i) < n; j ++) {
            if(f[i][j].visit) continue;
            for(int k = 1; k <= j; k ++) {
                if(j - k < i - 1) break;
                f[i][j] = f[i][j] + (f[i - 1][j - k] * c[n - 1 - j + k - 1][k - 1] * sum[k][m]);
            }
            f[i][j].set();
        }
    }
    dp[n][m] = f[m][n - 1];
}

int main()
{
    for(int i = 0; i < N; i ++) {
        c[i][0].a[0] = c[i][i].a[0] = 1;
        for(int j = 1; j < i; j ++) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
    freopen("out.cpp","w",stdout);
    for(int i = 1; i <= 150; i ++) {
        for(int j = 1; j <= 150; j ++) {
            solve(i,j);
            sum[i][j] = sum[i][j - 1] + dp[i][j];
        }
        cerr << i << endl;
        sum[i][i].output();
        //cout <<", ";
    }
    return 0;
}



