#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int a[5010][5010],b[5010];
struct point
{
    char s[35];
    int id;
    void read() {
        cin >> s >> id;
    }
}c[5010];


void process(int id,int n,int m)
{
    set<int> st;
    map<int,int> ma;
    st.insert(id);
    for(int i = 1; i <= a[id][0]; i ++)
        st.insert(a[id][i]);
    ma[b[id]] ++;
    for(int i = 1; i <= n; i ++) {
        if(i == id) continue;
        if(!st.count(i)) continue;
        int tot = 0;
        for(int j = 1; j <= a[i][0]; j ++)
            if(st.count(a[i][j])) tot ++;
        if(tot < m - 1) continue;
        ma[b[i]] ++;
    }
    for(map<int,int>::iterator it = ma.begin(); it != ma.end(); it ++)
        cout << it->first << " " << it->second << endl;
}   
    
int main()
{
    int cas = 0;
    ios::sync_with_stdio(0);
    int n,m,x;
    while(cin >> m >> n) {
        if(!n && !m) break;
        for(int i = 1; i <= m; i ++) c[i].read();
        for(int i = 1; i <= n; i ++) {
            cin >> x;
            cin >> b[x];
            cin >> a[x][0];
            for(int j = 1; j <= a[x][0]; j ++)
                cin >> a[x][j];
        }
        cout << "Case " << ++ cas << ":" << endl;
        for(int i = 1; i <= m; i ++) {
            cout << c[i].s << endl;
            process(c[i].id,n,n / m);
        }
    }
    return 0;
}

