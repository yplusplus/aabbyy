#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

double cal(int X,int Y,int T,int S)
{
	if(X <= Y) return 1.0 * S / X;
	double ans = 0;
	double val = T * Y;
	while(1) {
		double t = 1.0 * val / (X - Y);
		if(t * Y + val >= S) return ans + 1.0 * S / X;
		ans += t;
		val += t * Y;
	}
	return ans;
}

int main()
{
	int X,Y,T,S,t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d%d%d",&X,&Y,&T,&S);
		printf("Case #%d: %.3lf\n",cas,cal(X,Y,T,S));
	}
	return 0;
}


