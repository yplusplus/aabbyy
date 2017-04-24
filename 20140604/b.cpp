#include <bits/stdc++.h>
using namespace std;

string build(int n) {
	string temp = string(n >> 1, '0') + string(n >> 1, '1');
	temp[0] = '1';
	temp[n - 1] = '0';
	return temp;
}

string build(string s) {
	int n = s.length();
	while (n--) { // +1
		if (s[n] == '9') {
			s[n] = '0';
		} else {
			++s[n];
			break;
		}
	}
	n = s.length();
	string temp(n, '0');
	for (int i = 0; i < n; ++i) { // fix suffix
		if (s[i] == '0') {
			temp[n - 1 - i] = '1';
		}
	}
	return s + temp;
}

void inc(string &s) {
	int n = s.length();
	while (n--) {
		if (s[n] == '9') {
			s[n] = '0';
		} else {
			++s[n];
			break;
		}
	}
	if (n < 0) {
		s = '1' + s;
	}
}

bool check(const string &s) {
	int n = s.length();
	for (int i = 0; i < n; ++i) {
		if (s[i] == s[n - 1 - i]) return 0;
	}
	return 1;
}

bool check(const string &f, string &b) {
	int n = b.length();
	for (int l = n; l > 0; --l) {
		string t1 = b.substr(0, l);
		while (t1[l - 1] != '9') {
			inc(t1);
			string t2 = t1 + string(n - l, '0');
			for (int i = 0; i < n - l; ++i) {
				if (f[n - 1 - (l + i)] == t2[l + i]) {
					t2[l + i] = '1';
				}
			}
			if (check(f + t2)) {
				b = t2;
				return 1;
			}
		}
	}
	return 0;
}

string solve(const string &s) {
	if (s.length() & 1) {
		return build(s.length() + 1);
	}
	int n = s.length();
	string front, back;
	for (int i = 0; i < (n >> 1); ++i) {
		front += s[i];
		back += s[i + (n >> 1)];
	}
	//cerr << front << ' ' << back << endl;
	if (check(front, back)) {
		return front + back;
	} else {
		if (front == string(n >> 1, '9')) {
			return build(s.length() + 2);
		} else {
			return build(front);
		}
	}
}

string bruteForce(string a) {
	while (1) {
		inc(a);
		if (check(a)) {
			break;
		}
	}
	return a;
}

int run() {
	string number;
	//number = "100000"; while (1) { if (solve(number) != bruteForce(number)) { return 0; } inc(number); cerr << number << endl; }
	while (cin >> number && number != "0") {
		cout << solve(number) << endl;
		//cerr << bruteForce(number) << endl;
	}
	return 0;
}

int main() {
	freopen("anti.in", "r", stdin);
	freopen("anti.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
