#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2000010;
int q[N];
char s[N];
bool visit[N];
int sum[N],minx[N];

int get_val(char c)
{
    if(c == 'C') return 1;
    return -1;
}

int solve1(int n)
{
    int top = 0,tail = 0;
    for(int i = 1; i <= 2 * n; i ++) {
        while(top < tail && i - q[top] >= n) top ++;
        while(top < tail && sum[i] <= sum[q[tail - 1]]) tail --;
        q[tail ++] = i;
        minx[i] = q[top];
    }
    int ans = 0;
    for(int i = n; i < 2 * n; i ++)
        if(sum[minx[i]] - sum[i - n] >= 0) {
            visit[i - n] = true;
            ans ++;
    //        cout << i - n << " ";
        }
    //cout << endl;
    return ans;
}

int solve2(int n)
{
    int top = 0,tail = 0;
    for(int i = 1; i <= 2 * n; i ++) {
        sum[i] = sum[i - 1] + get_val(s[i]);
    }
    for(int i = 1; i <= 2 * n; i ++) {
        while(top < tail && i - q[top] >= n) top ++;
        while(top < tail && sum[i] <= sum[q[tail - 1]]) tail --;
        q[tail ++] = i;
        minx[i] = q[top];
    }
    int ans = 0;
    for(int i = n + 1; i <= 2 * n; i ++) {
        if(visit[2 * n - i]) continue;
        if(sum[minx[i]] - sum[i - n] >= 0) ans ++;
    }
    //cout << endl;
    return ans;
}

int main()
{
    int t,n;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%s",s + 1);
        n = strlen(s + 1);
        for(int i = 1; i <= n; i ++)
            s[i + n] = s[i];
        for(int i = 0; i <= 2 * n; i ++) visit[i] = false;
        sum[0] = 0;
        for(int i = 1; i <= 2 * n; i ++) {
            sum[i] = sum[i - 1] + get_val(s[i]);
        }
        int ans1 = solve1(n);
        reverse(s + 1,s + 2 * n + 1);
        //cout << "yes" << endl;
        int ans2 = solve2(n);
        printf("Case %d: %d\n",cas,ans1 + ans2);
    }
    return 0;
}

