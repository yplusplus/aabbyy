#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 200010;
struct point
{
	int flag;
	double val;
	int x,y,id;
	point() {}
	point(int x,int y,int flag,int id,double val):x(x),y(y),flag(flag),id(id),val(val) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.x != q.x) return p.x < q.x;
		if(p.y != q.y) return p.y < q.y;
		return p.id < q.id;
	}
}a[N];

int init(int n,int m)
{
	int x1,y1,x2,y2;
	double val;
	int ct = 0;
	for(int i = 1; i <= n; i ++) {
		scanf("%d%d%lf",&x1,&y1,&val);
		a[++ ct] = point(x1,y1,-2,0,val);
	}
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		a[++ ct] = point(x1 - 1,y1 - 1,1,i,0.0);
		a[++ ct] = point(x2,y2,1,i,0.0);
		a[++ ct] = point(x1 - 1,y2,-1,i,0.0);
		a[++ ct] = point(x2,y1 - 1,-1,i,0.0);
	}
	return ct;
}

double ans[N];
int numb[N];

double b[N];
int c[N];
int Y[N];

int lowbit(int x)
{
	return x & (-x);
}

void insert(int x,double val)
{
	for(int i = x; i < N; i += lowbit(i)) {
		c[i] ++;
		b[i] += val;
	}
}

void query(int x,double &ansx,int &ansy)
{
	ansx = 0;
	ansy = 0;
	for(int i = x; i > 0; i -= lowbit(i)) {
		ansx += b[i];
		ansy += c[i];
	}
}

int find(int x,int cnt)
{
	int lt = 1,rt = cnt,mid;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(Y[mid] == x) return mid;
		if(Y[mid] > x) rt = mid - 1;
		else lt = mid + 1;
	}
}

void solve(int n)
{
	memset(ans,0,sizeof(ans));
	memset(numb,0,sizeof(numb));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	for(int i = 1; i <= n; i ++)
		Y[i] = a[i].y;
	sort(Y + 1,Y + n + 1);
	int cnt = 1;
	for(int i = 2; i <= n; i ++)
		if(Y[i] != Y[cnt]) Y[++ cnt] = Y[i];
	for(int i = 1; i <= n; i ++)
		a[i].y = find(a[i].y,cnt);
	for(int i = 1; i <= n; i ++) {
		if(a[i].id == 0) {
			insert(a[i].y,a[i].val);
		}
		else {
			double x = 0;
			int y = 0;
			query(a[i].y,x,y);
			ans[a[i].id] += a[i].flag * x;
			numb[a[i].id] += a[i].flag * y;
		}
	}
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		int tot = init(n,m);
		sort(a + 1,a + tot + 1);
		solve(tot);
		for(int i = 1; i <= m; i ++)
			if(fabs(ans[i]) < 0.005) ans[i] = 0;
		for(int i = 1; i <= m; i ++)
			printf("%.2lf/%d\n",ans[i] + 1e-8,numb[i]);
	}
	return 0;
}

