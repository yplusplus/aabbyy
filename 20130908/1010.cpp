#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1500010;
int pri[10000010];
bool a[N];
int tot;
void prime()
{
    memset(a,false,sizeof(a));
    for(int i = 2; i * i < N; i ++)
        if(!a[i])
            for(int j = i * i; j < N;j += i)
                a[j] = true;
    tot = 0;
    for(int i = 0, j = 2; j < N; j ++)
        if(!a[j]) pri[tot ++] = j;
}

int visit[1000010];
int ansx[1000010],ansy[1000010];
int main()
{
    prime();
    memset(visit,0,sizeof(visit));
    visit[1] = 1;
    
    //cout << "yes" << endl;
    //cout << tot << endl;
    for(int i = 2; i <= 1000000; i += 2) {
        bool flag = false;
        //int pos = lower_bound(pri,pri + tot,i) - pri;
        for(int j = 0; j < tot; j ++) {
            if(!a[pri[j] + i]) {
                ansx[i] = pri[j];
                ansy[i] = pri[j] + i;
                flag = true;
                break;
            }
        }
        if(!flag) cout << "fuck : " << i << endl;
    }
    //cout << "over" << endl;
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        if(n == 0) printf("2 2\n");
        else if(n > 0) printf("%d %d\n",ansy[n],ansx[n]);
        else printf("%d %d\n",ansx[-n],ansy[-n]);
    }
    return 0;
}