#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int N = 500010;
int a[N],b[N],size[N];
set<int> st;
multiset<int> stt;

int ABS(int x)
{
    return x < 0 ? (-x) : x;
}

int main()
{
    char s[15];
    int n,m;
    int x,y;
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 0; i < N; i ++) {
            size[i] = 0;
        }
        stt.clear();
        st.clear();
        int mx = -0x7fffffff;
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&x);
            a[i] = b[i] = x;
            size[i] = 1;
            st.insert(x);
            if(i > 1) {
                stt.insert(ABS(a[i] - a[i - 1]));
            }
        }
        int mi = 0x7fffffff;
        if(st.size() < n) mi = 0;
        else {
            for(int i = 1; i <= n; i ++) {
                set<int>::iterator it = st.lower_bound(a[i]);
                it ++;
                if(it != st.end()) mi = min(mi,ABS((int)(*it) - a[i]));
                it --;
                if(it != st.begin()) {
                    it --;
                    mi = min(mi,ABS(a[i] - (int)(*it)));
                }
            }
        }        
        while(m --) {
            scanf("%s",s);
            if(s[0] == 'I') {
                scanf("%d%d",&x,&y);
                if(x < n) {
                    multiset<int>::iterator it = stt.find(ABS(b[x] - a[x + 1]));
                    stt.erase(it);
                }

                stt.insert(ABS(b[x] - y));
                size[x] ++;
                b[x] = y;

                if(x < n) {
                    stt.insert(ABS(b[x] - a[x + 1]));
                }

                set<int>::iterator itt = st.lower_bound(y);
                if(itt != st.end()) {
                    mi = min(mi,(int)(*itt) - y);
                }
                if(itt != st.begin()) {
                    itt --;
                    mi = min(mi,y - (int)(*itt));
                }
                st.insert(y);       
            }
            else if(s[1] == 'i') {
                printf("%d\n",mi);
            }
            else {
                multiset<int>::iterator it = stt.end();
                it --;
                printf("%d\n",(int)(*it));
            }
        }
    }
    return 0;
}
