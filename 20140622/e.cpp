#include <bits/stdc++.h>
using namespace std;

long long state[110];

void solve()
{
    int m,n;
    scanf("%d%d",&m,&n);
    int a[10];
    memset(a,0,sizeof(a));
    for(int i = 0; i < n; i ++) {
        long long x,y,z;
        scanf("%lld%lld%lld%*d",&x,&y,&z);
        if(!x || !y || !z) a[0] = 1;
        else if(abs(x) > m || abs(y) > m || abs(z) > m) a[1] = 1;
        else if(abs(x) == abs(y) || abs(x) == abs(z) || abs(y) == abs(z)) a[2] = 1;
        else {
            state[i] = 0;
            int xx,yy,zz;
            if(x < 0) xx = m + abs(x) - 1;
            else xx = x - 1;
            if(y < 0) yy = m + abs(y) - 1;
            else yy = y - 1;
            if(z < 0) zz = m + abs(z) - 1;
            else zz = z - 1;
            state[i] = (1LL << xx) | (1LL << yy) | (1LL << zz);
        }
    }
    if(a[0]) {
        puts("INVALID: NULL RING");
        return;
    }
    if(a[1]) {
        puts("INVALID: RING MISSING");
        return;
    }
    if(a[2]) {
        puts("INVALID: RUNE CONTAINS A REPEATED RING");
        return;
    }
    bool flag = false;
    //for(int i = 0; i < 8; i ++)
        //cout << state[i] <<  " ";
    //cout << endl;
    for(int i = 0; i < (1 << m); i ++) {
        long long x = 0;
        for(int j = 0; j <m; j ++)
            if(i & (1 << j)) x |= (1 << j);
            else x |= (1LL << (j + m));
        bool f = true;
        for(int j = 0; j < n; j ++)
            if((state[j] & x))continue;
            else {
                f = false;
                break;
            }
        if(f) {
            flag = true;
            break;
        }
    }
    if(flag) printf("RUNES SATISFIED!\n");
    else printf("RUNES UNSATISFIABLE! TRY ANOTHER GATE!\n");
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) solve();
    return 0;
}
/*
3 8
3 1 2 0
3 -1 2 0
3 1 -2 0
3 -1 -2 0
2 1 -3 0
-2 1 -3 0
-1 2 -3 0
-1 -2 -3 0
*/

