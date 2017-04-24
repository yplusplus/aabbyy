#include <bits/stdc++.h>
using namespace std;

map<string, string> hash;
bool delimiter[256];

void init() {
	memset(delimiter, false, sizeof(delimiter));
	delimiter[' '] = true;
	delimiter['-'] = true;
	delimiter[','] = true;
	delimiter['.'] = true;
	delimiter['"'] = true;
	delimiter['('] = true;
	delimiter[')'] = true;
	delimiter[':'] = true;
	delimiter[';'] = true;
	delimiter['!'] = true;
	delimiter['?'] = true;
	delimiter['\n'] = true;
}

string tolow(string word) {
	string res;
	for (int i = 0; i < word.size(); i++) {
		res += tolower(word[i]);
	}
	return res;
}

void handle(string word, bool digit) {
	string lower = tolow(word);
	int len = lower.length();
	if (digit) {
		if (hash.count(lower) > 0) {
			string target = hash[lower];
			if (target == "*") cout << word;
			else {
				if (islower(word[0])) {
					cout << target;
				} else if (islower(word[len - 1])) {
					target[0] = toupper(target[0]);
					cout << target;
				} else {
					for (int i = 0; i < target.length(); i++) {
						target[i] = toupper(target[i]);
					}
					cout << target;
				}
			}
		} else cout << word;
	} else {
		char str[200];
		sprintf(str, "%c%d%c", lower[0], len - 2, lower[len - 1]);
		string tmp(str);
		if (hash.count(tmp) == 0) {
			hash[tmp] = lower;
		} else if (hash[tmp] != lower) {
			hash[tmp] = "*";
		}
		cout << word;
	}
}

void solve(string line) {
	line += '\n';
	string word;
	bool digit = false;
	for (int i = 0; i < line.length(); i++) {
		if (delimiter[line[i]]) {
			if (!digit && word.length() <= 3) cout << word;
			else handle(word, digit);
			cout << line[i];
			digit = false;
			word = "";
		} else {
			if (isdigit(line[i])) digit = true;
			word += line[i];
		}
	}
}

int main() {
	init();
	string line;
	bool first = true;
	while (getline(cin, line)) {
		if (line == "") {
			hash.clear();
			cout << line << endl;
		} else solve(line);
	}
	return 0;
}
