#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int c[1 << 20],bit[35];

int get_max(int n)
{
    int ans = 0;
    for(int i = 0; i < 20; i ++) {
        if(bit[i] >= ((n + 1) >> 1)) ans += (1 << i);
    }
    if(c[ans] != (n + 1) / 2) return -1;
    return ans;
}

void dec(int x)
{
    for(int i = 0; i < 20; i ++)
        if(x & (1 << i)) bit[i] --;
    c[x] --;
}

void add(int x)
{
    for(int i = 0; i < 20; i ++)
        if(x & (1 << i)) bit[i] ++;
    c[x] ++;
}

void output(int x,int n)
{
    printf("%d",x);
    if(n == 1) printf("\n");
    else printf(" ");
}

int main()
{
    int n,x;
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d",&x);
        add(x);
    }
    int maxn = *max_element(c,c + (1 << 20));
    if(maxn > (n + 1) / 2) {
        cout << -1 << endl;
        return 0;
    }
    int min_pt1 = 0,min_pt2 = 0;
    int pre = -1;
    while(n) {
        if(n & 1) {
            maxn = get_max(n);
            if(maxn != -1) {
                output(maxn,n);
                dec(maxn);
                pre = maxn;
            }
            else {
                while(!c[min_pt1]) min_pt1 ++;
                if(pre != min_pt1) {
                    dec(min_pt1);
                    output(min_pt1,n);
                    pre = min_pt1;
                }
                else {
                    min_pt2 = max(min_pt2,min_pt1 + 1);
                    while(!c[min_pt2]) min_pt2 ++;
                    dec(min_pt2);
                    output(min_pt2,n);
                    pre = min_pt2;
                }
            }
        }
        else {
                while(!c[min_pt1]) min_pt1 ++;
                if(pre != min_pt1) {
                    dec(min_pt1);
                    output(min_pt1,n);
                    pre = min_pt1;
                }
                else {
                    min_pt2 = max(min_pt2,min_pt1 + 1);
                    while(!c[min_pt2]) min_pt2 ++;
                    dec(min_pt2);
                    output(min_pt2,n);
                    pre = min_pt2;
                }            
        }
        n --;
    }
    return 0;
}
