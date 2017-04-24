#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long n;
	while(scanf("%lld",&n) != EOF) {
		if(n <= 5) printf("The stranger will win!!\n");
		else if(n > 7) printf("I will win!!\n");
		else printf("It's an endless game!!\n");
	}
	return 0;
}
