#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

map<string,string> ma;

int main()
{
	string s;
	for(int i = 0; i < 4; i ++) {
		cin >> s;
		ma[s] = "gold";
	}
	for(int i = 0; i < 4; i ++) {
		cin >> s;
		ma[s] = "silver";
	}
	for(int i = 0; i < 4; i ++) {
		cin >> s;
		ma[s] = "bronze";
	}
	int n,a[110],m;
	string str,ss;
	scanf("%d",&n);
	for(int i = 0; i < n; i ++) {
		scanf("%d",&m);
		a[i] = 0;
		while(m --) {
			cin >> s >> ss >> str;
			if(!ma.count(s)) continue;
			if(ma[s] == str) a[i] ++;
		}
	}
	int maxn = -1;
	for(int i = 0; i < n; i ++)
		maxn = max(maxn,a[i]);
	int ans = 0;
	for(int i = 0; i < n; i ++)
		if(a[i] == maxn) ans += 5;
	cout << ans << endl;

	return 0;
}

