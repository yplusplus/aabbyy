#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

bool check(long long tmp , long long a, long long b) {
	if (tmp * a < 0) return false;
	long long p = sqrt(1.0 * tmp * a);
	while (p * p <= tmp * a) p++;
	p--;
	if (p * p != tmp * a) return false;
	return p + b == tmp;
}

long long sqr(long long x) {
	return x * x;
}

/*
x^2 - 2bx + b^2 = ax
x^2 - (2b + a) x + b^2 = 0
(2b + a) +/- sqrt((2b + a) ^ 2 - 4 b^2)
*/
int solve() {
	int a, b;
	scanf("%d%d", &a, &b);
	if (!a) {
		cout << 1 << endl;
		cout << b << endl;
		return 0;
	}
	long long x = (2 * b + a);
	long long y = sqr(x) - 4 * sqr(b);
	if (y < 0) {
		cout << 0 << endl;
		return 0;
	}
	if (y == 0) {
		if (x % 2) {
			cout << 0 << endl;
			return 0;
		}
		long long tmp = x / 2;
		if (!check(tmp, a, b)) cout << 0 << endl;
		else {
		    cout << 1 << endl;
	    	cout << x / 2 << endl;
		}
		return 0;
	}

	long long p = sqrt(1.0 * y);
	while (p * p <= y) p++;
	p--;
	if (p * p != y) {
		cout << 0 << endl;
		return 0;
	}

    if ((x + p) % 2) cout << 0 << endl;
	else {
		vector<long long> ans;
	    long long ans1 = (x + p) / 2;
		long long ans2 = (x - p) / 2;
		if (ans1 > ans2) swap(ans1, ans2);
		if (check(ans1, a, b)) ans.push_back(ans1);
		if (check(ans2, a, b)) ans.push_back(ans2);
		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); i++) {
			cout << ans[i];
			if (i == ans.size() - 1) cout << endl;
			else cout << " ";
		}
	}
	return 0;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) solve();
	return 0;
}
