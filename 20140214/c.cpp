#include <bits/stdc++.h>
using namespace std;

const char *Chinese[4][3] = {	{ "[pn]", "shi", "[n]" },
							 	{ "[pn]", "[vi]" },
								{ "[pn]", "[vt]", "[n]" },
								{ "ni", "hao" }
};
const char *English[4][4] = {	{ "[pn]", "[vi]" },
								{ "[pn]", "[vt]", "[n]" },
								{ "There", "is", "a", "[n]" },
								{ "Happy", "new", "year" }
};
const char *Japanese[5][6] = {	{ "[pn]", "ha", "[n]", "desu" },
								{ "[pn]", "ha", "[n]", "da" },
								{ "[pn]", "ha", "[n]", "ga", "[adj]", "desu" },
								{ "[n]", "saikou" },
								{ "yoi", "otoshiwo" }
};
const char *German[4][4] = { 	{ "Ich", "habe", "ein", "[n]" },
								{ "Ich", "bin", "[n]" },
								{ "Ich", "heisse", "[n]" },
								{ "Du", "hast", "[n]" }
};
const int Chinese_size[4] = { 3, 2, 3, 2 };
const int English_size[4] = { 2, 3, 4, 3 };
const int Japanese_size[5] = { 4, 4, 6, 2, 2 };
const int German_size[4] = { 4, 3, 3, 3 };

map<string, int> id;
string name[4];
const int N = 22;
vector<string> def[N];
int n, m;

void predo() {
	id[name[0] = "Chinese"] = 0;
	id[name[1] = "English"] = 1;
	id[name[2] = "Japanese"] = 2;
	id[name[3] = "German"] = 3;
	for (int i = 0; i < N; i++) def[i].resize(3, "");
}

bool find(vector<string> &a) {
	for (int i = 0; i < n; i++) if (a == def[i]) return 1;
	return 0;
}

bool Chinese_check(const vector<string> &s) {
	int n = s.size();
	vector<string> tmp(3, "");
	for (int i = 0; i < 4; i++) {
		if (n != Chinese_size[i]) continue;
		bool ok = 1;
		for (int j = 0; j < n && ok; j++) {
			if (Chinese[i][j][0] == '[') {
				tmp[0] = "Chinese";
				tmp[1] = Chinese[i][j];
				tmp[2] = s[j];
				if (!find(tmp)) ok = 0;
			} else {
				if (s[j] != Chinese[i][j]) ok = 0;
			}
		}
		if (ok) return 1;
	}
	return 0;
}

bool English_check(const vector<string> &s) {
	int n = s.size();
	vector<string> tmp(3, "");
	for (int i = 0; i < 4; i++) {
		if (n != English_size[i]) continue;
		bool ok = 1;
		for (int j = 0; j < n && ok; j++) {
			if (English[i][j][0] == '[') {
				tmp[0] = "English";
				tmp[1] = English[i][j];
				tmp[2] = s[j];
				if (!find(tmp)) ok = 0;
			} else {
				if (s[j] != English[i][j]) ok = 0;
			}
		}
		if (ok) return 1;
	}
	return 0;
}

bool Japanese_check(const vector<string> &s) {
	int n = s.size();
	vector<string> tmp(3, "");
	for (int i = 0; i < 5; i++) {
		if (n != Japanese_size[i]) continue;
		bool ok = 1;
		for (int j = 0; j < n && ok; j++) {
			if (Japanese[i][j][0] == '[') {
				tmp[0] = "Japanese";
				tmp[1] = Japanese[i][j];
				tmp[2] = s[j];
				if (!find(tmp)) ok = 0;
			} else {
				if (s[j] != Japanese[i][j]) ok = 0;
			}
		}
		if (ok) return 1;
	}
	return 0;
}

bool German_check(const vector<string> &s) {
	int n = s.size();
	vector<string> tmp(3, "");
	for (int i = 0; i < 4; i++) {
		if (n != German_size[i]) continue;
		bool ok = 1;
		for (int j = 0; j < n && ok; j++) {
			if (German[i][j][0] == '[') {
				tmp[0] = "German";
				tmp[1] = German[i][j];
				tmp[2] = s[j];
				if (!find(tmp)) ok = 0;
			} else {
				if (s[j] != German[i][j]) ok = 0;
			}
		}
		if (ok) return 1;
	}
	return 0;
}

string get_type(const string &s) {
	vector<string> com;
	char *p = strtok(const_cast<char *>(s.c_str()), " ");
	while (p) {
		com.push_back(p);
		p = strtok(0, " ");
	}
	if (Chinese_check(com)) return name[0];
	if (English_check(com)) return name[1];
	if (Japanese_check(com)) return name[2];
	if (German_check(com)) return name[3];
	return "I don't know.";
}

int main() {
	//freopen("in", "r", stdin);
	int _;
	predo();
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cout << "Case #" << cas << ":" << endl;
		cin >> n >> m;
		for (int i = 0; i < n; i++) for (int j = 0; j < 3; j++) cin >> def[i][j];
		string sentense;
		getline(cin, sentense);
		for (int i = 0; i < m; i++) {
			getline(cin, sentense);
			cout << get_type(sentense) << endl;
		}
	}
	return 0;
}
