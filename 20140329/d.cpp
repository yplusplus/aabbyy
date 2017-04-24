#include <bits/stdc++.h>
using namespace std;

const long long inf = 1LL << 60;
const int maxn = 50005, maxm = 500005;
int n, m, s, l, co, co2, head[maxn], head2[maxn], a[maxn], tt[maxn];
long long d[maxn], d2[maxn];

struct e
{
    int v, w, next;
}edge[maxm], edge2[maxm];

void add(int u, int v, int w)
{
    edge[co].v = v;
    edge[co].w = w;
    edge[co].next = head[u];
    head[u] = co++;
}

void add2(int u, int v, int w)
{
    edge2[co2].v = v;
    edge2[co2].w = w;
    edge2[co2].next = head2[u];
    head2[u] = co2++;
}


bool visit[maxn];

void spfa(long long dist[], int eh[], e edge[], int s, int flag) {
	for (int i = 1; i <= n; i++) dist[i] = inf;
	memset(visit, 0, sizeof(visit));
	dist[s] = 0;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		visit[u] = false;
		for (int i = eh[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			long long tmp = dist[u] + edge[i].w;
			if (flag == 0) tmp += tt[u];
			else tmp += tt[v];
			if (dist[v] > tmp) {
				dist[v] = tmp;
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	//for (int i = 1; i <= n; i++) { cout << dist[i] << " "; } cout << endl; cout << "hello" << endl;
}
 
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        co = co2 = 0;
        memset(head, -1, sizeof(head));
        memset(head2, -1, sizeof(head2));
		scanf("%d%d%d%d", &n, &m, &s, &l);
        for (int i = 1; i <= l; i++)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &tt[i]);
        }
        while (m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
            add2(v, u, w);
        }
		spfa(d, head, edge, s, 0);
		spfa(d2, head2, edge2, s, 1);
		long long ans = 0;
		bool found = false;
		for (int i = 1; i <= l; i++) {
			ans += d[a[i]] + d2[a[i]];
			if (d[a[i]] == inf || d2[a[i]] == inf) found = true;
		}
		if (found) puts("Tumblerful");
		else cout << ans << endl;
    }
    return 0;
}

