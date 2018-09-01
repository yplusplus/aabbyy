#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
#include <string.h>
#include <iostream>

#define pb push_back
#define mp make_pair
#define _cls(a) memset(a,-1,sizeof(a));
#define ll long long

using namespace std;

int n,m,K;

vector< pair<int,ll> > g[100010];

struct Node {
    int u;
    int k;
    ll c;
    Node() {
    }
    Node(int u, int k, ll c):u(u),k(k),c(c){}
};

ll dis[100010][20];

class Prio {
    public:
        bool operator()( const Node &a, const Node &b) {
            return a.c > b.c || a.c == b.c && a.k > b.k;
        }
};

ll bfs() {

    priority_queue< Node, vector<Node>, Prio > q;
    _cls(dis);

    q.push( Node(1,0,0) );
    dis[1][0] = 0;

    while(!q.empty()) {
        Node node = q.top();
        q.pop();

        int u = node.u;
        int k = node.k;
        ll c = node.c;

        if( u == n ) {
            return dis[u][k];
        }

        for(int i = 0; i < g[u].size();++i) {
            int v = g[u][i].first;
            if( dis[v][k] == -1 || dis[v][k] > dis[u][k] + g[u][i].second ) {
                dis[v][k] = dis[u][k] + g[u][i].second;
                q.push(Node(v, k, dis[v][k]));
            }

            if(k<K) {
                if( dis[v][k+1] == -1 || dis[v][k+1] > dis[u][k]) {
                    dis[v][k+1] = dis[u][k];
                    q.push(Node(v, k+1, dis[v][k+1]));
                }
            }
        }
    }

    return -1;
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        cin>>n>>m>>K;
        for(int i = 0; i <=n;++i) {
            g[i].clear();
        }
        for(int i = 0; i < m; ++i) {
            int u,v;
            ll c;
            cin>>u>>v>>c;
            g[u].push_back(mp(v,c));
        }

        ll c = bfs();
        cout<<c<<endl;
        for(int i = 0; i <=n;++i) {
            g[i].clear();
        }
    }
}
