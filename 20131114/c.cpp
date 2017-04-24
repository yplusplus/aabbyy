#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

map<string, string> pwd;
map<string, int> st;
int main() {
	int n;
	string op, s1, s2;
	while (cin >> n) {
		pwd.clear();
		st.clear();
		while (n--) {
			cin >> op;
			if (op == "register") {
				cin >> s1 >> s2;
				if (pwd.find(s1) == pwd.end()) {
					pwd[s1] = s2;
					st[s1] = 0;
					cout << "success: new user added" << endl;
				} else cout << "fail: user already exists" << endl;
			}
			if (op == "login") {
				cin >> s1 >> s2;
				if (pwd.find(s1) == pwd.end()) cout << "fail: no such user" << endl;
				else if (pwd[s1] != s2) cout << "fail: incorrect password" << endl;
				else if (st[s1]) cout << "fail: already logged in" << endl;
				else {
					st[s1] = 1;
					cout << "success: user logged in" << endl;
				}
			}
			if (op == "logout") {
				cin >> s1;
				if (pwd.find(s1) == pwd.end()) cout << "fail: no such user" << endl;
				else if (st[s1] == 0) cout << "fail: already logged out" << endl;
				else {
					st[s1] = 0;
					cout << "success: user logged out" << endl;
				}
			}
		}
	}
	return 0;
}


