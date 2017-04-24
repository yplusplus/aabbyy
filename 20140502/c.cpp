#include <bits/stdc++.h>
using namespace std;

const long long oo = 1LL << 60;
const int N = 30010;
struct tree
{
	int lt,rt;
	long long sum,flag;
	long long dis() {
		return rt - lt + 1;
	}
}a[N << 2];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].flag = oo;
	if(lt == rt) {
		scanf("%lld",&a[step].sum);
		return;
	}
	int mid = (lt + rt) >> 1;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	a[step].sum = a[2 * step].sum + a[2 * step + 1].sum;
}

void down(int step)
{
	a[2 * step].flag = a[step].flag;
	a[2 * step + 1].flag = a[step].flag;
	a[2 * step].sum = a[step].flag * a[2 * step].dis();
	a[2 * step + 1].sum = a[step].flag * a[2 * step + 1].dis();
	a[step].flag = oo;
}

void update(int lt,int rt,int step,long long val)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		a[step].flag = val;
		a[step].sum = val * a[step].dis();
		return;
	}
	if(a[step].flag != oo) down(step);
	if(rt <= a[2 * step].rt) update(lt,rt,2 * step,val);
	else if(lt > a[2 * step].rt) update(lt,rt,2 * step + 1,val);
	else {
		update(lt,a[2 * step].rt,2 * step,val);
		update(a[2 * step + 1].lt,rt,2 * step + 1,val);
	}
	a[step].sum = a[2 * step].sum + a[2 * step + 1].sum;
}

long long query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step].sum;
	if(a[step].flag != oo) down(step);
	if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
	else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
	return query(lt,a[2 * step].rt,2 * step) + query(a[2 * step + 1].lt,rt,2 * step + 1);
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		init(1,n,1);
		int lt,rt;
		long long pre = a[1].sum;
		while(m --) {
			scanf("%d%d",&lt,&rt);
			long long sum = query(lt,rt,1);
			long long ave = sum / (rt - lt + 1);
			//if(lt == 1) cout << sum << " " << ave << endl;
			if(ave * (rt - lt + 1) == sum) update(lt,rt,1,ave);
			else {
				if(a[1].sum <= pre) {
					if(sum < 0) update(lt,rt,1,ave);
					else update(lt,rt,1,ave + 1);
				}
				else {
					if(sum < 0) update(lt,rt,1,ave - 1);
					else update(lt,rt,1,ave);
				}
			}
		}
		for(int i = 1; i <= n; i ++) {
			printf("%lld",query(i,i,1));
			if(i == n) printf("\n");
			else printf(" ");
		}
		printf("\n");
	}
	return 0;
}
