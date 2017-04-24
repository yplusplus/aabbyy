#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
struct point
{
	int x,y;
	void read() {
		scanf("%d%d",&x,&y);
	}
}a[N];
int c[N],b[N],ask[N],cnt;

int lowbit(int x)
{
	return x & (-x);
}

void insert(int x,int y)
{
	x = cnt - x + 1;
	for(int i = x; i < N; i += lowbit(i))
		c[i] = min(c[i],y);
}

int query(int x)
{
	x = cnt - x + 1;
	int ans = N;
	for(int i = x; i > 0; i -= lowbit(i))
		ans = min(ans,c[i]);
	return ans;
}

int find(int x)
{
	int lt = 1,rt = cnt,mid;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		if(b[mid] == x) return mid;
		else if(b[mid] > x) rt = mid - 1;
		else lt = mid + 1;
	}
	cout << "not find : "  << x << endl;
}

int find_right(int x)
{
	//cout << x <<" " << b[cnt] << " " << cnt <<  endl;
	int lt = 1,rt = cnt,mid;
	int ans = N;
	//for(int i = 1; i <= cnt; i ++) cout << b[i] << " ";
	//cout << endl;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		if(b[mid] >= x) {
			ans = mid;
			rt = mid - 1;
		}
		else lt = mid + 1;
	}
	return ans;
}

int main()
{
	int t,n,m;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		int tot = 0;
		for(int i = 1; i <= n; i ++) {
			a[i].read();
			b[++ tot] = a[i].x;
			b[++ tot] = a[i].y;
		}
		for(int i = 1; i <= m; i ++) {
			scanf("%d",&ask[i]);
			b[++ tot] = ask[i];
		}
		sort(b + 1,b + tot + 1);
		cnt = 1;
		for(int i = 2; i <= tot; i ++)
			if(b[i] != b[cnt]) b[++ cnt] = b[i];
	//	cout << "number : " << cnt << endl;
		for(int i = 0; i < N; i ++) c[i] = N;
		for(int i = 1; i <= n; i ++) {
			a[i].x = find(a[i].x);
			a[i].y = find(a[i].y);
			insert(a[i].y,a[i].x);
		}
		printf("Case %d:\n",cas);
		for(int i = 1; i <= m; i ++) {
			ask[i] = find(ask[i]);
			//cout << b[ask[i]] << " : " << ask[i] << endl;
			int ans = 0;
			int lt = 1,rt = 1000000000,mid;
			while(lt <= rt) {
				mid = (lt + rt) >> 1;
				int tt = find_right(b[ask[i]] + mid);
				//cout << tt << " "<< b[tt] << " " << b[ask[i]] + mid << endl;
				if(tt == N) {
					rt = mid - 1;
					continue;
				}
				int mix = query(tt);
				if(mix == N) {
					rt = mid - 1;
					continue;
				}
				if(b[ask[i]] - b[mix] >= mid) {
					lt = mid + 1;
					ans = mid;
				}
				else rt = mid - 1;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
