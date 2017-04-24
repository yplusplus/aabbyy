#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000010;
int pri[N],state[N];
bool a[4500010];
int fac_sum[N],sum[N];
void prime()
{
	memset(pri,-1,sizeof(pri));
	for(int i = 2; i < N; i ++) {
		if(pri[i] != -1) continue;
		pri[i] = i;
		if(i > 1010) continue;
		for(int j = i * i; j < N; j += i)
			pri[j] = i;
	}
	memset(a,false,sizeof(a));
	a[1] = a[0] = true;
	for(int i = 2; i * i < 4500010; i ++)
		if(!a[i])
			for(int j = i * i; j < 4500010; j += i)
				a[j] = true;
}

int num[25];
int get_state(int n)
{
	int cc = 1;
	if(n == 1) return (1 << 3);
	int new_state = 0;
	if(pri[n] == n) new_state |= 1;
	int tot = 1;
	int c = 0;
	while(n > 1) {
		int x = pri[n];
		int cnt = 1;
		int tmp = 1,mul = 1;
		while(n % x == 0) {
			n /= x,cnt ++;
			mul *= x;
			tmp += mul;
		}
		cc *= cnt;
		tot *= tmp;
		num[c ++] = cnt - 1;
	}
	if(!a[cc]) new_state |= 2;
	if(!a[tot]) new_state |= 4;
	bool flag = true;
	for(int i = 0; i < c; i ++) {
		int x = (num[i] + 1) * num[i] / 2 * cc / (num[i] + 1);
		if(x & 1) {
			flag = false;
			break;
		}
	}
	if(flag) new_state |= 8;
	return new_state;
}

int pa[N],pb[N],st[4];
int c[16];

struct point
{
	int val,c;
	point() {}
	point(int val,int c):val(val),c(c) {}
	friend bool operator < (const point &p,const point &q) {
		return p.val > q.val;
	}
}pt[55];

int main()
{
	int bit[55];
	memset(bit,0,sizeof(bit));
	for(int i = 0; i < 16; i ++) {
		for(int j = 0; j < 4; j ++) {
			if(i & (1 << j)) bit[i] ++;
		}
	}
	prime();
	fac_sum[1] = 1;
	sum[1] = 1;
	for(int i = 1; i < N; i ++)
		state[i] = get_state(i);
	int t,n,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		memset(c,0,sizeof(c));
		for(int i = 1; i <= n; i ++) {
			scanf("%d%d",&pa[i],&pb[i]);
			c[state[pa[i]]] += pb[i];
		}
		for(int i = 0; i < 4; i ++)
			scanf("%d",&st[i]);
		for(int i = 1; i <= n; i ++) {
			printf("%d",bit[state[pa[i]]]);
			if(i == n) printf("\n");
			else printf(" ");
		}
		int ans = -1000000000;
		for(int i = 0; i < (1 << 16); i ++) {
			int ct = 0,tsum = 0;
			int new_state = 0;
			bool flag = true;
			int sum = 0;
			int cc = 0;
			for(int j = 0; j < 16; j ++) {
				if(!(i & (1 << j))) continue;
				pt[ct ++] = point(bit[j],c[j] - 1);
				sum += bit[j];
				if(!c[j]) flag = false;
				tsum += c[j];
				new_state |= j;
				cc ++;
			}
			if(!flag) continue;
			if(cc > m) continue;
			if(tsum < m) continue;
			sort(pt,pt + ct);
			int tm = m - cc;
			for(int j = 0; j < ct && tm; j ++) {
				if(tm > pt[j].c) {
					sum += pt[j].c * pt[j].val;
					tm -= pt[j].c;
				}
				else {
					sum += pt[j].val * tm;
					break;
				}
			}
			for(int j = 0; j < 4; j ++)
				if(new_state & (1 << j)) continue;
				else sum += st[j];
			ans = max(ans,sum);
		}
		printf("%d\n",ans);
	}
	return 0;
}


