#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 11;
char mat[N][N];
int cur;

void init() { cur = 0;}

void getmat(int n) {
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) mat[i][j] = ' ';
    for (int i = 0; i < n; i++) mat[i][0] = 'a' + cur++, cur %= 26;
    for (int i = 1; i < n - 1; i++) mat[n - i - 1][i] = 'a' + cur++, cur %= 26;
    for (int i = 0; i < n; i++) mat[i][n - 1] = 'a' + cur++, cur %= 26;
    for (int i = 0; i < n; i++) cout << mat[i] << endl;
}

int main() {
    init();
    for (int i = 3; i <= 10; i++) getmat(i);
    return 0;
}

