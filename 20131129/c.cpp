#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

LL bruce_force(int n, int m) {
	int t = min(n, m);
	LL ans = 0;
	for (int i = 1; i <= t; i++, i++) {
		ans += (LL) (n - i + 1) * (m - i + 1) * i;
	}
	return ans;
}

int main() {
	LL n, m;
	while (~scanf("%lld%lld", &n, &m) && (n || m)) {
	//while (1) {
		//n = rand() % 100000 + 1;
		//m = rand() % 100000 + 1;
		n++, m++;
		LL t = min(n, m), ht = t >> 1;
		//cout << ht << endl;
		LL ans = 0;
		ht--;
		ans += (ht * ht + ht >> 1) * (ht * ht + ht >> 1) << 3;
		ans += (12 - (n + m << 2)) * (ht * (ht + 1) * ((ht << 1) + 1) / 6);
		ans += (6 - (n + m << 2) + (m * n << 1)) * ((ht + 1) * ht >> 1);
		ans += (1 - m - n + m * n) * (ht + 1);
		printf("%lld\n", ans);
		//printf("%lld\n", bruce_force(n - 1, m - 1));
		//if (ans != bruce_force(n - 1, m - 1)) {
		//	cout << n << ' ' << m << endl;
		//	break;
		//}
	}
	return 0;
}
