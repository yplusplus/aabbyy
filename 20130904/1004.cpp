#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111111;
double x[N];
int s[N];

bool check(int n) {
	sort(s, s + n);
	n = unique(s, s + n) - s;
	//for (int i = 0; i < n; i++) cout << s[i] << ' '; cout << endl;
	if (n == 1) return false;
	if (n == 2) {
		if (abs(s[0] - s[1]) == 18000) return true;
		return false;
	}
	s[n] = s[0] + 36000;
	for (int i = 1; i <= n; i++) if (s[i] - s[i - 1] >= 18000) return false;
	return true;
}

int main() {
	//freopen("in", "r", stdin);
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		s[0] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lf", x + i);
			x[i] *= 100;
			if (x[i] >= 0) x[i] += 0.05;
			else x[i] -= 0.05;
			s[i] = (int) x[i];
			s[i] += 36000, s[i] %= 36000;
		}
		n++;
		for (int i = 1; i < n; i++) s[i] += s[i - 1], s[i] %= 36000;
		if (check(n)) puts("Yes");
		else puts("No");
	}
	return 0;
}