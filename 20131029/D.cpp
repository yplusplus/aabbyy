#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int n,d1,d2;
	cin >> n >> d1 >> d2;
	int lt = 1,rt = 100000000,mid,ans = 0;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(1LL * mid * d2 >= n * d1) {
			ans = mid;
			rt = mid - 1;
		}
		else lt = mid + 1;
	}
	int tot = n * d1;
	for(int i = 1; i <= d2; i ++) {
		printf("%d",min(ans,tot));
		if(i == d2) printf("\n");
		else printf(" ");
		tot -= min(ans,tot);
	}
	return 0;
}