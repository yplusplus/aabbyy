#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510;
int sg[N];

int dfs(int u)
{
    if(u < 0) return 0;
    if(sg[u] != -1) return sg[u];
    int visit[N];
    memset(visit,0,sizeof(visit));
    for(int i = 1; i <= u; i ++) {
        visit[dfs(i - 2) ^ dfs(u - i - 1)] = 1;
    }
    for(int i = 0; ; i ++)
        if(!visit[i]) return sg[u] = i;
}
        
int main()
{
    memset(sg,-1,sizeof(sg));
    sg[0] = 0;
    sg[1] = 1;
    sg[2] = 1;
    for(int i = 3; i <= 500; i ++)
        dfs(i);
    
    /*
    for(int i = 1; i <= 34 * 8; i ++) {
        cout << sg[i] << " ";
        if(i % 34 == 0) cout << endl;
    }
    cout << endl;
    
    
    for(int i = 34; i <= 200; i ++)
        if(sg[i] != sg[i - 34]) cout << "fuck :  " << i << endl;
        */
    int n;
    scanf("%d",&n);
    if(n < 200) {
        if(sg[n]) cout << "White" << endl;
        else cout << "Black" << endl;
    }
    else {
        n = n % 136 + 136;
        if(sg[n]) cout << "White" << endl;
        else cout << "Black" << endl;
    }        
    return 0;
}

