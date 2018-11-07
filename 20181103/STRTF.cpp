#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

/*
1 : a[i] ^ a[i + 1]
2 : a[i] ^ a[i + 2]
3 : a[i] ^ a[i + 1] ^ a[i + 2] ^ a[i + 3]
4 : a[i] ^ a[i + 4]
5 : a[i] ^ a[i + 1] ^ a[i + 4] ^ a[i + 5]
6 : a[i] ^ a[i + 2] ^ a[i + 4] ^ a[i + 6]
7 : a[i] ^ a[i + 1] ... ^ a[i + 7]
8 : a[i] ^ a[i + 8]
9 : a[i] ^ a[i + 1] ^ a[i + 8] ^ a[i + 9]
10: a[i] ^ a[i + 2] ^ a[i + 8] ^ a[i + 10]
11: a[i] ^ a[i + 1] ^ a[i + 2] ^ a[i + 3] ^ a[i + 8] ^ a[i + 9] ^ a[i + 10] ^ a[i + 11]
*/

const int N = 200010;
int a[257][N];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[0][i]);
	}
	for (int i = 1; i <= 256; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = a[i - 1][j] ^ a[i - 1][j + 1];
		}
	}

	int k, x;
	while (m--) {
		scanf("%d%d", &k, &x);
		int low = 0;
		if (k <= 256) {
			printf("%d\n", a[k][x]);
			continue;
		}
		for (int i = 0; (1 << i) <= n; i++)
			if (k & (1 << i)) {
				low |= (1 << i);
			}

		//cout << "here : " << low << " " << k << endl;
		int b = low & 255;
		low = (low >> 8) << 8;
		int ans = a[b][x];
		for (int i = low; i; i = (i - 1) & low) {
			//cout << "here : " << b << " " << i << endl;
			if (x + i <= n) ans ^= a[b][x + i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
