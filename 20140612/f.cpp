#include <bits/stdc++.h>
using namespace std;

const int N = 210;
vector<int> v[N];

int mod(int x,int y)
{
    x %= y;
    if(x <= 0) x += y;
    return x;
}

int main()
{
    freopen("factor.in","r",stdin);
    freopen("factor.out","w",stdout);
    int n;
    cin >> n;
    for(int i = 1; i <= 2 * n - 1; i ++) {
        int visit[N * 2];
        memset(visit,0,sizeof(visit));
        visit[2 * n] = 1,visit[i] = 1;
        v[i].push_back(i);
        v[i].push_back(2 * n);
        for(int j = 1; j <= n - 1; j ++) {
            int x = i - j,y = i + j;
            x = mod(x,2 * n - 1);
            y = mod(y,2 * n - 1);
            visit[x] = visit[y] = 1;
            v[i].push_back(x);
            v[i].push_back(y);
        }
    }
    int m;
    int now = 1;
    cin >> m;
    while(m --) {
        int x;
        scanf("%d",&x);
        for(int i = now; i < now + x; i ++) {
            for(int j = 0; j < v[i].size(); j += 2) {
                cout << v[i][j] << " " << v[i][j + 1] << endl;
            }
        }
        cout << endl;
        now += x;
    }
    return 0;
}
