#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int n,m;
    int a[110][110],t;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d",&n,&m);
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                scanf("%d",&a[i][j]);
        if(a[n][m]) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}

