#include <bits/stdc++.h>
using namespace std;

struct point
{
	long long x,y;
	void sp() {
		swap(x,y);
	}
	point() {
		x = y = 0;
	}
	point(long long x,long long y):x(x),y(y) {}
};

long long cal(long long n)
{
	long long tot = 0;
	long long tmp = 5;
	while(tmp <= n) {
		tot += n / tmp;
		tmp *= 5;
	}
	return tot;
}

void add(point &p,point q)
{
	p.x += q.x;
	p.y += q.y;
}

map<long long,point> ma;
//[0,n]
point dfs(long long n)
{
	if(ma.count(n)) return ma[n];
	if(n < 5) {
		ma[n] = point(n + 1,0);
		return point(n + 1,0);
	}
	long long ansx = 0,ansy = 0;
	long long tmp = 1;
	while(tmp < n) tmp *= 5;
	if(tmp == n) {
		point p = dfs(n - 1);
		long long x = cal(n);
		if(x & 1) p.y += 1;
		else p.x += 1;
		return ma[n] = p;
	}
	tmp /= 5;
	long long tt = n / tmp;
	point pre;
	long long cc = cal(tmp);
	if(tt) {
		point ret = dfs(tmp - 1);
		if(cc & 1) {
			pre.x = ret.x * ((tt + 1) / 2);
			pre.y = ret.y * ((tt + 1) / 2);
			pre.x += ret.y * (tt / 2);
			pre.y += ret.x * (tt / 2);
		}
		else {
			pre.x = ret.x * tt;
			pre.y = ret.y * tt;
		}
	}
	point ret = dfs(n % tmp);
	if(cc % 2 == 0) add(pre,ret);
	else {
		if(tt & 1) ret.sp();
		add(pre,ret);
	}
	return ma[n] = pre;
}

int main()
{
	long long n;
	while(cin >> n,n != -1) cout << dfs(n).x << endl;
	return 0;
}
