#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct bignum
{
    int a[N],n;
    void init() {
        char s[100010];
        scanf("%s",s);
        n = strlen(s);
        memset(a,0,sizeof(a));
        for(int i = n - 1; i >= 0; i --)
            a[i] = s[n - i - 1] - '0';
    }

    int inc() {
        a[0] ++;
        for(int i = 0; i < n; i ++) {
            if(a[i] >= 10) {
                a[i + 1] ++;
                a[i] -= 10;
            }
        }
        if(a[n]) n ++;
        int sum = 0;
        for(int i = 0; i < n; i ++) {
            sum += a[i];
            if(sum >= 10) sum -= 10;
        }
        return sum;
    }

    void output() {
        for(int i = n - 1; i >= 0; i --)
            printf("%d",a[i]);
        printf("\n");
    }
}a;

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t --) {
        a.init();
        while(1) {
            int x = a.inc();
            if(!x) {
                a.output();
                break;
            }
        }
    }
    return 0;
}

