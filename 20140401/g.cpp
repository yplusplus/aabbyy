#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("garage.in","r",stdin);
	freopen("garage.out","w",stdout);
	int W,H,w,h;
	cin >> W >> H >> w >> h;
	int x = 0,y = 0;
	for(int i = 1; ; i ++) {
		if((2 * i + 1) * w > W) {
			x = i;
			break;
		}
	}
	for(int i = 1; ; i ++) {
		if((2 * i + 1) * h > H) {
			y = i;
			break;
		}
	}
	cout << x * y << endl;
	return 0;
}
