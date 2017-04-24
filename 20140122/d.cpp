#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1111;
LL x[N];

int main() {
	int n, r;
	ios::sync_with_stdio(0);
	while (cin >> n >> r) {
		set<LL> cover, ans;
		LL a;
		for (int i = 0; i < r; i++) {
			cin >> x[i];
			a = x[i];
			while (a > 1) {
				cover.insert(a);
				a >>= 1;
			}
		}
		for (int i = 0; i < r; i++) {
			a = x[i];
			while (a > 1) {
				if (cover.find(a ^ 1) == cover.end()) ans.insert(a ^ 1);
				a >>= 1;
			}
		}
		set<LL>::iterator si = ans.begin();
		cout << *si;
		for (si++; si != ans.end(); si++) cout << ' ' << *si;
		cout << endl;
	}
	return 0;
}
