#include <bits/stdc++.h>
using namespace std;

int run() {
	int _;
	string buf, rec, tmp;
	cin >> _;
	getline(cin, buf);
	while (_--) {
		getline(cin, rec);
		set<string> other;
		while (getline(cin, buf)) {
			stringstream in(buf);
			in >> tmp;
			if (tmp == "what") break;
			assert(tmp != "fox");
			while (in >> tmp) other.insert(tmp);
		}
		bool pnt = 0;
		stringstream in(rec);
		while (in >> tmp) {
			if (other.find(tmp) == other.end()) {
				if (pnt) cout.put(' ');
				pnt = 1;
				cout << tmp;
			}
		}
		cout << endl;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
