#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[110][10010];
char str[20010];

bool check(int n)
{
    for(int i = 0; i < n; i ++)
        if(str[i] != str[n - i - 1]) return false;
    return true;
}

void solve(int n)
{
    for(int i = 0; i < n;  i++)
        for(int j = 0; j < n; j ++)
            if(i != j) {
                strcpy(str,s[i]);
                strcat(str,s[j]);
                if(check(strlen(str))) {
                    printf("%s\n",str);
                    return;
                }
            }
    printf("0\n");
}

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 0; i < n; i ++)
            scanf("%s",s[i]);
        solve(n);
    }
    return 0;
}


