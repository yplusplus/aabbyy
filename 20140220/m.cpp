#include <bits/stdc++.h>
using namespace std;

stack<int> sta;

void solve(int n,int m)
{
    long long ans = 0;
    int x;
    while(!sta.empty()) sta.pop();
    for(int i = 1; i <= n; i ++) {
        sta.push(i);
        scanf("%d",&x);
        while(!sta.empty() && ans < x) {
            int nowL = m + (int)sta.size() - 1;
            ans += nowL  - (i - sta.top());
            sta.pop();
        }
        if(ans < x) {
            for(int j = i + 1; j <= n; j ++)
                scanf("%*d");
            cout << "Myon" << endl;
            return;
        }
        ans -= x;
    }
    while(!sta.empty() && m + (int)sta.size() - 1 - (n - sta.top()) >= 0) {
        ans += m + (long long)sta.size() - 1 - (n - sta.top());
        sta.pop();
    }
    cout << ans << endl;
}

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF) {
        solve(n,m);
    }
    return 0;
}

