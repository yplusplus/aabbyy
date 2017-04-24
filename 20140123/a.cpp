#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
	LL l, p, v, cas = 1;
	while (cin >> l >> p >> v && l + p + v) {
		cout << "Case " << cas++ << ": " << v / p * l + min(l, v % p) << endl;
	}
	return 0;
}
