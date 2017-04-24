#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; Case++) {
        int n, m;
        scanf("%d%d", &n, &m);
        int cnt = 0;
        char line[111];
        for (int i = 0; i < n; i++) {
            scanf("%s", line);
            for (int j = 0; j < m; j++) cnt += line[j] == 'O';
        }
        printf("Case %d: %s\n", Case, (cnt & 1) ? "Maze" : "Fat brother");
    }
    return 0;
}
