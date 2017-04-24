#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int a = 0, b = 0, c;
        for (int i = 0; i < n; i++) {
            cin >> c;
            a += c;
        }
        for (int i = 0; i < m; i++) {
            cin >> c;
            b += c;
        }
        if (a > b) cout << "Calem" << endl;
        else if (a < b) cout << "Serena" << endl;
        else cout << "Draw" << endl;
    }
    return 0;
}
