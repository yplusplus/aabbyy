#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 11111;
double x[N], y[N];
template<class T> T sqr(T a) { return a * a;}

int main() {
	//freopen("in", "r", stdin);
	double avr, sd;
	int op, n;
	while (~scanf("%d%d", &op, &n)) {
		if (op == 1) {
			avr = 0;
			for (int i = 0; i < n; i++) {
				scanf("%lf", x + i);
				avr += x[i];
			}
			avr /= n;
			sd = 0;
			for (int i = 0; i < n; i++) sd += sqr(x[i] - avr);
			sd = sqrt(sd / n);
			for (int i = 0; i < n; i++) {
				if (i) putchar(' ');
				printf("%.2f", (x[i] - avr) / sd);
			}
			puts("");
		}
		if (op == 2) {
			double mp;
			scanf("%lf", &mp);
			avr = 0;
			for (int i = 0; i < n; i++) {
				scanf("%lf", x + i);
				avr += x[i];
			}
			avr /= n;
			sd = 0;
			for (int i = 0; i < n; i++) sd += sqr(x[i] - avr);
			sd = sqrt(sd / (n - 1));
			double se = sd / sqrt((double) n);
			printf("%.2f\n", (avr - mp) / se);
		}
		if (op == 3 || op == 4) {
			double mx = 0, my = 0;

			for (int i = 0; i < n; i++) {
				scanf("%lf", x + i);
				mx += x[i];
			}
			mx /= n;
			double sdx = 0;
			for (int i = 0; i < n; i++) sdx += sqr(x[i] - mx);
			sdx = sqrt(sdx / n);
			
			for (int i = 0; i < n; i++) {
				scanf("%lf", y + i);
				my += y[i];
			}
			my /= n;
			double sdy = 0;
			for (int i = 0; i < n; i++) sdy += sqr(y[i] - my);
			sdy = sqrt(sdy / n);

			double sum = 0;
			for (int i = 0; i < n; i++) sum += (x[i] - mx) * (y[i] - my);
			sum /= n * sdx * sdy;
			//cout << "sd " << sum << ' ' << sdx << ' ' << sdy << endl;
			if (op == 3) printf("%.2f\n", sum);
			else {
				double b = sum * sdy / sdx;
				double a = my - b * mx;
				printf("%.2f %.2f\n", a, b);
			}
		}
	}
	return 0;
}



