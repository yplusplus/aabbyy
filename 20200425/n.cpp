#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int k, n;

string dec2bin(int x) {
    string res;
    while (x > 0) {
        res += '0' + x % 2;
        x >>= 1;
    }
    while (res.size() < k + 1) res += '0';
    reverse(res.begin(), res.end());
    return res;
}

int encode(int x, int y) {
    int z = 0;
    string xbin = dec2bin(x);
    string ybin = dec2bin(y);
    for (int i = 0; i <= k; i++) {
        z <<= 1;
        z += xbin[i] - '0';
        z <<= 1;
        z += ybin[i] - '0';
    }
    return z;
}

int main() {
    cin >> n;
    while ((1 << k) < n) k++;
    //cout << k << endl;

    vector<pair<int, int> > vec(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = encode(i, j);
            int y;
            scanf("%d", &y);
            //cout << i << " " << j << " " << x << endl;
            vec[i * n + j] = {x, y};
        }
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        int j = i;
        while (j + 1 < vec.size() && vec[j + 1].second == vec[i].second) j++;
        if (i > 0) printf(" ");
        printf("%d,%d", vec[i].second, j - i + 1);
        i = j;
    }
    puts("");

    return 0;
}
