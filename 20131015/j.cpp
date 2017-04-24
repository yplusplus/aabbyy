#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20010;
int a[N];
int b[N];
void cal(int st,int ed,int need,int m,long long &ans,long long &tot)
{
	for(int i = st - 1; i <= ed + 1; i ++) b[i] = 0;
	for(int i = st; i <= ed; i ++) b[i] = m - a[i];
	for(int i = ed; i >= st; i --) b[i] += b[i + 1];
	int left = 0;
	for(int i = st; i <= ed; i ++) {
		if(a[i] >= m) {
			ans += m;
			if(left >= a[i] - m) {
				ans += a[i] - m;
				left -= a[i] - m;
			}
			else {
				ans += left;
				left = 0;
			}
		}
		else {
			ans += a[i];
			left = min(left + m - a[i],-b[i + 1]);
		}
		tot += left;
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&a[i]);
	int i = n;
	long long ans = 0;
	long long tot = 0;
	while(i >= 1) {
		int j = i;
		long long need = 0;
		while(j >= 1 && (m - a[j]) + need < 0) {
			need += m - a[j];
			j --;
		}
		//cout << i << " " << j << endl;
		if(!j) cal(j + 1,i,need,m,ans,tot);
		else cal(j,i,need,m,ans,tot);
		i = j - 1;
	}
	cout << ans << " " << tot << endl;
	return 0;
}

