#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
double a[N];

int main()
{
	int n,m;
	while(scanf("%d%d",&m,&n) != EOF) {
		double tot = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%lf",&a[i]);
			tot += a[i];
		}
		double lt = 0,rt = 10000000000,mid,c = 0;
		for(int times = 1; times <= 100; times ++) {
			mid = (lt + rt) / 2;
			double sum = 0;
			for(int i = 1; i <= n; i ++)
				sum += min(mid,a[i]);
			if(sum >= mid * m) {
				c = mid;
				lt = mid;
			}
			else rt = mid;
		}
		printf("%.20lf\n",tot - c * m + c);
	}
	return 0;
}
