#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct tree
{
	int lt,rt;
	int flag,mix,cover;
}a[N << 2];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].flag = 0;
	a[step].mix = 0;
	a[step].cover = 0;
	if(lt == rt) return;
	int mid = (lt + rt) >> 1;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void down(int step)
{
	if(a[step].cover) {
		a[2 * step].cover = a[2 * step + 1].cover = 1;
		a[2 * step].flag = a[2 * step + 1].flag = a[step].flag;
		a[2 * step].mix = a[2 * step + 1].mix = a[step].mix;
		a[step].cover = 0;
	}
}

void modify(int lt,int rt,int step,int val)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		a[step].cover = 1;
		a[step].flag = a[step].mix = val;
		return;
	}
	down(step);
	if(rt <= a[2 * step].rt) modify(lt,rt,2 * step,val);
	else if(lt > a[2 * step].rt) modify(lt,rt,2 * step + 1,val);
	else {
		modify(lt,a[2 * step].rt,2 * step,val);
		modify(a[2 * step + 1].lt,rt,2 * step + 1,val);
	}
	a[step].mix = min(a[2 * step].mix,a[2 * step + 1].mix);
}

int query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step].mix;
	down(step);
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
	else return min(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

struct point
{
	int x,y,z;
	void read() {
		scanf("%d%d%d",&x,&y,&z);
	}
	friend bool operator < (const point &p,const point &q) {
		return p.z < q.z;
	}
}c[N];

int main()
{
	freopen("rmq.in","r",stdin);
	freopen("rmq.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	init(1,n,1);
	for(int i = 1; i <= m; i ++) c[i].read();
	sort(c + 1,c + m + 1);
	for(int i = 1; i <= m; i ++)
		modify(c[i].x,c[i].y,1,c[i].z);
	for(int i = 1; i <= m; i ++) {
		if(query(c[i].x,c[i].y,1) != c[i].z) {
			puts("inconsistent");
			return 0;
		}
	}
	puts("consistent");
	for(int i = 1; i <= n; i ++) {
		printf("%d",query(i,i,1));
		if(i == n) printf("\n");
		else printf(" ");
	}
	return 0;
}
