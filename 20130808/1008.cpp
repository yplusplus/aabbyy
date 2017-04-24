#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[1000010];

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        scanf("%s",s);
        int tot = 0;
        int sum = 0;
        for(int i = 0; s[i]; i ++) {
           if(s[i] == 'M') tot ++;
           else if(s[i] == 'I') sum ++;
           else sum += 3;
        }
        if(tot != 1 || s[0] != 'M') {
            printf("No\n");
            continue;
        }
        if(sum & 1) {
            if(sum == 1) printf("Yes\n");
            else printf("No\n");
            continue;
        }
        int x = sum % 6;
        if(x == 2 || x == 4) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

