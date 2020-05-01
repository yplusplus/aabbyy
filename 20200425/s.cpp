#include <iostream>
#include <set>
#include <cstring>
#include <string>
using namespace std;

set<string> dict;

bool start_with(const string &a, const string &prefix) {
    return a.compare(0, prefix.length(), prefix) == 0;
}

int main() {
    int n;
    cin >> n;

    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        dict.insert(s);
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        auto it = dict.lower_bound(s);
        if (it == dict.end() || !start_with(*it, s)) dict.insert(s);
        cout << s << endl;
        it = dict.upper_bound(s);
        for (int i = 0; i < 49; i++) {
            if (it == dict.end()) break;
            if (!start_with(*it, s)) break;
            cout << *it << endl;
            it++;
        }
    }
    return 0;
}
