#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
 
using namespace std;
int ans[222];
int n, k, a, b;
int main() {
    while (cin >> n >> k >> a >> b) {
        int aoffset = 0, boffset = 0, x;
        priority_queue<int> A, B;
        for (int i = 0; i < n; i++) {
            cin >> x;
            if (x <= k) A.push(x);
            else B.push(x);
        }
        ans[0] = B.size();
        for (int i = 1; i < 222; i++) {
            if (!B.empty()) {
                int bm = B.top();
                B.pop();
                A.push(-aoffset);
            }
            aoffset += a;
            while (!A.empty()) {
                int am = A.top();
                am += aoffset;
                if (am <= k) break;
                A.pop();
                B.push(am - boffset);
                boffset += b;
            }
            ans[i] = B.size();
        }
        int q;
        cin >> q;
        while (q--) {
            cin >> x;
            cout << ans[x - 1] << endl;
        }
    }
    return 0;
}

