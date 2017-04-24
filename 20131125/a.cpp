#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long oo = 1LL << 62;
const int N = 5010;
int nxt[N],a[N],c[N][6],f[6][N],P[N],period[N];

void read(int &x)
{
    char c;
    while(1) {
        c = getchar();
        if(isdigit(c)) break;
    }
    x = c - '0';
    while(1) {
        c = getchar();
        if(isdigit(c)) x = 10 * x + (c - '0');
        else break;
    }
}

long long x,y;
long long ex_gcd(long long a,long long b)
{
    if(!b) {
        x = 1,y = 0;
        return a;
    }
    long long d = ex_gcd(b,a % b);
    long long tmp = x;
    x = y;
    y = tmp - (a / b) * y;
    return d;
}

long long ival(long long p,long long q)
{
    p %= q;
    if(p <= 0) p += q;
    return p;
}

long long solve(long long a[],long long b[],long long m)
{
    long long ans = b[1],lcm = a[1];
    for(int i = 2; i <= m; i ++) {
        long long d = ex_gcd(lcm,a[i]);
        if((b[i] - ans) % d) return oo;
        x *= ((b[i] - ans) / d);
        x = ival(x,a[i] / d);
        ans = ival(ans + lcm * x,lcm / d * a[i]);
        lcm = lcm / d * a[i];
    }
    return ans;
}

    
int main()
{
    int n;
    while(read(n),n != 0) {
        for(int i = 1; i <= 5 * n; i ++) read(a[i]);
        int ct = 0;
        for(int i = 1; i <= n; i ++) {
            c[i][1] = ++ ct;
            c[i][2] = ++ ct;
        }
        for(int i = 1; i <= n; i ++) {
            c[i][3] = ++ ct;
            c[i][4] = ++ ct;
        }
        for(int i = 1; i <= n; i ++) c[i][5] = ++ ct;
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= 5; j ++) {
                nxt[c[i][j]] = 5 * (i - 1) + j;
            }
        }
        for(int i = 0; i <= 5; i ++)
            for(int j = 0; j <= 5 * n; j ++)
                f[i][j] = -1;
        for(int i = 1; i <= 5 * n; i ++) {
            if(a[i] <= 5) {
                P[a[i]] = i;
                int pos = i;
                ct = 0;
                while(1) {
                    if(f[a[i]][pos] != -1) break;
                    f[a[i]][pos] = ct ++;
                    pos = nxt[pos];
                }
                period[a[i]] = ct;
            }
        }
        long long mix = oo;
        int id;
        for(int i = 1; i <= n; i ++) {
            long long X[6],Y[6];
            int tmp[6];
            for(int j = 1; j <= 5; j ++) tmp[j] = 5 * (i - 1) + j;
            do {
                bool flag = true;
                for(int j = 1; j <= 5; j ++) {
                    if(f[j][tmp[j]] == -1) {
                        flag = false;
                        continue;
                    }
                    X[j] = period[j];
                    Y[j] = f[j][tmp[j]];
                }
                if(flag) {
                    long long tt = solve(X,Y,5);
                    if(tt < mix) {
                        mix = tt;
                        id = i;
                    }
                }
            }while(next_permutation(tmp + 1,tmp + 6));
        }
        if(mix == oo) printf("Neverending game.\n");
        else {
            printf("Player %d wins game number ",id);
            cout << max(1LL,mix) << "." << endl;
        }
    }
    return 0;
}

