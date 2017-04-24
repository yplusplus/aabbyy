#include <bits/stdc++.h>
using namespace std;

typedef vector<string> VS;
map<string, string> son;
void init() {
	son["AA"] = "A";
	son["BB"] = "B";
	son["OO"] = "O";
	son["AB"] = son["BA"] = "AB";
	son["AO"] = son["OA"] = "A";
	son["BO"] = son["OB"] = "B";
}

inline string combine(const string &a, const string &b) {
	string c;
	c += son[a.substr(0, 1) + b[0]] + ('-' == a[1] && '-' == b[1] ? '-' : '+');
	return c;
}

void split(const string &s, VS &v) {
	int cnt = 0;
	char sg = s[s.length() - 1];
	v.clear();
	for (int i = 0; isalpha(s[i]); ++i, ++cnt) {
		v.push_back(s.substr(i, 1) + sg);
		if ('+' == sg) v.push_back(s.substr(i, 1) + '-');
	}
	if (2 == cnt || 'O' == s[0]) return ;
	v.push_back(string("O") + sg);
	if ('+' == sg) v.push_back(string("O") + '-');
	sort(v.begin(), v.end());
	cnt = unique(v.begin(), v.end()) - v.begin();
	while (v.size() > cnt) v.pop_back();
}

void test1() {
	VS tmp;
	string blood;
	while (cin >> blood) {
		split(blood, tmp);
		for (int i = 0, sz = tmp.size(); i < sz; ++i) cout << tmp[i] << "~" << endl;
	}
}

void test2() {
	string a, b;
	while (cin >> a >> b) cout << combine(a, b) << endl;
}

bool input(string *const s) {
	for (int i = 0; i < 3; ++i) cin >> s[i];
	if ("E" == s[0] && "N" == s[1] && "D" == s[2]) return 0;
	return 1;
}

const char *blood = "ABO";
const char *allel = "+-";

string solve(const string &a, const string &b, VS &vc) {
	VS va, vb;
	split(a, va);
	split(b, vb);
	vc.clear();
	int n = va.size(), m = vb.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			vc.push_back(combine(va[i], vb[j]));
		}
	}
	sort(vc.begin(), vc.end());
	int cnt = unique(vc.begin(), vc.end()) - vc.begin();
	while (vc.size() > cnt) vc.pop_back();
	return vc.size() ? "?" : "IMPOSSIBLE";
}

string solve(const string &a, VS &vb, const string &c) {
	VS va, vbp;
	string b;
	split(a, va);
	vb.clear();
	int n = va.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				for (int l = 0; l < 2; ++l) {
					vbp.clear();
					b = blood[j];
					b = son[b + blood[k]] + allel[l];
					split(b, vbp);
					for (int p = 0, sz = vbp.size(); p < sz; ++p) {
						if (combine(va[i], vbp[p]) == c) {
							vb.push_back(b);
							break;
						}
					}
				}
			}
		}
	}
	sort(vb.begin(), vb.end());
	int cnt = unique(vb.begin(), vb.end()) - vb.begin();
	while (vb.size() > cnt) vb.pop_back();
	return vb.size() ? "?" : "IMPOSSIBLE";
}

int run() {
	init();
	//test1();
	//test2();
	int cas = 0;
	string s[3];
	while (input(s)) {
		VS ans;
		if ("?" == s[2]) s[2] = solve(s[0], s[1], ans);
		else {
			if ("?" == s[1]) s[1] = solve(s[0], ans, s[2]);
			else s[0] = solve(s[1], ans, s[2]);
		}
		cout << "Case " << ++cas << ":";
		if (ans.empty()) for (int i = 0; i < 3; ++i) cout << ' ' << s[i];
		else {
			for (int i = 0; i < 3; ++i) {
				if ("?" == s[i]) {
					if (1 == ans.size()) cout << ' ' << ans[0];
					else {
						cout << " {";
						for (int j = 0, sz = ans.size(); j < sz; ++j) {
							if (j) cout << ", ";
							cout << ans[j];
						}
						cout << "}";
					}
				} else cout << ' ' << s[i];
			}
		}
		cout << endl;
	}
	return 0;
}

int main() {
	//freopen("in_a", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}

