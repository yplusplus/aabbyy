#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

double A,B,C;

double cal(double p,double q,double x,double y)
{
	return - p * x * A - q * y * B + p * y * C + q * x * C;
}

double cal(double p)
{
	double lt = 0,rt = 1;
	if (cal(p, 1 - p, 0, 1) > cal(p, 1 - p, 1, 0)) return 0;
	else return 1;
	for(int i = 0; i < 50; i ++) {
		double x = lt + (rt - lt) / 3;
		double y = rt - (rt - lt) / 3;
		double fx = cal(p,1 - p,x,1 - x);
		double fy = cal(p,1 - p,y,1 - y);
		if(fx <= fy) lt = x;
		else rt = y;
	}
	return lt;
}

int main()
{
	//ios::sync_with_stdio(0);
	while(scanf("%lf%lf%lf",&A,&B,&C) != EOF) {
		double lt = 0,rt = 1,ans = 0;
		for(int i = 0; i < 100; i ++) {
			double x = lt + (rt - lt) / 3;
			double y = rt - (rt - lt) / 3;
			double xx = cal(x);
			double yy = cal(y);
			double fx = -cal(x,1 - x,xx,1 - xx);
			double fy = -cal(y,1 - y,yy,1 - yy);
			if(fx <= fy) lt = x;
			else rt = y;
		}
		double x = cal(lt);
		ans = -cal(lt,1 - lt,x,1 - x);
		if(fabs(ans) < 1e-8) ans = 0;
		printf("%.6f\n",ans);
	}
	return 0;
}

