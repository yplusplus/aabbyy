#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 510;
struct point
{
	long long x,y;
	point() {}
	point(long long x,long long y):x(x),y(y) {}
};
vector<point> v[N];
int a[N];

void solve(vector<point> &v,int x,int n)
{
	v.clear();
	long long tmp = x;
	while(tmp <= n) {
		v.push_back(point(tmp,tmp * x - 1));
		tmp *= x;
	}
}

long long cal(long long n,int m)
{
	return n / m;
}

long long solve(int n,int m)
{
	long long pos = a[n];
	long long ans = 0;
	int next[N];
	memset(next,0,sizeof(next));
	while(pos <= m) {
		long long rpos = m;
		long long lcm = 1;
		for(int i = 1; i <= n && lcm <= m; i ++) {
			while(next[i] < v[i].size() && v[i][next[i]].y < pos) next[i] ++;
			if(next[i] >= v[i].size()) return ans;
			rpos = min(rpos,v[i][next[i]].y);
			lcm = lcm * (next[i] + 1LL) / __gcd(lcm,next[i] + 1LL);
		}
//		cout << lcm << " " << rpos << " " << pos << " " << ans << endl;
		ans += cal(rpos,lcm) - cal(pos - 1,lcm);
		pos = rpos + 1;
//		cout << ans << endl;
	}
	return ans;
}

int main()
{
	int n,m,r;
	while(scanf("%d%d%d",&n,&m,&r) != EOF) {
		for(int i = 1; i <= n; i ++)
			scanf("%d",&a[i]);
		sort(a + 1,a + n + 1);
		int cc = 1;
		for(int i = 2; i <= n; i ++)
			if(a[cc] != a[i]) a[++ cc] = a[i];
		n = cc;
		for(int i = 1; i <= n; i ++) {
			solve(v[i],a[i],r);
		}
		if(a[n] > r) {
			printf("0\n");
			continue;
		}
		printf("%lld\n",solve(n,r) - solve(n,m - 1));
	}
	return 0;
}
