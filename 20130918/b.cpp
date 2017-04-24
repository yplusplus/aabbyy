#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N =100010;
struct tree
{
	int mx[2],lmx[2],rmx[2];
	int lt,rt,flag;
	int dis() {
		return rt - lt + 1;
	}
}a[N * 4];

int c[N];

void update(tree &p,tree lt,tree rt)
{
	p.lt = lt.lt;
	p.rt = rt.rt;
	for(int i = 0; i < 2; i ++) {
		p.mx[i] = max(lt.mx[i],rt.mx[i]);
		p.mx[i] = max(p.mx[i],lt.rmx[i] + rt.lmx[i]);
		if(lt.lmx[i] == lt.dis()) p.lmx[i] = lt.lmx[i] + rt.lmx[i];
		else p.lmx[i] = lt.lmx[i];
		if(rt.rmx[i] == rt.dis()) p.rmx[i] = rt.rmx[i] + lt.rmx[i];
		else p.rmx[i] = rt.rmx[i];
	}
}

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].flag = 0;
	if(lt == rt) {
		if(c[lt]) {
			a[step].mx[1] = a[step].lmx[1] = a[step].rmx[1] = 1;
			a[step].mx[0] = a[step].lmx[0] = a[step].rmx[0] = 0;
		}
		else {
			a[step].mx[0] = a[step].lmx[0] = a[step].rmx[0] = 1;
			a[step].mx[1] = a[step].lmx[1] = a[step].rmx[1] = 0;
		}
		return;
	}
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	update(a[step],a[2 * step],a[2 * step + 1]);
}

void reverse(int step)
{
	swap(a[step].mx[0],a[step].mx[1]);
	swap(a[step].lmx[0],a[step].lmx[1]);
	swap(a[step].rmx[0],a[step].rmx[1]);
	a[step].flag ^= 1;
}

void down(int step)
{
	reverse(2 * step);
	reverse(2 * step + 1);
	a[step].flag ^= 1;
}

void reverse(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		reverse(step);
		return;
	}
	if(a[step].flag) down(step);
	if(rt <= a[2 * step].rt) reverse(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) reverse(lt,rt,2 * step + 1);
	else {
		reverse(lt,a[2 * step].rt,2 * step);
		reverse(a[2 * step + 1].lt,rt,2 * step + 1);
	}
	update(a[step],a[2 * step],a[2 * step + 1]);
}

tree query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step];
	if(a[step].flag) down(step);
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
	else {
		tree l = query(lt,a[2 * step].rt,2 * step);
		tree r = query(a[2 * step + 1].lt,rt,2 * step + 1);
		tree ans;
		update(ans,l,r);
		return ans;
	}
}

int main()
{
	int n,m,cd,x,y;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) scanf("%d",&c[i]);
		init(1,n,1);
		scanf("%d",&m);
		while(m --) {
			scanf("%d%d%d",&cd,&x,&y);
			if(!cd) {
				tree ans = query(x,y,1);
				printf("%d\n",ans.mx[1]);
			}
			else {
				reverse(x,y,1);
			}
		}
	}
	return 0;
}

