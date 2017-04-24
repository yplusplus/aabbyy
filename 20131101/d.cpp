#include <bits/stdc++.h>
using namespace std;

short int bit[32000010];
struct point
{
	int val,cost;
	point() {}
	point(int val,int cost):val(val),cost(cost) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.cost != q.cost) return p.cost > q.cost;
		return p.val > q.val;
	}
};
priority_queue<point> pq;
int a[3][10010];
int len[3];

int main()
{
	bit[0] = 0;
	int m,n;
	cin >> m >> n;
	if(n == 1) {
		printf("1\n");
		return 0;
	}
	if(n == 2) {
		printf("1 2\n");
		return 0;
	}
	int tot = 1;
	while(tot * m <= 32000000) tot *= m;
	memset(a,0,sizeof(a));
	memset(len,0,sizeof(len));
	for(int i = 1; i < tot; i ++) {
		bit[i] = bit[i / m] + (i % m);
	}
	pq.push(point(1,1));
	pq.push(point(2,1));
	len[1] = len[2] = 1;
	a[1][0] = a[2][0] = 1;
	for(int i = 3; i <= n; i ++) {
		int flag = i % 3;
		int flag1 = (i - 1) % 3;
		int flag2 = (i - 2) % 3;
		int lenx = max(len[flag1],len[flag2]);
		for(int j = 0; j < lenx; j ++) {
			a[flag][j] = a[flag1][j] + a[flag2][j];
		}
		for(int j = 0; j < lenx; j ++)
			if(a[flag][j] >= tot) {
				a[flag][j + 1] ++;
				a[flag][j] -= tot;
			}
		lenx ++;
		if(!a[flag][lenx - 1]) lenx --;
		len[flag] = lenx;
		int cost = 0;
		for(int j = 0; j < lenx; j ++)
			cost += bit[a[flag][j]];
		pq.push(point(i,cost));
	}
	for(int i = 1; i <= n; i ++) {
		printf("%d",pq.top().val);
		pq.pop();
		if(i == n) printf("\n");
		else printf(" ");
	}
	return 0;
}
