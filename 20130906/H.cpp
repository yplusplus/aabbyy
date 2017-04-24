#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
int main() {
	int n;
	LL a, b, c;
	while (cin >> n) {
		while (n--) {
			cin >> a >> b >> c;
			if (a < 0) a = -a, b = -b, c = -c;
			LL dt = b * b - (a * c << 2);
			if (dt >= 0) {
				double d = sqrt((double) dt);
				if (dt) printf("%.2f %.2f\n", (-b - d) / (2.0 * a), (-b + d) / (2.0 * a));
				else printf("%.2f\n", (double) -b / (2.0 * a));
			} else puts("NO");
		}
	}
	return 0;
}



