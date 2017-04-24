#include <bits/stdc++.h>
using namespace std;

int main()
{
	double a,b,c;
	int t;
	scanf("%d",&t);
	while(t --) {
	    scanf("%lf%lf%lf",&a,&b,&c);
		long long aa = 100 * (a + 1e-8);
		long long bb = 100 * (b + 1e-8);
		long long cc = 100 * (c + 1e-8);
		if(100 * (aa * bb + aa * cc + bb * cc) < aa * bb * cc) printf("Aha\n");
		else printf("No way\n");
	}
	return 0;
}
