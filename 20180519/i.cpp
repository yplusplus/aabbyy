#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

const int N = 111111;
int a[N];
int dp[N];
int n;
int b[N];
int m;
vector<int> vec[N];
int zeros[N];
int cnt[N];

int find_pos(int x) {
    int res = 0;
    int l = 0, r = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (b[mid] < x) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

long long calc() {

    zeros[0] = 0;
    for (int i = 1; i <= n; i++) {
        cnt[i] = 0;
        vec[i].clear();
        zeros[i] = zeros[i - 1] + (a[i] == 0);
    }
    
    if (zeros[n] == n) {
		return (1LL + n) * n / 2;
    }
	
    m = 0;
    b[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        int p = find_pos(a[i]) + 1;
        dp[i] = p;
        if (p > m) b[m = p] = a[i];
        else if (b[p] > a[i]) b[p] = a[i];
    }

    for (int i = n; i >= 1; i--) {
        if (a[i] == 0) continue;
        if (dp[i] == m) {
            vec[m].push_back(i);
        } else if (vec[dp[i] + 1].size() > 0 
                && a[vec[dp[i] + 1].back()] > a[i]) {

            vec[dp[i]].push_back(i);
            int l = 0, r = vec[dp[i] + 1].size() - 1;
            int res = i;
            while (l <= r) {
                int mid = (l + r) >> 1;
                int pos = vec[dp[i] + 1][mid];
                if (zeros[pos] - zeros[i] == 0) {
                    r = mid - 1;
                } else if (a[i] >= a[pos]) {
                    l = mid + 1;
                } else {
                    res = pos;
                    l = mid + 1;
                }
            }
            if (a[i] + 1 <= a[res] - 1) {
                cnt[a[i] + 1]++;
                cnt[a[res]]--;
            }
        }
    }

    for (int i = 0; i < vec[m].size(); i++) {
        int x = vec[m][i];
        if (zeros[n] - zeros[x] > 0) {
            if (a[x] + 1 <= n) {
                cnt[a[x] + 1]++;
                break;
            }
        }
    }

    for (int i = 0; i < vec[1].size(); i++) {
        int x = vec[1][i];
        if (zeros[x] - zeros[0] > 0) {
            if (1 <= a[x] - 1) {
                cnt[1]++;
                cnt[a[x]]--;
            }
        }
    }

    // calc ans
    long long ans = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += cnt[i];
        ans += 1LL * i * m;
        if (sum > 0) {
            ans += i;
        }
    }
    return ans;
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        long long ans = calc();
        cout << ans << endl;
    }
    return 0;
}