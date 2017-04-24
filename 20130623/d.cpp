#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long a[25];
int n,m;

bool sure(int mid)
{
	long long sum = 0;
	for(int i = 1; i <= m; i ++) {
		int x = max(0LL,a[i] - mid);
		if(x > n - mid) return false;
		sum += x;
	}
	return sum <= 1LL * (n - mid) * (m - 1);
}

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i ++)
		cin >> a[i];
	int ans = 0,lt = 0,rt = n,mid;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(sure(mid)) ans = mid,rt = mid - 1;
		else lt = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
