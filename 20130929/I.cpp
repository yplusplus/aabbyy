#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

void solve(long long n,long long r,long long st,long long ed,long long &x,long long &y)
{
	if(n == 0) {
		x = 1;
		y = 0;
		return;
	}
	long long len = (1LL << (n - 1));
	if(r < len) {
		if(ed < len) {
			solve(n - 1,r,st,ed,x,y);
			return;
		}
		if(st >= len) {
			solve(n - 1,r,st - len,ed - len,x,y);
			return;
		}
		long long x1,y1,x2,y2;
		solve(n - 1,r,st,len - 1,x1,y1);
		solve(n - 1,r,0,ed - len,x2,y2);
		x = x1 + x2;
		y = y1 + y2;
		return;
	}
	if(ed < len) {
		solve(n - 1,r - len,st,ed,x,y);
		return;
	}
	if(st >= len) {
		solve(n - 1,r - len,st - len,ed - len,y,x);
		return;
	}
	long long x1,y1,x2,y2;
	solve(n - 1,r - len,st,len - 1,x1,y1);
	solve(n - 1,r - len,0,ed - len,y2,x2);
	x = x1 + x2;
	y = y1 + y2;
}

int main()
{
	ios::sync_with_stdio(0);
	long long n,r,st,ed;
	while(cin >> n >> r >> st >> ed) {
		if(n == -1 && r == -1 && st == -1 && ed == -1) break;
		long long x = 0,y = 0;
		solve(n + 1,r,st,ed,x,y);
		//cout << x << " " << y << endl;
		cout << x - y << endl;
	}
	return 0;
}