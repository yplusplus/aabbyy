#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
using namespace std;

const int N = 111111;
bool visit[N];
int a[N];
int n, s;
int main() {
	while (cin >> n >> s) {
		for (int i = 0; i < n; i++) cin >> a[i];
		sort(a, a + n);
		int pos = n - 1;
		vector<int> vec;
		memset(visit, false, sizeof(visit));
		for (int i = 0; i < pos; i++) {
			if (a[i] + a[pos] > s) {
				vec.push_back(a[i]);
				vec.push_back(a[pos]);
				visit[i] = true;
				visit[pos] = true;
				pos--;
			}
		}
		for (int i = n - 1; i >= 0; i--) {
			if (!visit[i]) vec.push_back(a[i]);
		}
		int ans = 0;
		int cnt = 0;
		vec.push_back(s + 1);
		for (int i = 0; i < n; i++) {
			ans++;
			if (vec[i] + vec[i + 1] <= s) i++;
		}
		cout << ans << endl;
		for (int i = 0; i < n; i++) {
			cout << vec[i];
			if (i == n - 1) cout << endl;
			else cout << " ";
		}
	}
	return 0;
}

