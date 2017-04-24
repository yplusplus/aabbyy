#include <bits/stdc++.h>
using namespace std;

const int N = 222;
const int M = 222;
int n, m;

#define MP make_pair
typedef pair<int, int> pii;

void get_point(pii &p) {
	scanf("%d%d", &p.first, &p.second);
}

int sign(int x) {
	return x > 0 ? 1 : (x < 0 ? - 1: 0);
}

pii operator - (const pii &a, const pii &b) {
    return MP(sign(a.first - b.first), sign(a.second - b.second));
}

void get_image(int &m, vector<pii> &vec, pii dir[][N]) {
	pii p[M];
	vec.clear();
	vector<pii> t;
	scanf("%d", &m);
	for (int i = 0; i < 2 * m; i++) {
		get_point(p[i]);
		t.push_back(p[i]);
	}
	sort(t.begin(), t.end());
	t.erase(unique(t.begin(), t.end()), t.end());
	for (int i = 0; i < 2 * m; i += 2) {
		int a = lower_bound(t.begin(), t.end(), p[i]) - t.begin();
		int b = lower_bound(t.begin(), t.end(), p[i + 1]) - t.begin();
		vec.push_back(MP(a, b));
	}
	sort(vec.begin(), vec.end());
	m = t.size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
            dir[i][j] = t[i] - t[j];
		}
	}
}

vector<pii> vec;
pii dir[N][N], tdir[N][N];

bool check() {
	int tm;
	vector<pii> tvec;
	get_image(tm, tvec, tdir);
	if (tm != m || vec.size() != tvec.size()) return false;
	for (int i = 0; i < m; i++) {
		for (int j = i; j < m; j++) {
			if (dir[i][j] != tdir[i][j]) return false;
		}
	}
	for (int i = 0; i < tvec.size(); i++) {
		if (vec[i] != tvec[i]) {
			return false;
		}
	}
	return true;
}

int main() {
    bool first = true;
	while (~scanf("%d", &n)) {
        if (first) first = false;
        else puts("");
		get_image(m, vec, dir);
		for (int i = 1; i < n; i++) { 
			if(check()) puts("CORRECT");
			else puts("INCORRECT");
		}
	}
	return 0; 
}
