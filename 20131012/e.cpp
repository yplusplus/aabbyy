#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct point
{
	string name;
	int n,tot;
	vector<string> s;
	vector<int> val;
	void read() {
		tot = 0;
		val.clear();
		s.clear();
		cin >> name >> n;
		string str;
		int x;
		for(int i = 0; i < n; i ++) {
			cin >> str >> x;
			tot += x;
			s.push_back(str);
			val.push_back(x);
		}
	}
	void output() {
		cout << name << " " << n;
		for(int i = 0; i < n; i ++)
			cout << " " << s[i] << " " << val[i];
		cout << " " << tot << endl;
	}
	friend bool operator < (const point &p,const point &q) {
		if(p.tot != q.tot) return p.tot > q.tot;
		return p.name < q.name;
	}
}a[77];

int main()
{
	int t,n;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case #%d:\n",cas);
		scanf("%d",&n);
		for(int i = 1; i <= n; i ++) a[i].read();
		sort(a + 1,a + n + 1);
		for(int i = 1; i <= n; i ++) a[i].output();
	}
	return 0;
}

