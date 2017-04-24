#include <bits/stdc++.h>
using namespace std;

/*
   bool visit[21][1 << 22];
   int a[25], tot;
   int bits[1 << 20];

   int used[1 << 22];
   bool check() {
   for (int i = 0; i < (1 << tot); i++) {
   long long sum = a[tot];
   for (int j = 0; j < tot; j++) {
   if (i >> j & 1) {
   sum += a[j];
   }
   }
//cout << "sum = " << sum << " " << bits[i] << endl;
if (visit[bits[i] + 1][sum]) return false;
}
return true;
}
 */

int main() {
	/*
	   bits[0] = 0;
	   for (int i = 1; i < (1 << 20); i++) {
	   bits[i] = bits[i >> 1] + (i & 1);
	   }
	   tot = 0;
	   for (int i = 1; i < 1 << 20 && tot < 21; i++) {
	   a[tot] = i;
	   if (check()) {
	   tot++;
	//cout << tot << " " << i << endl;
	printf("ans[%d] = %d\n", tot, i);
	//cout << i << ", ";
	memset(visit, false, sizeof(visit));
	for (int j = 0; j < (1 << tot); j++) {
	long long sum = 0;
	for (int k = 0; k < tot; k++) {
	if (j >> k & 1)
	sum += a[k];
	}
	visit[bits[j]][sum] = true;
	}
	}
	}
	 */
	freopen("chipmunks.in", "r", stdin);
	freopen("chipmunks.out", "w", stdout);
	int ans[25];
	ans[1] = 1;
	ans[2] = 2;
	ans[3] = 3;
	ans[4] = 5;
	ans[5] = 8;
	ans[6] = 14;
	ans[7] = 25;
	ans[8] = 45;
	ans[9] = 85;
	ans[10] = 162;
	ans[11] = 310;
	ans[12] = 595;
	ans[13] = 1165;
	ans[14] = 2285;
	ans[15] = 4485;
	ans[16] = 8808;
	ans[17] = 17306;
	ans[18] = 34302;
	ans[19] = 68009;
	ans[20] = 134853;
	int n;
	cin >> n;
	cout << ans[n] << endl;
	return 0;
}

