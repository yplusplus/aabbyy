#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int score[8] = { 10, 8, 6, 5, 4, 3, 2, 1};
const int N = 1111;
const int INF = 11111111;
char buf[N];

struct Node {
	int sum;
	string first, last;
	vector<int> rank;
	void fix() { while (rank.size() < 8) rank.push_back(INF); sort(rank.begin(), rank.end());}
} driver[N], team[N];

bool cmp_driver(Node a, Node b) {
	if (a.sum != b.sum) return a.sum > b.sum;
	for (int i = 0; i < 8; i++) if (a.rank[i] != b.rank[i]) return a.rank[i] < b.rank[i];
	if (a.last != b.last) return a.last < b.last;
	return a.first < b.first;
}

bool cmp_team(Node a, Node b) {
	if (a.sum != b.sum) return a.sum > b.sum;
	return a.first < b.first;
}

void getstr(string &str) {
	char ch;
	str = "";
	while ((ch = getchar()) == ' ') ;
	str += ch;
	while ((ch = getchar()) != '.') str += ch;
}

map<string, int> driver_id, team_id;
string driver_name, team_name, first, last;
int main() {
	//freopen("in", "r", stdin);
	int n, cas = 1;
	while (cin >> n && n) {
		int x, id;
		driver_id.clear(), team_id.clear();
		while (n--) {
			gets(buf);
			gets(buf);
			gets(buf);
			while (cin >> buf && strcmp(buf, "---")) {
				sscanf(buf, "%d", &x);
				cin >> first >> last;
				getstr(team_name);
				driver_name = first + " " + last;
				if (driver_id.find(driver_name) == driver_id.end()) {
					driver_id[driver_name] = driver_id.size();
					id = driver_id[driver_name];
					driver[id].first = first;
					driver[id].last = last;
					driver[id].sum = 0;
					driver[id].rank.clear();
				}
				id = driver_id[driver_name];
				driver[id].sum += score[x - 1];
				driver[id].rank.push_back(x);
				
				//cout << driver_name << endl;
				if (team_id.find(team_name) == team_id.end()) {
					team_id[team_name] = team_id.size();
					id = team_id[team_name];
					team[id].first = team_name;
					team[id].sum = 0;
					team[id].rank.clear();
				}
				id = team_id[team_name];
				team[id].sum += score[x - 1];
				team[id].rank.push_back(x);
			}
		}
		cout << "Season " << cas++ << ":" << endl;
		int tt;

		tt = driver_id.size();
		for (int i = 1; i <= tt; i++) driver[i].fix();
		sort(driver + 1, driver + tt + 1, cmp_driver);
		cout << "Drivers Standing:" << endl;
		for (int i = 1; i <= tt; i++) {
			string tmp = driver[i].first + " " + driver[i].last;
			printf("%-25s %d\n", tmp.c_str(), driver[i].sum);
		}
		cout << endl;

		tt = 0;
		tt = team_id.size();
		for (int i = 1; i <= tt; i++) team[i].fix();
		sort(team + 1, team + tt + 1, cmp_team);
		cout << "Teams Standing:" << endl;
		for (int i = 1; i <= tt; i++) printf("%-25s %d\n", team[i].first.c_str(), team[i].sum);
		cout << endl;
	}
	return 0;
}






