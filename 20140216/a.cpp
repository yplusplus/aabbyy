#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second
const int N = 33;
int mat[N][N], pos[N];

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int n, k, x, y, z;
	while (cin >> n && n) {
		memset(mat, 0, sizeof mat);
		for (int i = 1; i <= n; i++) {
			cin >> x >> k;
			for (int j = 0; j < k; j++) {
				cin >> y >> z;
				mat[x][y] = z;
			}
		}
		int id;
		vector<PII> ans;
		while (cin >> id && id) {
			for (int i = 1; i <= n; i++) cin >> pos[i];
			int sum = 0;
			for (int i = 1; i <= n; i++) {
				cin >> x;
				for (int j = 1; j <= n; j++) {
					sum += (abs(j - i) + 1) * mat[pos[j]][x];
					//cout << pos[j] << ' ' << x << ' ' << mat[pos[j]][x] << endl;
				}
			}
			ans.push_back(PII(sum, id));
		}
		sort(ans.begin(), ans.end());
		cout << "Configuration Load" << endl;
		int sz = ans.size();
		for (int i = 0; i < sz; i++) {
			cout.width(5);
			cout << ans[i].y << "         " << ans[i].x << endl;
		}
	}
	return 0;
}
