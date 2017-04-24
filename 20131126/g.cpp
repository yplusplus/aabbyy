#include <bits/stdc++.h>
using namespace std;

priority_queue<int> q,qt;

int main()
{
    int t,visit[256];
    char s[10010];
    gets(s);
    sscanf(s,"%d",&t);
    while(t --) {
        gets(s);
        while(!q.empty()) q.pop();
        while(!qt.empty()) qt.pop();
        for(int i = 1; i <= 6; i ++)
            for(int j = 1; j <= 6; j ++)
                qt.push(-(i + j));
        memset(visit,0,sizeof(visit));
        for(int i = 0; s[i]; i ++)
            visit[s[i]] ++;
        for(int i = 0; i < 256; i ++)
            if(visit[i] && i != ' ') q.push(visit[i]);
        int ans = 0;
        while(!q.empty()) {
            int x = q.top();
            int y = -qt.top();
            ans += x * y;
            q.pop();
            qt.pop();
        }
        cout << ans << endl;
    }
    return 0;
}

