#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

const int N = 26;
const int M = 1 << 7;
vector<string> prod[N];
typedef vector<string>::iterator vsit;
bool visit[N][M];
vector<int> prefix[N];
int len[M];
int n, limit;
bool vis[2][M];

bool is_raw(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

int append(int prefix, int suffix) {
    int l = len[suffix];
    while ((prefix >> limit) == 0 && l > 0) {
        prefix <<= 1;
        l--;
        prefix |= (suffix >> l & 1);
    }
    return prefix;
}

bool is_new_word(int ch, int now) {
    if (!visit[ch][now]) {
        visit[ch][now] = true;
        prefix[ch].push_back(now);
        return true;
    }
    return false;
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (vsit it = prod[i].begin(); it != prod[i].end(); it++) {
            if (is_raw(*it)) {
                int now = 1;
                for (int j = 0; j < it->length(); j++) {
                    now = append(now, (*it)[j] - '0' + 2);
                }
                is_new_word(i, now);
            }
        }
    }
    int all = 1 << limit << 1;
    while (true) {
        bool found = false;
        for (int ch = 0; ch < N; ch++) {
            for (vsit it = prod[ch].begin(); it != prod[ch].end(); it++) {
                bool *now = vis[0], *pre = vis[1];
                memset(now, false, sizeof(bool) * all);
                now[1] = true;
                for (int i = 0; i < it->length(); i++) {
                    swap(now, pre);
                    memset(now, false, sizeof(bool) * all);
                    char t = (*it)[i];
                    if (isdigit(t)) {
                        for (int j = 1; j < all; j++) {
                            if (pre[j]) {
                                now[append(j, t - '0' + 2)] = true;
                            }
                        }
                    } else {
                        for (int j = 1; j < all; j++) {
                            if (pre[j]) {
                                for (int k = 0; k < prefix[t - 'A'].size(); k++) {
                                    now[append(j, prefix[t - 'A'][k])] = true;
                                }
                            }
                        }
                    }
                }
                for (int j = 1; j < all; j++) {
                    if (now[j]) found |= is_new_word(ch, j);
                }
            }
        }
        if (!found) break;
    }
    vector<string> outputs;
    int start = 'S' - 'A';
    for (int i = 0; i < prefix[start].size(); i++) {
        int now = prefix[start][i];
        string word;
        while (len[now]) {
            word += (char)('0' + (now & 1));
            now >>= 1;
        }
        reverse(word.begin(), word.end());
        outputs.push_back(word);
    }
    sort(outputs.begin(), outputs.end());
    cout << outputs.size() << endl;
    for (int i = 0; i < outputs.size(); i++) {
        if (outputs[i] != "") cout << outputs[i] << endl;
        else cout << "eps" << endl;
    }
}

int main() {
    freopen("valid.in", "r", stdin);
    freopen("valid.out", "w", stdout);
    len[1] = 0;
    for (int i = 2; i < M; i++) {
        if ((i & (i - 1)) == 0) len[i] = len[i - 1] + 1;
        else len[i] = len[i - 1];
    }
    ios::sync_with_stdio(false);
    cin >> n >> limit;
    string line;
    getline(cin, line);
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        prod[line[0] - 'A'].push_back(line.substr(3, line.length() - 3));
    }
    solve();
    return 0;
}
