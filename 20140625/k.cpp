#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int oo = 1000000000;
vector<int> v[N];
struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
}res[N],a[N],b[N],c[N];

bool cmp(const point &p,const point &q)
{
	if(p.x != q.x) return p.x < q.x;
	return p.y > q.y;
}

bool cmp2(const point &p,const point &q)
{
	return p.x > q.x;
}

bool cmp3(const point &p,const point &q)
{
	return p.y < q.y;
}

int L[N],P[22][N];
bool visit[N];

void init_lca(int m)
{
	for(int i = 1; (1 << i) <= m; i ++)
		for(int j = 1; j <= m; j ++)
			if(P[i - 1][j] != -1) P[i][j] = P[i - 1][P[i - 1][j]];
}

int query(int p,int D)
{
	if(a[p].y + 1 >= D) return 1;
	int tmp = p;
	for(int i = 20; i >= 0; i --)
		if(P[i][p] != -1) {
			int x = P[i][p];
			if(a[x].y + 1 < D) p = x;
		}
	int x = P[0][p];
	//if(tmp == 2 && D == 80) cout << x << endl;
	if(x == -1) return oo - 1;
	//if(tmp == 2 && x == 4) cout << L[tmp] << " " << L[x] << endl;
	return a[x].y + 1 >= D ? L[tmp] - L[x] + 1 : oo - 1;
}

void dfs(int u,int pre)
{
	visit[u] = 1;
	P[0][u] = pre;
	for(int i = 0; i < v[u].size(); i ++) {
		int x = v[u][i];
		if(!visit[x]) {
			L[x] = L[u] + 1;
			dfs(x,u);
		}
	}
}

int nxt[N];
int solve(int n,int m)
{
	if(n == 0) return oo;
	if(a[1].x != 1) return oo;
	if(a[n].y != m) return oo;
	int tmp = 1;
	int ans = 1;
	while(1) {
		if(a[tmp].y == m) return ans;
		if(nxt[tmp] <= tmp) return oo;
		tmp = nxt[tmp];
		ans ++;
	}
}

int main()
{
	memset(P,-1,sizeof(P));
	int c1 = 0,c2 = 0;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; i ++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(x <= y) {
			a[++ c1] = point(x,y);
		}
		else {
			b[++ c2] = point(y,x);
			c[c2] = b[c2];
		}
	}
	sort(a + 1,a + c1 + 1,cmp);
	sort(b + 1,b + c2 + 1,cmp2);
	sort(c + 1,c + c2 + 1,cmp3);
	int maxn = -1,cc = 0;
	for(int i = 1; i <= c1; i ++) {
		if(a[i].y > maxn) res[++ cc] = a[i],maxn = max(maxn,a[i].y);
	}
	c1 = cc;
	for(int i = 1; i <= cc; i ++) a[i] = res[i];
	for(int i = 1; i <= c1; i ++) {
		int lt = i + 1,rt = c1,mid,ans = -1;
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			if(a[mid].x <= a[i].y + 1) ans = mid,lt = mid + 1;
			else rt = mid - 1;
		}
		if(ans != -1) v[ans].push_back(i);
		nxt[i] = ans;
	}
	for(int i = c1; i >= 1; i --)
		if(!visit[i]) dfs(i,i);
	init_lca(c1);
	int ans = oo;
	for(int i = 1; i <= c2; i ++) {
		int lt = 1,rt = c1,mid,id = -1;
		if(b[i].x + 1 == b[i].y) {
			ans = 1;
			continue;
		}
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			if(a[mid].x <= b[i].x + 1) id = mid,lt = mid + 1;
			else rt = mid - 1;
		}
		if(id == -1) continue;
	//	cout << b[i].x << " " << b[i].y << " " << a[id].x << " " << a[id].y << " " << a[4].x << " " << a[4].y  << endl;
		int tmp = query(id,b[i].y);
		ans = min(ans,tmp + 1);
	}
	ans = min(ans,solve(c1,n));
	int ansx = 0,ansy = n + 1;
	for(int i = 1; i <= c2; i ++) {
		ansx = max(ansx,b[i].x);
		ansy = min(ansy,b[i].y);
	}
	if(ansx + 1 >= ansy) ans = min(ans,2);
	int id = -1;
	for(int i = 1; i <= c1; i ++) {
		if(a[i].x <= ansx + 1) {
			id = i;
		}
	}
	if(id != -1) ans = min(ans,2 + query(id,ansy));
	if(ans >= 100000000) printf("impossible\n");
	else printf("%d\n",ans);
	return 0;
}
