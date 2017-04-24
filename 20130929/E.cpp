#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
long long C(int n, int m) {
	//cout << n << " " << m << endl;
	ll res = 1;
	for (int i = 0; i < m; i++) res *= (n - i);
	for (int i = 1; i <= m; i++) res /= i;
	return res;
}
int main() {
	int a, b;
	while (~scanf("%d%d", &a, &b)) {
		if (a == -1 && b == -1) break;
		ll c = a + b;
		//cout << C(c, a) << endl;
		printf("%d+%d%s%lld\n", a, b, C(c, a) == c ? "=" : "!=", c);
	}
	return 0;
}