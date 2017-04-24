#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 200010;
const long long oo = -(1LL << 60);
struct tree
{
	int lt,rt;
	long long val;
}a[N * 4];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].val = oo;
	if(lt == rt) return;
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void insert(int pos,int step,long long val)
{
	if(a[step].lt == a[step].rt) {
		a[step].val = max(a[step].val,val);
		return;
	}
	if(pos <= a[2 * step].rt) insert(pos,2 * step,val);
	else insert(pos,2 * step + 1,val);
	a[step].val = max(a[2 * step].val,a[2 * step + 1].val);
}

long long query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		return a[step].val;
	}
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
	else return max(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

void init2(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].val = -oo;
	if(lt == rt) return;
	int mid = (lt + rt) / 2;
	init2(lt,mid,2 * step);
	init2(mid + 1,rt,2 * step + 1);
}

void insert2(int pos,int step,long long val)
{
	if(a[step].lt == a[step].rt) {
		a[step].val = min(a[step].val,val);
		return;
	}
	if(pos <= a[2 * step].rt) insert2(pos,2 * step,val);
	else insert2(pos,2 * step + 1,val);
	a[step].val = min(a[2 * step].val,a[2 * step + 1].val);
}

long long query2(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		return a[step].val;
	}
	if(rt <= a[2 * step].rt) return query2(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query2(lt,rt,2 * step + 1);
	else return min(query2(lt,a[2 * step].rt,2 * step),query2(a[2 * step + 1].lt,rt,2 * step + 1));
}

struct point
{
	int id,x,y;
	point() {}
	point(int id,int x,int y):id(id),x(x),y(y) {}
}p1[N],p2[N];

bool cmp(const point &p,const point &q)
{
	return p.x > q.x;
};

bool cmp2(const point &p,const point &q) {
	return p.x < q.x;
}

struct node
{
	int x,y;
	long long val;
	node() {}
	node(int x,int y,long long val):x(x),y(y),val(val) {}
}e1[N],e2[N];

bool cmpx(const node &p,const node &q) 
{
	return p.x > q.x;
}

bool cmpy(const node &p,const node &q) {
	return p.x < q.x;
}

long long sum[N],ans[N];

void solve_positive(int n,int c,int d)
{
	sort(e1,e1 + c,cmpx);
	sort(p1,p1 + d,cmp);
	init(1,n,1);
	for(int i = 0,j = 0; i < d; i ++) {
		while(j < c && e1[j].x >= p1[i].x) {
			insert(e1[j].y,1,e1[j].val);
			j ++;
		}
		long long val = query(p1[i].x,p1[i].y,1);
		if(val < 0) val = 0;
		ans[p1[i].id] = sum[p1[i].y] - sum[p1[i].x] - val;
	//	printf("%lld\n",ans[p1[i].id]);
	}

}


void solve_negative(int n,int c,int d)
{
	sort(e2,e2 + c,cmpy);
	sort(p2,p2 + d,cmp2);
	init2(1,n,1);
	for(int i = 0, j = 0; i < d; i ++) {
		while(j < c && e2[j].x <= p2[i].x) {
			insert2(e2[j].y,1,e2[j].val);
			j ++;
		}
		long long val = query2(p2[i].y,n,1);
		if(val == -oo) ans[p2[i].id] = -1;
		else ans[p2[i].id] = val - (sum[p2[i].y] - sum[p2[i].x]);
	//	printf("%lld\n",ans[p1[i].id]);
	}
}

int main()
{
	int n,m,r,x,y,z;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 0; i <= n; i ++) sum[i] = 0;
		for(int i = 2; i <= n; i ++) scanf("%lld",&sum[i]);
		for(int i = 2; i <= n; i ++)
			sum[i] += sum[i - 1];
		int c1 = 0,c2 = 0;
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			if(x <= y) {
				e1[c1 ++] = node(x,y,sum[y] - sum[x] - z);
			}
			else e2[c2 ++] = node(y,x,sum[x] - sum[y] + z);
		}
		int d1 = 0,d2 = 0;
		scanf("%d",&r);
		for(int i = 1; i <= r; i ++) {
			scanf("%d%d",&x,&y);
			if(x <= y) p1[d1 ++] = point(i,x,y);
			else p2[d2 ++] = point(i,y,x);
		}
		solve_positive(n,c1,d1);
		solve_negative(n,c2,d2);
		for(int i = 1; i <= r; i ++)
			printf("%lld\n",ans[i]);
	}
	return 0;
}
