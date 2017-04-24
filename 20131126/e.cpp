#include <bits/stdc++.h>
using namespace std;

map<int,int> ma[45];

void init(int id)
{
    int n;
    cin >> n;
    for(int i = 2; i * i <= n; i ++) {
        if(n % i) continue;
        while(n % i == 0) ma[id][i] ++, n /= i;
    }
    if(n > 1) ma[id][n] = 1;
}

int main()
{
    int t,n,a,b;
    cin >> t;
    while(t --) {
        cin >> n;
        for(int i = 0; i < 45; i ++) ma[i].clear();
        init(1);
        init(2);
        ++ n;
        for(int i = 3; i <= n; i ++) {
            for(map<int,int>::iterator it = ma[i - 1].begin(); it != ma[i - 1].end(); it ++)
                ma[i][it->first] = it->second;
            for(map<int,int>::iterator it = ma[i - 2].begin(); it != ma[i - 2].end(); it ++)
                ma[i][it->first] += it->second;
        }
        for(map<int,int>::iterator it = ma[n].begin(); it != ma[n].end(); it ++)
            cout << it->first << " " << it->second << endl;
        cout << endl;
    }
    return 0;
}

