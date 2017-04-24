#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
int f[100010];

int main()
{
    memset(f,0,sizeof(f));
    f[0] = 1;
    for(int i = 1; i <= 100000; i ++) {
        for(int j = i - 1,add = 2; j >= 0; add ++) {
            if((add / 2) % 2) f[i] += f[j];
            else f[i] -= f[j];
            if(f[i] < 0) f[i] += mod;
            if(f[i] >= mod) f[i] -= mod;
            if(add & 1) j -= add;
            else j -= add / 2;
        }   
    }
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        printf("%d\n",f[n]);
    }
    return 0;
}
            

