#include <bits/stdc++.h>
using namespace std;

deque<char> dq;
char s[500010];

int main()
{
	freopen("prefixes.in","r",stdin);
	freopen("prefixes.out","w",stdout);
	scanf("%s",s);
	dq.push_front(s[0]);
	for(int i = 1; s[i]; i ++) {
		if(s[i] <= dq[0]) dq.push_front(s[i]);
		else dq.push_back(s[i]);
	}
	for(int i = 0; i < dq.size(); i ++)
		printf("%c",dq[i]);
	printf("\n");
	return 0;
}
