#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int N = 70010;
int a[N],b[N];
set<int> st[N];
int cnt;

int find(int x)
{
        int lt = 1,rt = cnt,mid,ans = -1;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(b[mid] == x) {
                ans = mid;
                break;
            }
            else if(b[mid] > x) rt = mid - 1;
            else lt = mid + 1;
        } 
     return ans;
}

int main()
{
    int n,m,x,y,z;
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d",&a[i]);
        b[i] = a[i];
    }
    sort(b + 1,b + n + 1);
    cnt = 1;
    for(int i = 2; i <= n; i ++)
        if(b[i] != b[cnt]) b[++ cnt] = b[i];
    for(int i = 1; i <= n; i ++) {
        a[i] = find(a[i]);
        st[a[i]].insert(i);
    }
    scanf("%d",&m);
    while(m --) {
        scanf("%d%d%d",&x,&y,&z);
        z = find(z);
        if(z == -1) {
            printf("0");
            continue;
        }
        set<int>::iterator it = st[z].lower_bound(x);
        if(it == st[z].end() || (*it) > y) printf("0");
        else printf("1");
    }
    printf("\n");
    return 0;
}


