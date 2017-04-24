#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
char s[N];
int a[N];

void div2()
{
    int tmp = 0;
    for(int i = N - 1; i >= 0; i --) {
        int temp = (10 * tmp + a[i]) % 2;
        a[i] = (10 * tmp + a[i]) / 2;
        tmp = temp;
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        scanf("%s",s);
        int n = strlen(s);
        memset(a,0,sizeof(a));
        for(int i = 0; i < n; i ++) a[i] = s[n - i - 1] - '0';
        if(a[0] & 1) {
           div2();
        }
        else {
            div2();
            if(a[0] % 2) {
                a[0] -= 2;
            }
            else a[0] --;
            for(int i = 0; i < N; i ++) {
                if(a[i] < 0) {
                    a[i] += 10;
                    a[i + 1] --;
                }
            }
        } 
        int i;
        for(i = N - 1; i >= 0; i --) if(a[i]) break;
        for(i; i >= 0; i --) printf("%d",a[i]);
        printf("\n");
        if(t) printf("\n");
    }
    return 0;
}

