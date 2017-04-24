#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 22;
string prob[N][3], ans[N];
int ord[N];

int main() {
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> prob[i][j];
			}
			sort(prob[i], prob[i] + 3);
		}
		int x;
		for (int i = 0; i < n; i++) {
			cin >> x;
			ord[i] = x - 1;
		}
		string last = "";
		bool ok = 1;
		for (int i = 0; i < n; i++) {
			int j = 0, &k = ord[i];
			//cout << i << ' ' << k << endl;
			while (j < 3 && prob[k][j] <= last) j++;
			if (j >= 3) ok = 0;
			else {
				//cout << i << ' ' << prob[k][j] << endl;
				ans[i] = prob[k][j];
				last = prob[k][j];
			}
		}
		if (ok) for (int i = 0; i < n; i++) cout << ans[i] << endl;
		else cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}

