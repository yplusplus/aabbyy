#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

unsigned long long ans[75];

int main()
{
	bool flag = false;
	ios::sync_with_stdio(0);
	unsigned long long n;
	while(cin >> n) {
		if(flag) cout << endl;
		unsigned long long tmp = 1;
		int c = 0;
		while(n) {
			ans[++ c] = tmp;
			n -= tmp;
			tmp = tmp * 2;
			if(n <= tmp) {
				ans[c] += n;
				break;
			}
			tmp ++;
		}
		flag = true;
		cout << c << endl;
		for(int i = c; i >= 1; i --) {
			cout << ans[i];
			if(i == 1) cout << endl;
			else cout << " ";
		}
	}
	return 0;
}
