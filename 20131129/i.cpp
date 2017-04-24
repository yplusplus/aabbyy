#include <bits/stdc++.h>
using namespace std;

int main()
{
	double x,y,z,r;
	int t;
	int ans = 0;
	scanf("%d",&t);
	while(t --) {
		cin >> x >> y >> z >> r;
		int xx = (x + 1e-8) * 100;
		int yy = (y + 1e-8) * 100;
		int zz = (z + 1e-8) * 100;
		int rr = (r + 1e-8) * 100;
		if(((xx <= 5600 && yy <= 4500 && zz <= 2500) || xx + yy + zz <= 12500) && rr <= 700) ans ++,printf("1\n");
		else printf("0\n");
	}
	cout << ans << endl;
	return 0;
}
