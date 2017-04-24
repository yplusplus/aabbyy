#include <bits/stdc++.h>
using namespace std;

const string subject_name[3] = { "Computer", "Chinese", "Mathematics" };
typedef double DB;
typedef long long LL;
typedef pair<string, string> PS2;
typedef pair<DB, PS2> PIS2;
typedef vector<PIS2> VP;
#define x first
#define y second

const int nx[3][3] = {
	{ 0, 2, 0 },
	{ 2, 1, 0 },
	{ 2, 0, 2 },
};

map<string, int> id;
void init() { for (int i = 0; i < 3; ++i) id[subject_name[i]] = i; }

int run() {
	int n;
	init();
	while (cin >> n) {
		VP student(n);
		for (int i = 0; i < n; ++i) cin >> student[i].y.x >> student[i].y.y >> student[i].x;
		LL dist_x = 0, dist_y = 0, ep;
		sort(student.begin(), student.end());
		reverse(student.begin(), student.end());
		int last, cur;
		last = 0;
		for (int i = ep = 1 ; i < n; ++i) ep *= 3;
		for (int i = n - 1; i >= 0; --i) {
			cur = id[student[i].y.x];
			dist_x += ep * abs(last - cur);
			last = nx[last][cur];
			ep /= 3;
		}
		last = 0;
		for (int i = ep = 1 ; i < n; ++i) ep *= 3;
		for (int i = n - 1; i >= 0; --i) {
			cur = id[student[i].y.y];
			dist_y += ep * abs(last - cur);
			last = nx[last][cur];
			ep /= 3;
		}
		//cerr << dist_x << ' ' << dist_y << endl;
		cout << abs(dist_x - dist_y) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_b", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
