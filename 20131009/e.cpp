#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int INF = 33333;
int n;
const int N = 15;
int a[N];

bool check(int x, int i) {
	if (i == n) return x <= 1;
	return check(abs(x - a[i]), i + 1);
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		vector<int> vec;
		int l = -INF, r = INF;
		for (int i = l; i <= r; i++) {
			if (check(i, 0)) vec.push_back(i);
		}
		//cout << vec.size() << endl;
		vector<pair<int, int> > segment;
		for (int i = 0, j; i < vec.size(); i = j + 1) {
			j = i;
			while (j + 1 < vec.size() && vec[j + 1] - vec[i] == j + 1 - i) j++;
			segment.push_back(make_pair(vec[i], vec[j]));
		}
		cout << segment.size() << endl;
		for (int i = 0; i < segment.size(); i++) {
			cout << segment[i].first << " " << segment[i].second << endl;
		}
	}
}


