#include <bits/stdc++.h>
using namespace std;

int dx[] = {2, 2, 1, 2, 2, 2, 1};
string s, t;
vector<string> vec[2];
string tone[2][12];

void init() {
	tone[0][0] = "C";
	tone[0][1] = "C#";
	tone[0][2] = "D";
	tone[0][3] = "D#";
	tone[0][4] = "E";
	tone[0][5] = "F";
	tone[0][6] = "F#";
	tone[0][7] = "G";
	tone[0][8] = "G#";
	tone[0][9] = "A";
	tone[0][10] = "A#";
	tone[0][11] = "B";
	tone[1][0] = "B#";
	tone[1][1] = "Db";
	tone[1][2] = "";
	tone[1][3] = "Eb";
	tone[1][4] = "Fb";
	tone[1][5] = "E#";
	tone[1][6] = "Gb";
	tone[1][7] = "";
	tone[1][8] = "Ab";
	tone[1][9] = "";
	tone[1][10] = "Bb";
	tone[1][11] = "Cb";
}

bool get_scale(string str, vector<string> &vec) {
	char st = str[0];
	int id = -1;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 2; j++) {
			if (tone[j][i] == str) {
				id = i;
			}
		}
	}
	if (id == -1) return false;
	vec.clear();
	vec.push_back(str);
	for (int i = 0; i < 7; i++) {
		int cur_id = (dx[i] + id) % 12;
		st++;
		if (st > 'G') st = 'A';
		if (tone[0][cur_id][0] == st) {
			vec.push_back(tone[0][cur_id]);
		} else if (tone[1][cur_id][0] == st) {
			vec.push_back(tone[1][cur_id]);
		} else return false;
		id = cur_id;
	}
	return true;
}

void solve(string line) {
	stringstream input(line);
	input >> s >> t;
	if (!get_scale(s, vec[0])) {
		printf("Key of %s is not a valid major key\n", s.c_str());
		return;
	}
	if (!get_scale(t, vec[1])) {
		printf("Key of %s is not a valid major key\n", t.c_str());
		return;
	}
	assert(vec[0].size() == 8);
	assert(vec[1].size() == 8);
	printf("Transposing from %s to %s:\n", s.c_str(), t.c_str());
	string query;
	while (input >> query, query != "*") {
		int id = -1;
		for (int i = 0; i < vec[0].size(); i++) {
			if (vec[0][i] == query) {
				id = i;
				break;
			}
		}
		if (id == -1) {
			printf("  %s is not a valid note in the %s major scale\n", query.c_str(), s.c_str());
		} else {
			printf("  %s transposes to %s\n", query.c_str(), vec[1][id].c_str());
		}
	}
}

int main() {
	init();
	string line;
	bool first = true;
	while (getline(cin, line)) {
		if (line == "*") break;
		if (first) {
			first = false;
		} else puts("");
		solve(line);
	}
	return 0;
}
