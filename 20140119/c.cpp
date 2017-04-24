#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 555;
char str[N];
int n, k;

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%s", &n, &k, str);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			int id = str[i] - 'A';
			for (int j = 1; j <= k && i - j >= 0; j++) {
				if (str[i] == str[i - j]) {
					ans++;
					break;
				}
			}
		}
		printf("Case %d: %d\n", Case++, ans);
	}
	return 0;
}

