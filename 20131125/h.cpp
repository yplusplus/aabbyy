#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1111;
char grille[N][N];
char message[N][N];
int n;

void rotate() {
    char t[N][N];
    memcpy(t, grille, sizeof(t));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grille[i][j] = t[n - 1 - j][i];
        }
    }
}

string get_message() {
    string res = "";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grille[i][j] == 'O') res += message[i][j];
        }
    }
    return res;
}

int main() {
    while (~scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) scanf("%s", grille[i]);
        for (int i = 0; i < n; i++) scanf("%s", message[i]);
        int cnt = 4;
        string str = "";
        do {
            str += get_message();
            rotate();
        } while (--cnt);
        puts(str.c_str());
    }
    return 0;
}
