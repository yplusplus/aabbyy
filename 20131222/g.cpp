#include <iostream>
using namespace std;

char str[11111];
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; Case++) {
        scanf("%s", str);
        printf("Case %d: %s\n", Case, (strlen(str) & 1) ? "Odd" : "Even");
    }
    return 0;
}

