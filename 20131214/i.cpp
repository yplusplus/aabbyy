#include <bits/stdc++.h>
using namespace std;

const int N = 4000010;
int a[N];
bool flag[N];

void prime()
{
    memset(a,0,sizeof(a));
    for(int i = 2; i <= 2000; i ++)
        if(!a[i]) {
            a[i] = i;
            for(int j = i * i; j <= 4000000; j += i)
                a[j] = i;
        }
    for(int i = 2; i <= 4000000; i ++)
        if(!a[i]) a[i] = i;
    a[0] = a[1] = -1;
}
 
bool check(int n)
{
    int ans = 1;
    while(n > 1) {
        int x = a[n],y = 1;
        while(n % x == 0) n /= x,y ++;
        ans *= y;
    }
    return a[ans] == ans;
}
        
void init()
{
    prime();
    for(int i = 2; i <= 4000000; i ++) {
        if(check(i)) flag[i] = true;
    }
}
    
int main()
{
    init();
    int t;
    int n,m;
    scanf("%d",&t);
    while(t --) {
        int tot = 0;
        scanf("%d%d",&n,&m);
        for(int i = n; i <= m; i ++) {
            if(flag[i]) tot ++;
        }
        if(!tot) printf("-1\n");
        else {
            for(int i = n; i <= m; i ++) {
                if(!flag[i]) continue;
                printf("%d",i);
                tot --;
                if(tot) printf(" ");
                else printf("\n");
            }
        }
    }
    return 0;
}    
    


