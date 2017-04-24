#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned long long ll;
const int N = 100010;

struct tree
{
	int lt,rt,pos;
	long long cost,val,flag;
}a[N * 4];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].cost = a[step].val = a[step].flag = 0;
	a[step].pos = lt;
	if(lt == rt) return;
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void down(int step)
{
	if(!a[step].flag) return;
	a[2 * step].flag += a[step].flag;
	a[2 * step].val -= a[step].flag;
	a[2 * step + 1].flag += a[step].flag;
	a[2 * step + 1].val -= a[step].flag;
	a[step].flag = 0;
}

void update(int step)
{
	a[step].val = min(a[2 * step].val,a[2 * step + 1].val);
	if(a[2 * step].cost <= a[2 * step + 1].cost) {
		a[step].cost = a[2 * step].cost;
		a[step].pos = a[2 * step].pos;
	}
	else {
		a[step].cost = a[2 * step + 1].cost;
		a[step].pos = a[2 * step + 1].pos;
	}
}

void set(int pos,int step,long long val,long long cost)
{
	if(a[step].lt == a[step].rt) {
		a[step].val = val;
		a[step].cost = cost;
		return;
	}
	down(step);
	if(pos <= a[2 * step].rt) set(pos,2 * step,val,cost);
	else set(pos,2 * step + 1,val,cost);
	update(step);
}

void dec(int lt,int rt,int step,long long val)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		a[step].val -= val;
		a[step].flag += val;
		return;
	}
	down(step);
	if(rt <= a[2 * step].rt) dec(lt,rt,2 * step,val);
	else if(lt > a[2 * step].rt) dec(lt,rt,2 * step + 1,val);
	else {
		dec(lt,a[2 * step].rt,2 * step,val);
		dec(a[2 * step + 1].lt,rt,2 * step + 1,val);
	}
	update(step);
}

long long query_cost(int lt,int rt,int step,int &pos)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		pos = a[step].pos;
		return a[step].cost;
	}
	down(step);
        if(rt <= a[2 * step].rt) return query_cost(lt,rt,2 * step,pos);
        else if(lt > a[2 * step].rt) return query_cost(lt,rt,2 * step + 1,pos);
	else {
		int pos1,pos2;
		long long cost1 = query_cost(lt,a[2 * step].rt,2 * step,pos1);
		long long cost2 = query_cost(a[2 * step + 1].lt,rt,2 * step + 1,pos2);
		if(cost1 <= cost2) pos = pos1;
		else pos = pos2;
		return min(cost1,cost2);
	}
}

long long query_val(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step].val;
	down(step);
	if(rt <= a[2 * step].rt) return query_val(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query_val(lt,rt,2 * step + 1);
	else {
		long long v1 = query_val(lt,a[2 * step].rt,2 * step);
		long long v2 = query_val(a[2 * step + 1].lt,rt,2 * step + 1);
		return min(v1,v2);
	}
}

void read(long long &x)
{
	char c;
	while(1) {
		c = getchar();
		if(isdigit(c)) break;
	}
	x = c - '0';
	while(1) {
		c = getchar();
		if(isdigit(c)) x = 10 * x + (c - '0');
		else return;
	}
}

int main()
{
	int t,n,m;
	long long x,y,z;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		init(1,n,1);
		bool flag = true;
		long long ans = 0;
		int pos = 1;
		for(int i = 1; i <= n; i ++) {
			read(x);
			read(y);
			read(z);
			if(!flag) continue;
			if(x * y > m) {
				flag = false;
				continue;
			}
			if(i == 1) {
				ans += x * y * z;
				set(1,1,m - x * y,z);
				continue;
			}
			long long need = x * y;
			while(need && pos < i) {
				long long val = query_val(pos,i - 1,1);
				if(val == 0) {
					pos ++;
					if(pos == i) break;
					continue;
				}
				int p;
				long long cost = query_cost(pos,i - 1,1,p);
				if(cost > z) break;
				val = query_val(p,i - 1,1);
				if(val >= need) {
					val -= need;
					ans += need * cost;
					dec(p,i - 1,1,need);
					need = 0;
				}
				else {
					need -= val;
					ans += val * cost;
					dec(p,i - 1,1,val);
					pos = p + 1;
				}
			}
			ans += need * z;
			set(i,1,m - x * y,z);
		}
		if(!flag) printf("Impossible\n");
        else cout << ans << endl;
		//else printf("%lld\n",ans);
	}
	return 0;
}
