#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    scanf("%d",&n);
    long long a[N][N];
    for(int i = 1; i <= n; i ++) {
        for(int j = i + 1; j <= n; j ++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }
    long long lcm[N];
    for(int i = 1; i <= n; i ++) {
        lcm[i] = 1;
        for(int j = 1; j <= n; j ++) {
            if(i == j) continue;
            lcm[i] = lcm[i] / __gcd(lcm[i],a[i][j]) * a[i][j];
        }
    }
    for(int i = 2; i <= n; i ++) {
        for(int j = lcm[i - 1] / lcm[i] + 1; j; j ++) {
            bool flag = true;
            lcm[i] *= j;
            for(int k = 1; k <= n; k ++) {
                if(k == i) continue;
                if(__gcd(lcm[k],lcm[i]) != a[i][k]) {
                    flag = false;
                    break;
                }
            }
            if(flag) break;
            lcm[i] /= j;
        }
    }
    for(int i = 1; i <= n; i ++) cout << lcm[i] << " ";
    cout << endl;
    return 0;
}

