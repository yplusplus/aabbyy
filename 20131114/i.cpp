#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL G = 98;

LL X[3], Y[3], V;
template<class T> T sqr(T x) { return x * x; }
bool check(int a, int b) {
	LL x = abs(X[b] - X[a]), y = Y[b] - Y[a];
	if (x == 0) return sqr(V) * 10 >= G * y * 2;
	return sqr(sqr(V)) * 100 - sqr(G) * sqr(x) >= G * y * sqr(V) * 20;
}

int main() {
	while (cin >> V) {
		for (int i = 0; i < 3; i++) cin >> X[i] >> Y[i];
		if (check(1, 2) && check(2, 1) && (check(1, 0) || check(2, 0))) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
