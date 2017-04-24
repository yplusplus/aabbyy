#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <algorithm>
using namespace std;

char s[100010][15];
int f[100010];
int bit[1 << 20];
int change(char c)
{
    if(c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return c - '0';
}

int cal(char *s1,char *s2)
{
    int sum = 0;
    for(int i = 0; i < 5; i ++) {
        int x = change(s1[i]) ^ change(s2[i]);
        sum += bit[x];
    }
    return sum;
}

int main()
{
    bit[0] = 0;
    for (int i = 1; i < 1 << 20; i++) {
        bit[i] = bit[i >> 1] + (i & 1);
    }
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 0; i < n; i ++) {
            scanf("%s",s[i]);
            f[i] = 0;
            for(int j = 0; j < 5; j ++) {
                f[i] = (f[i] << 4) + change(s[i][j]);
            }
            //cout << f[i] << endl;
        } 
        int ans = 20;
        if(n < 1000) {
            for(int i = 0; i < n; i ++)
                for(int j = i + 1; j < n; j ++)
                    ans = min(ans,bit[f[i] ^ f[j]]); 
        }
        else {
            int times = 2000000;
            while(times --) {
                int x = rand() % n;
                int y = rand() % n;
                if(x != y) x = f[x] ^ f[y];
                ans = min(ans,bit[x]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}