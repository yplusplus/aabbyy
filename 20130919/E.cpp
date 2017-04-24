#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define ll long long
const int N = 25;
ll f[N];
ll f2[N];
ll n;

void dfs(int n, ll k) {
    //cout << n << " " << k << endl;
	if (k == 0 || n == 0) return;
	if (n == 1) { putchar('X'); return; }
	ll sum = 0;
	int left = 0, mid = 0, right = 0;
	ll leftk = k;
	for (left = 0; left < n; left++) {
		if (leftk / f2[n - 1 - left] > f[left]) leftk -= f[left] * f2[n - 1 - left];
		else if (leftk / f2[n - 1 - left] == f[left]) {
			if (leftk > f2[n - 1 - left] * f[left]) leftk -= f2[n - 1 - left] * f[left];
			else break;
		}
		else break;
	}
	int mr = n - 1 - left;
	if (left) {
		k = leftk % f2[mr];
		leftk = (leftk - 1) / f2[mr] + 1;
	} else k = leftk, leftk = 0;
    
	if (left) {
		putchar('(');
		dfs(left, leftk);
		putchar(')');
	}
    if(!k) k = f2[mr];
	for (mid = 0; mid <= mr; mid++) {
		if (k / f[mr - mid] > f[mid]) k -= f[mid] * f[mr - mid];
		else {
			if (k / f[mr - mid] == f[mid]) {
				if (k > f[mr - mid] * f[mid]) {
					k -= f[mid] * f[mr - mid];
				}
				else break;
			}
			else break;
		}
	}
	ll midk = 0;
	if (mid) {
		midk = (k - 1) / f[mr - mid] + 1;
		k %= f[mr - mid];
	}
    if(!k) k = f[mr - mid];
	if (mid) {
		putchar('(');
		dfs(mid, midk);
		putchar(')');
	}

	right = mr - mid;
	if (right) {
		putchar('(');
		dfs(right, k);
		putchar(')');
	}
	putchar('X');
}

int main() {
	f[0] = f[1] = 1;
	for (int i = 2; i < N; i++) {
		f[i] = 0;
		for (int left = 0; left < i; left++) {
			for (int mid = 0; mid + left < i; mid++) {
				int right = i - left - mid - 1;
				f[i] += f[left] * f[mid] * f[right];
			}
		}
		//cout << i << " " << f[i] << endl;
	}
	f2[0] = 1;
	f2[1] = 2;
	for (int i = 2; i < N; i++) {
		f2[i] = 0;
		for (int left = 0; left <= i; left++) {
			int right = i - left;
			f2[i] += f[left] * f[right];
		}
		//cout << i << " " << f2[i] << endl;
	}
	int T, Case = 1;
	cin >> T;
	while (T--) {
		cin >> n;
		printf("Case #%d: ", Case++);
		for (int i = 1; i < N; i++) {
			if (n > f[i]) n -= f[i];
			else {
				//cout << i << " " << n << endl;
				dfs(i, n);
				puts("");
				break;
			}
		}
	}
	return 0;
}

