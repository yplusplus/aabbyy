#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


char str[100];
vector<string> vec[1111];
map<string, int> mp;
int n;

struct Word {
	string s;
	int cnt;
	Word(string s, int cnt) : s(s), cnt(cnt) {}
	bool operator < (const Word &x) const {
		if (cnt != x.cnt) return cnt > x.cnt;
		return s < x.s;
	}
};

int main() {
	int flag = 0;
	int days = 0;
	mp.clear();
	while (~scanf("%s", str)) {
		if (strcmp(str, "<text>") == 0) {
			flag = 1;
			days++;
			continue;
		}
		if (strcmp(str, "</text>") == 0) {
			flag = 0;
			if (days - 7 > 0) {
				int t = days - 7;
				for (int i = 0; i < vec[t].size(); i++) {
					mp[vec[t][i]]--;
				}
			}
			continue;
		}
		if (strcmp(str, "<top") == 0) {
			scanf("%d%s", &n, str);
			vector<Word> words;
			for (map<string, int>::iterator it = mp.begin(); it != mp.end(); it++) {
				if (it->second) {
					words.push_back(Word(it->first, it->second));
				}
			}
			sort(words.begin(), words.end());
			printf("<top %d>\n", n);
			for (int i = 0; i < n && i < words.size(); i++) {
				printf("%s %d\n", words[i].s.c_str(), words[i].cnt);
			}
			if (words.size() > n) {
				for (int i = n; i < words.size(); i++) {
					if (words[i].cnt == words[n - 1].cnt) {
						printf("%s %d\n", words[i].s.c_str(), words[i].cnt);
					}
				}
			}
			printf("</top>\n");
			continue;
		}
		if (flag) {
			if (strlen(str) < 4) continue;
			vec[days].push_back(str);
			mp[str]++;
		}
	}
	return 0;
}
