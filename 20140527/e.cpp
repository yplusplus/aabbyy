#include <bits/stdc++.h>
using namespace std;

const int N = 155;
struct point
{
	int a[4];
	point() {
		memset(a,0,sizeof(a));
	}
	point(int ta[4]) {
		for(int i = 0; i < 4; i ++) a[i] = ta[i];
	}
	friend bool operator < (const point &p,const point &q) {
		for(int i = 0; i < 4; i ++)
			if(p.a[i] != q.a[i]) return p.a[i] < q.a[i];
		return p.a[0] < q.a[0];
	}
};

int unions(int x,int y)
{
	int high = (x >> 1) & (y >> 1);
	int low = high ^ 1 ^ (x & 1) ^ (y & 1);
	return ((x >> 1) ^ (y >> 1)) * 2 + low;
}

map<point,int> ma;

int dfs(point p)
{
	if(p.a[0] + p.a[1] + p.a[2] + p.a[3] == 1) return 0;
	if(ma.count(p)) return ma[p];
	//for(int i = 0; i < 4; i ++) cout << p.a[i] << " ";
	//cout << endl;
	point q;
	for(int i = 0; i < 4; i ++)
		for(int j = i; j < 4; j ++) {
			q = p;
			q.a[i] --,q.a[j] --;
			if(q.a[i] < 0 || q.a[j] < 0) continue;
			int x = unions(i,j);
			q.a[x] ++;
			if(!dfs(q)) return ma[p] = 1;
		}
	if(p.a[1]) {
		q = p;
		q.a[0] ++,q.a[1] --;
		if(!dfs(q)) return ma[p] = 1;
	}
	if(p.a[3]) {
		q = p;
		q.a[2] ++,q.a[3] --;
		if(!dfs(q)) return ma[p] = 1;
	}
	return ma[p] = 0;
}

int pre[N];
int c[N],b[N];

int find(int x)
{
	if(pre[x] == -1) return x;
	return pre[x] = find(pre[x]);
}

int main()
{
	freopen("points.in","r",stdin);
	freopen("points.out","w",stdout);
	memset(pre,-1,sizeof(pre));
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	if(m == n * (n - 1) / 2) {
		printf("Betty\n");
		return 0;
	}
	for(int i = 1; i <= n; i ++) c[i] = 1;
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d",&x,&y);
		x = find(x);
		y = find(y);
		if(x == y) b[x] ++;
		else {
			c[x] += c[y];
			pre[y] = x;
			b[x] += b[y];
			b[x] ++;
		}
	}
	point p;
	int cnt = 0;
	for(int i = 1; i <= n; i ++)
		if(pre[i] == -1) {
			cnt ++;
			int tot = (c[i] * (c[i] - 1) / 2 - b[i]) & 1;
			p.a[(c[i] & 1) * 2 + tot] ++;
		}
	//for(int i = 0; i < 4; i ++) cout << p.a[i] << " ";
	if(cnt > 1 &&  dfs(p)) printf("Andrew\n");
	else printf("Betty\n");
	return 0;
}
