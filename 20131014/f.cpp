#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;
	if(n == 1) cout << 14 << endl;
	else if(n == 2) cout << 155 << endl;
	else if(n == 3) cout << 1575 << endl;
	else {
		cout << 1575;
		for(int i = 4; i <= n; i ++)
			printf("0");
		printf("\n");
	}
	return 0;
}

