#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int a[N];

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n * m * 2; i ++)
			scanf("%d",&a[i]);
		sort(a + 1,a + n * m * 2 + 1);
		int lt = 0,rt = a[2 * n * m] - a[1],mid,ans = 0;
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			int tot = 0;
			int sum = 0;
			for(int i = 2; i <= n * m * 2; i ++) {
				if(a[i] - a[i - 1] <= mid) {
					i ++;
					tot ++;
					sum += 2 * (m - 1);
				}
				else if(sum) sum --;
				else {
					tot = -1;
					break;
				}
			}
			if(tot >= n) {
				//cout << mid << " " << tot << endl;
				ans = mid;
				rt = mid - 1;
			}
			else lt = mid + 1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
