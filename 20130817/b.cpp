#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[1010][110];
int len[1010];
char s[110];
int b[110];

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 1; i <= n; i ++) {
            scanf("%s",s + 1);
            len[i] = strlen(s + 1);
            for(int j = 1; j <= len[i]; j ++)
                a[i][j] = s[j] - '0';
        }
        while(m --) {
            scanf("%s",s + 1);
            int r = strlen(s + 1);
            for(int i = 1; i <= r; i ++)
                b[i] = s[i] - '0';
            int id = -1,maxn = -1000000000;
            for(int i = 1; i <= n; i ++) {
                for(int j = 1; j + r - 1 <= len[i]; j ++) {
                    int sum = 0;
                    for(int k = 0; k < r; k ++) {
                        if(a[i][j + k] == b[k + 1]) sum ++;
                        if(r - k - 1 + sum <= maxn) break;
                    }
                    if(sum > maxn) maxn = sum,id = i;
                }
            }
            printf("%d\n",id);
//            cout << maxn << endl;
        }
    }
    return 0;
}


