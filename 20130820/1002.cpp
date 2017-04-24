#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

#define MAXN 44
queue<int> que;
bool g[MAXN][MAXN], visit[MAXN], inblossom[MAXN];
int match[MAXN], pre[MAXN], base[MAXN];
int ok[MAXN];
int findancestor(int u, int v) {
    bool inpath[MAXN];
    memset(inpath, false, sizeof(inpath));
    while(1) {
        u = base[u];
        inpath[u] = true;
        if(match[u] == -1) break;
        u = pre[match[u]];
    }
    while(1) {
        v = base[v];
        if(inpath[v]) return v;
        v = pre[match[v]];
    }
}
void reset(int u,int anc) {
    while(u != anc) {
        int v=match[u];
        inblossom[base[u]] = inblossom[base[v]] = true;
        v = pre[v];
        if(base[v] != anc) pre[v] = match[u];
        u = v;
    }
}
void contract(int u,int v,int n) {
    int anc = findancestor(u,v);
    memset(inblossom, 0, sizeof(inblossom));
    reset(u, anc), reset(v, anc);
    if(base[u] != anc) pre[u] = v;
    if(base[v] != anc) pre[v] = u;
    for(int i = 1; i <= n; i++)
        if(inblossom[base[i]]) {
            base[i] = anc;
            if(!visit[i]) {
                que.push(i);
                visit[i] = 1;
            }
        }
}
bool bfs(int S,int n) {
    for(int i = 0; i <= n; i++) pre[i] = -1, visit[i] = 0, base[i] = i;
    while(!que.empty()) que.pop();
    que.push(S);
    visit[S]=1;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(int v = 1; v <= n; v++) {
            if(ok[v] && g[u][v] && base[v] != base[u] && match[u] != v) {
                if(v == S || (match[v] != -1 && pre[match[v]] != -1)) contract(u,v,n);
                else if(pre[v] == -1) {
                    pre[v] = u;
                    if(match[v] != -1) que.push(match[v]), visit[match[v]] = 1;
                    else {
                        u = v;
                        while(u != -1) {
                            v = pre[u];
                            int w = match[v];
                            match[u] = v, match[v] = u;
                            u = w;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
int Match(int n) {
    memset(match, -1, sizeof(match));
    //if (e.fi != -1) match[e.fi] = e.se;
    //if (e.se != -1) match[e.se] = e.fi;
    int ans = 0;
    //cout << e.fi << " " << e.se << endl;
    for(int i = 1; i <= n; i++) {
        //cout << "i = " << i << endl;
        if(ok[i] && match[i] == -1 && bfs(i, n)) ans++;
    }
    return ans;
}

pii et[133];
int n, m;
int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(g, false, sizeof(g));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            g[a][b] = true;
            g[b][a] = true;
            et[i] = mp(a, b);
        }
        memset(ok, true, sizeof(ok));
        int cnt = Match(n);
        vector<int> vec;
        for (int i = 0; i < m; i++) {
            ok[et[i].fi] =ok[et[i].se] = false;
            int tmp = Match(n);
            if (tmp < cnt - 1) vec.pb(i);
            ok[et[i].fi] =ok[et[i].se] = true;
        }
        if (vec.empty()) {
            puts("0");
            puts("");
        } else {
            printf("%d\n", vec.size());
            for (int i = 0; i < vec.size(); i++) {
                printf("%d%c", vec[i] + 1, i == vec.size() - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}

