#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> a,b;

int main()
{
	char s[15];
	int n,m;
	scanf("%d",&n);
	a.push_back(2);
	b.push_back(10);
	while(n --) {
		scanf("%d%s",&m,s);
		if(s[0] == 'h') a.push_back(m);
		else b.push_back(m);
	}
	if(!a.size() || !b.size()) printf("Inconsistent\n");
	else {
		sort(a.begin(),a.end());
		sort(b.begin(),b.end());
		if(a.back() >= b[0]) printf("Inconsistent\n");
		else printf("%d\n",b[0]);
	}
	return 0;
}


