#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int n, m, s[100005];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &s[i]);
            if (!s[i]) sum++;
        }
        if (sum <= m)
        {
            printf("%d\n", n);
        }
        else
        {
            int l = 0, r = -1, cnt = 0, ans = 0;
            while (r < n-1)
            {
                while (s[r+1] || cnt < m)
                {
                    r++;
                    if (!s[r]) cnt++;
                }
                ans = max(ans, r-l+1);
                while (r >= l && s[l])
                {
                    l++;
                }
                l++;
                cnt--;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
