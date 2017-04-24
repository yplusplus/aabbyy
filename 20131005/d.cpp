#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int N = 1111;
string str[N];
int main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> str[i];
        char prefix[10];
        cin >> prefix;
        for (int i = 0; i < n; i++) {
            if (str[i][0] == prefix[0]) cout << str[i] << endl;
        }
    }
}

