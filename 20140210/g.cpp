#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int pre[N],dep[N],mid[N];
vector<int> v[N];
struct point
{
	int height;
	vector<int> v;
	void read() {
		scanf("%d",&height);
		height += N;
		int x,y;
		scanf("%d",&x);
		while(x --) {
			scanf("%d",&y);
			v.push_back(y);
		}
	}
	friend bool operator < (const point &p,const point &q) {
		return p.height > q.height;
	}
}a[N];

map<int,int> ma;
set<int> st[N];
int times = 0;
int ans[N];
bool flag[N];
int n;

int find(int x)
{
	if(pre[x] == -1) return x;
	return pre[x] = find(pre[x]);
}

bool cmp(int x,int y)
{
	return mid[x] < mid[y];
}

void dfs(int u)
{
	sort(v[u].begin(),v[u].end(),cmp);
	if(u <= n) ans[++ times] = u;
	for(int i = 0; i < v[u].size(); i ++)
		dfs(v[u][i]);
}

int main()
{
	int m,r;
	scanf("%d%d%d",&n,&m,&r);
	for(int i = 1; i <= m; i ++) 
		a[i].read();
	sort(a + 1,a + m + 1);
	for(int i = 1; i < N; i ++) {
		pre[i] = -1;
		mid[i] = i;
	}
	++ m;
	a[m].height = N - 5;
	for(int i = 1; i <= n; i ++) a[m].v.push_back(i);
	sort(a + 1,a + m + 1);
	int tmp = n + 1;
	for(int i = 1; i <= m; i ++) {
		if(!ma.count(a[i].height)) {
			ma[a[i].height] = ++ tmp;
		}
	}
//	for(int i = 1; i <= m; i ++)
//		cout << ma[a[i].height] << endl;
	for(int i = 1; i <= m; i ++) {
		int id = ma[a[i].height];
		for(int j = 0; j < a[i].v.size(); j ++) {
			int x = find(a[i].v[j]);
			int y = find(id);
		//	cout << x << " " << y << endl;
			if(x == y) continue;
			if(st[y].count(x)) continue;
			st[y].insert(x);
			pre[x] = y;
			v[y].push_back(x);
			mid[y] = min(mid[y],mid[x]);
		}
	}
	//cout << "over" << endl;
	dfs(ma[a[m].height]);
	while(r --) {
		int x;
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
