#include <bits/stdc++.h>
using namespace std;

const int oo = -1000000000;
const int N = 50010;
struct tree
{
	int lt,rt,mx;
}a[N * 4];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].mx = oo;
	if(lt == rt) return;
	int mid = (lt + rt) >> 1;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void insert(int lt,int rt,int step,int mx)
{
	if(a[step].lt == a[step].rt) {
		a[step].mx = max(a[step].mx,mx);
		return;
	}
	if(rt <= a[2 * step].rt) insert(lt,rt,2 * step,mx);
	else if(lt > a[2 * step].rt) insert(lt,rt,2 * step + 1,mx);
	else {
		insert(lt,a[2 * step].rt,2 * step,mx);
		insert(a[2 * step + 1].lt,rt,2 * step + 1,mx);
	}
	a[step].mx = max(a[2 * step].mx,a[2 * step + 1].mx);
}

int query(int lt,int rt,int step)
{
	if(a[step].lt == lt && a[step].rt == rt) return a[step].mx;
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else return max(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

struct point
{
    int x,y,z;
    void read() {
        scanf("%d%d%d",&x,&y,&z);
    }
}c[N];

int main()
{
	int n;
    while(scanf("%d",&n) != EOF) {
        for(int i = 1; i <= n; i ++) c[i].read();
        init(1,n,1);
        for(int i = n; i >= 1; i --) {
            int lt = c[i].y + i,rt = c[i].z + i - 1;
            rt = min(rt,n);
            int tmp = 0;
            if(lt <= rt && rt <= n) tmp = query(lt,rt,1);
            tmp += c[i].x;
            if(i == 1) cout << tmp << endl;
            insert(i,i,1,tmp);
        }
    }
	return 0;
}


