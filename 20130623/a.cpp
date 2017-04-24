#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	long long n,m,N;
	cin >> n >> m >> N;
	long long lt = m,rt = N - 1,ans = m,mid;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(m * (N - mid) - (n - m) * (mid + 1) >= 0) {
			ans = mid + 1;
			lt = mid + 1;
		}
		else rt = mid - 1;
	}
	cout << ans << endl;
	return 0;
}

