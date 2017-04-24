#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111;

bool check(const string &s) {
	if (s[0] == 'L') {
		for (int i = 0; i < s.length(); i++) {
			if ((i & 1) && s[i] != 'R') return 0;
			if (!(i & 1) && s[i] != 'L') return 0;
		}
	} else {
		for (int i = 0; i < s.length(); i++) {
			if ((i & 1) && s[i] != 'L') return 0;
			if (!(i & 1) && s[i] != 'R') return 0;
		}
	}
	return 1;
}

bool check(int n, const string &s) {
	if (s.length() == 1) return 1;
	string sub[2];
	int l = s.length();
	sub[0] = sub[1] = "";
	for (int i = 0; i < l; i++) sub[i & 1] += s[i];
	if (check(sub[0]) && check(n - 1, sub[1])) return 1;
	if (check(sub[1]) && check(n - 1, sub[0])) return 1;
	return 0;
}

string expand(const string &s) {
	string tmp = "";
	for (int i = 0; i < s.length(); i++) {
		if (i & 1) tmp += 'R';
		else tmp += 'L';
		tmp += s[i];
	}
	tmp += 'R';
	return tmp;
}

bool test(int n, const string &s) {
   if (n > 11) return check(n, s);
   string tmp = "L";
   while (--n) tmp = expand(tmp);
   //cout << tmp << endl;
   if (strstr(tmp.c_str(), s.c_str())) return 1;
   return 0;
}   

int main() {
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		int n;
		string str;
		cin >> n >> str;
		cout << "Case " << cas << ": " << (test(n, str) ? "Yes" : "No") << endl;
	}
	return 0;
}
