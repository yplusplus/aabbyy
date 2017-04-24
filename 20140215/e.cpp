#include <bits/stdc++.h>
using namespace std;

double odd[3];
int bet[3], gain[3];
int s;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &s);
		for (int i = 0; i < 3; i++) scanf("%lf", &odd[i]);
		int ans = s;
		int used = 3;
		for (int i = 0; i < 3; i++) bet[i] = 1;
		while (used <= s) {
			int mi = 1 << 30;
			for (int i = 0; i < 3; i++) {
				gain[i] = (int) floor(bet[i] * odd[i]);
				mi = min(gain[i], mi);
			}
			if (used < mi) {
				//cout << s << endl;
				//cout << used << " " << mi << endl;
				ans = max(ans, s + mi - used);
				for (int i = 0; i < 3; i++) {
					if (gain[i] == mi) {
						bet[i]++;
						used++;
					}
				}
				//ans = max(ans, (s % used) + (s / used * (mi - used)));
				//break;
			} else {
				for (int i = 0; i < 3; i++) {
					if (gain[i] <= used) {
						bet[i]++;
						used++;
					}
				}
			}
			//cout << used << " " << mi << endl;
		}
		printf("%d\n", ans);
	}
	return 0;
}
