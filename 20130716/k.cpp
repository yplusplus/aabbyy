#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

typedef unsigned long long ull;
const int N = 200010;
char s[N],str[N];
ull key1 = 31,key2 = 131;
struct point
{
	ull x,y;
	point() {}
	point(ull x,ull y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.x != q.x) return p.x < q.x;
		return p.y < q.y;
	}
};

set<point> st;
ull sum1[N],sum2[N];
ull p1[N],p2[N];

int main()
{
	p1[0] = p2[0] = 1;
	for(int i = 1; i < N; i ++) {
		p1[i] = p1[i - 1] * key1;
		p2[i] = p2[i - 1] * key2;
	}
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		bool flag = false;
		scanf("%s",s + 1);
		int n;
		scanf("%d",&n);
		st.clear();
		while(n --) {
			scanf("%s",str);
			ull val1 = 0,val2 = 0;
			for(int i = 0; str[i]; i ++) {
				val1 = val1 * key1 + (str[i] - 'a' + 1);
				val2 = val2 * key2 + (str[i] - 'a' + 1);
			}
			st.insert(point(val1,val2));
	//		printf("%llu %llu\n",val1,val2);
		}
		n = strlen(s + 1);
		for(int i = 1; i <= n && !flag; i ++) {
			sum1[i] = sum1[i - 1] * key1 + (s[i] - 'a' + 1);
			sum2[i] = sum2[i - 1] * key2 + (s[i] - 'a' + 1);
			int x = n - i;
			if(x - 1 >= 0 && x - 1 < i) {
				ull val1 = sum1[i] - sum1[x - 1] * p1[i - (x - 1)];
				ull val2 = sum2[i] - sum2[x - 1] * p2[i - (x - 1)];
				if(st.count(point(val1,val2))) flag = true;
			}
			if(x + 1 < i) {
				ull val1 = sum1[i] - sum1[x + 1] * p1[i - (x + 1)];
				ull val2 = sum2[i] - sum2[x + 1] * p2[i - (x + 1)];
				if(st.count(point(val1,val2))) flag = true;
			}
		}
		printf("Case #%d: ",cas);
		if(flag) printf("zplinti1\n");
		else printf("bearchild\n");
	}
	return 0;
}

