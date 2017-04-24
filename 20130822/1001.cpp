#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
int a[N],b[N];

int main()
{
    int n,m,x;
    while(scanf("%d%d",&n,&m) != EOF) {
        bool flag = false;
        for(int i = 1; i <= n; i ++)
            scanf("%d",&a[i]);
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&b[i]);
            if(b[i] == 1) flag = true;
        }
        while(m --) {
            scanf("%d",&x);
            if(x <= 0) {
                printf("NO\n");
                continue;
            }
            if(flag) printf("YES\n");
            else if(x & 1) printf("NO\n");
            else printf("YES\n");
        }
    }
    return 0;   
}

