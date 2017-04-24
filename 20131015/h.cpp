#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int N = 110;
string pre[N],suf[N];
int f[N];

int cal(string a,string b)
{
	int ans = 0;
	for(int i = 0; i + b.length() <= a.length(); i ++) {
		bool flag = true;
		for(int j = 0; j < b.length() && flag; j ++)
			if(a[i + j] != b[j]) flag = false;
		if(flag) ans ++;
	}
	return ans;
}

string get_pre(string a,int len)
{
	string s = "";
	for(int i = 0; i < a.length() && i < len; i ++)
		s += a[i];
	return s;
}

string get_suf(string a,int len)
{
	reverse(a.begin(),a.end());
	string s = "";
	for(int i = 0; i < a.length() && i < len; i ++)
		s += a[i];
	reverse(s.begin(),s.end());
	return s;
}

int main()
{
	memset(f,0,sizeof(f));
	string a,b,c;
	cin >> a >> b >> c;
	int x,y;
	int n;
	scanf("%d",&n);
	f[1] = cal(b,a);
	f[2] = cal(c,a);
	pre[1] = get_pre(b, a.length() - 1);
	suf[1] = get_suf(b, a.length() - 1);
	pre[2] = get_pre(c, a.length() - 1);
	suf[2] = get_suf(c, a.length() - 1);
	for(int i = 3; i <= n + 2; i ++) {
		scanf("%d%d",&x,&y);
		f[i] = (f[x] + f[y]) % mod;
		pre[i] = pre[x] + pre[y];
		pre[i] = get_pre(pre[i],a.length() - 1);
		suf[i] = suf[x] + suf[y];
		suf[i] = get_suf(suf[i],a.length() - 1);
		f[i] = (f[i] + cal(suf[x] + pre[y],a)) % mod;
	}
	cout << f[n + 2] << endl;
	return 0;
}

