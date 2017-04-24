#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
struct point
{
	int time;
	long double p;
	void read() {
		double x;
		scanf("%d%lf",&time,&x);
		p = x;
	}
	friend bool operator < (const point &p,const point &q) {
		return p.time < q.time;
	}
}a[N];

struct node
{
	int id,t;
	node() {}
	node(int id,int t):id(id),t(t) {}
	friend bool operator < (const node &p,const node &q) {
		if(p.t != q.t) return p.t > q.t;
		return p.id > q.id;
	}
};

priority_queue<node> pq;
int T[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < m; i ++) pq.push(node(i,0));
	for(int i = 1; i <= n; i ++) a[i].read();
	for(int i = 1; i <= n; i ++) {
		node u = pq.top();
		pq.pop();
		T[i] = u.t + a[i].time;
		u.t += a[i].time;
		pq.push(u);
		a[i].time = T[i];
	}
	//sort(a + 1,a + n + 1);
	long double ans = 0;
	long double p = 0;
	int MAXT = 0;
	a[n].p = 0;
	for(int i = 1; i <= n; i ++) {
		ans += max(MAXT,a[i].time) * exp(p) * (1 - a[i].p);
		p += log(a[i].p);
		MAXT = max(MAXT,a[i].time);
	}
	/*
	int i = 1;
	while(i <= n) {
		int j = i;
		while(j <= n && a[i].time == a[j].time) j ++;
		long double tmp = 0;
		for(int k = i; k < j; k ++) {
			tmp += log(a[k].p);
		}
		if(j <= n) ans += (1 - exp(tmp)) * exp(p) * a[i].time;
		else ans += exp(p) * a[i].time;
		for(int k = i; k < j; k ++)
			p += log(a[k].p);
		i = j;
		//cout << ans << endl;
	}
	*/
	printf("%.20lf\n",(double)ans);
	return 0;
}

