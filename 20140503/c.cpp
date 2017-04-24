#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct tree
{
	int lt,rt;
	long long mx,state;
}a[N * 4];

struct point
{
	long long vol,val,state;
	point() {}
	point(long long vol,long long val,long long state):vol(vol),val(val),state(state) {}
	friend bool operator < (const point &p,const point &q) {
		return p.vol < q.vol;
	}
}c[N];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	if(lt == rt) {
		a[step].mx = c[lt].val;
		a[step].state = c[lt].state;
		return;
	}
	int mid = (lt + rt) >> 1;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	if(a[2 * step].mx >= a[2 * step + 1].mx) a[step].state = a[2 * step].state;
	else a[step].state = a[2 * step + 1].state;
	a[step].mx = max(a[2 * step].mx,a[2 * step + 1].mx);
}

tree query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step];
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
	else {
		tree t1 = query(lt,a[2 * step].rt,2 * step);
		tree t2 = query(a[2 * step + 1].lt,rt,2 * step + 1);
		if(t1.mx >= t2.mx) return t1;
		return t2;
	}
}

int main()
{
	freopen("dowry.in","r",stdin);
	freopen("dowry.out","w",stdout);
	int n;
	long long L,R;
	cin >> n >> L >> R;
	long long b[55],d[55];
	for(int i = 0; i < n; i ++) {
		cin >> b[i] >> d[i];
	}
	if(n <= 16) {
		long long maxn = -1,state = 0;
		for(int i = 0; i < (1 << n); i ++) {
			long long vol = 0,sum = 0;
			for(int j = 0; j < n; j ++) {
				if(i & (1 << j)) {
					vol += b[j];
					sum += d[j];
				}
			}
			if(vol >= L && vol <= R) {
				if(maxn < sum) {
					maxn = sum;
					state = i;
				}
			}
		}
		if(maxn == -1) {
			cout << 0 << endl;
		}
		else {
			int tot = 0;
			for(int j = 0; j < n; j ++)
				if(state & (1 << j)) tot ++;
			cout << tot << endl;
			for(int j = 0; j < n; j ++)
				if(state & (1 << j)) cout << j + 1 << " ";
			cout << endl;
		}
		return 0;
	}
	long long maxn = -1,state = 0;
	for(int i = 0; i < (1 << 16); i ++) {
		c[i].state = i,c[i].vol = c[i].val = 0;
		for(int j = 0; j < 16; j ++)
			if(i & (1 << j))
				c[i].vol += b[j],c[i].val += d[j];
		if(c[i].vol >= L && c[i].vol <= R && maxn < c[i].val) {
			maxn = c[i].val;
			state = i;
		}
	}
	sort(c,c + (1 << 16));
	init(0,(1 << 16) - 1,1);
	for(long long i = 0; i < (1 << (n - 16)); i ++) {
		long long vol = 0,sum = 0;
		for(int j = 0; j < n - 16; j ++) {
			if(i & (1 << j)) {
				vol += b[j + 16];
				sum += d[j + 16];
			}
		}
		if(vol > R) continue;
		int lt = 0,rt = (1 << 16) - 1,mid;
		int x = -1,y = -1;
		while(lt <= rt) {
			mid = (lt + rt) / 2;
			if(vol + c[mid].vol >= L) x = mid,rt = mid - 1;
			else lt = mid + 1;
		}
		lt = 0,rt = (1 << 16) - 1;
		while(lt <= rt) {
			mid = (lt + rt) / 2;
			if(vol + c[mid].vol <= R) y = mid,lt = mid + 1;
			else rt = mid - 1;
		}
		if(x == -1 || x > y) continue;
		tree tmp = query(x,y,1);
		if(tmp.mx + sum > maxn) {
			maxn = tmp.mx + sum;
			state = tmp.state | (i << 16);
		}
	}
	int tot = 0;
	for(int i = 0; i < n; i ++)
		if(state & (1LL << i)) tot ++;
	cout << tot << endl;
	for(int i = 0; i < n; i ++)
		if(state & (1LL << i)) cout << i + 1 << " ";
	cout << endl;
	return 0;
}
