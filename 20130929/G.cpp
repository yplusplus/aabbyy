#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1111;
int maz[N][N];
int main() {
	int Case = 1;
	int n;
	while (~scanf("%d", &n), n) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &maz[i][j]);
				sum += maz[i][j];
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			int tmp = 0;
			for (int j = 0; j < n; j++) {
				tmp += maz[i][j] - maz[j][i];
			}
			ans += max(0, tmp);
		}
		printf("%d. %d %d\n", Case++, sum, ans);
	}
	return 0;
}