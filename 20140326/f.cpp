#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		double n,m;
		int A,B;
		scanf("%lf%lf%d%d",&n,&m,&A,&B);
		printf("Case #%d: ",cas);
		double x = m * (A + B) - n * A;
		if(x < -1e-8) printf("Impossible\n");
		else {
			x /= B;
			if(!(x >= -1e-8 && x <= 10)) printf("Impossible\n");
			else printf("%.2lf\n",x);
		}
	}
	return 0;
}
