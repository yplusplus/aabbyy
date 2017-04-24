#include <iostream>
#include <set>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <map>
#include <climits>
#include <deque>
#include <vector>
using namespace std;

int n;
int str2int(string str) {
    if (str == "IN") return 0;
    else if (str == "OUT") return 1;
    else if (str == "COLLECT") return 3;
    return 2;
}

deque<pair<int, int> > commands;

void decompose(set<int> &multiple, int x) {
    for (int j = 1; j * j <= x; j++) {
        if (x % j) continue;
        int y = j;
        int z = x / j;
        multiple.insert(y);
        multiple.insert(z);
    }
}

void solve() {
    vector<pair<int, int> > buffer;
    //cout << commands.size() << endl;
    while (commands.size() && commands[0].first == 2) commands.pop_front();
    while (commands.size() && commands.back().first == 2) commands.pop_back();
    //cout << commands.size() << endl;
    int minCnt = 1, delta = 0;
    for (int i = 0, j; i < commands.size(); i = j) {
        int d = 0;
        j = i;
        if (commands[i].first == 2) {
            while (j < commands.size() && commands[j].first == 2) {
                d += commands[j++].second;
            }
        } else {
            d = commands[i].second;
            if (commands[i].first == 0) {
                delta += d;
            } else {
                delta -= d;
            }
            minCnt = max(minCnt, -delta + 1);
            j++;
        }
        buffer.push_back(make_pair(commands[i].first, d));
    }
    delta = 0;
    map<int, int> cnt;
    int payCnt = 0;
    //cout << "minCnt = " << minCnt << endl;
    for (int i = 0; i < buffer.size(); i++) {
        //cout << buffer[i].first << " " << buffer[i].second << endl;
        if (buffer[i].first == 0) {
            delta += buffer[i].second;
        } else if (buffer[i].first == 1) {
            delta -= buffer[i].second;
        } else {
            set<int> multiple;
            decompose(multiple, buffer[i].second);
            //cout << "*********** " << buffer[i].second << endl;
            for (set<int>::iterator it = multiple.begin(); it != multiple.end(); it++) {
                //cout << *it << endl;
                //assert(*it > delta);
                if (*it - delta >= minCnt) {
                    //cout << *it << " " << delta << " " << *it - delta << endl;
                    cnt[*it - delta]++;
                }
            }
            payCnt++;
        }
        //cout << i << " " << minCnt << endl;
    }
    if (payCnt == 0) {
        printf("SIZE >= %d\n", minCnt);
    } else {
        vector<int> answer;
        for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); it++) {
            if (it->second == payCnt) answer.push_back(it->first);
        }
        if (answer.empty()) puts("IMPOSSIBLE");
        else {
            for (int i = 0; i < answer.size(); i++) {
                printf("%d%c", answer[i], i == answer.size() - 1 ? '\n' : ' ');
            }
        }
    }
}

int main() {
    while (~scanf("%d", &n), n) {
        commands.clear();
        for (int i = 0; i < n; i++) {
            char cmd[20];
            int d;
            scanf("%s%d", cmd, &d);
            int cmdId = str2int(cmd);
            if (cmdId == 3) continue;
            commands.push_back(make_pair(cmdId, d));
        }
        solve();
    }
    return 0;
}
