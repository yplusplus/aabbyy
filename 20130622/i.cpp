#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<string> v[15];

void dfs(int n)
{
	if(n == 1) {
		v[1].push_back("0");
		return;
	}
	dfs(n - 1);
	for(int i = 0; i < v[n - 1].size(); i ++) {
		int maxn = 0;
		for(int j = 0; j < v[n - 1][i].size(); j ++) {
			if(v[n - 1][i][j] - '0' > maxn)
				maxn = v[n - 1][i][j] - '0';
		}
		maxn ++;
		if(i & 1) {
			for(int j = 1; j <= maxn; j ++) {
				string tmp = v[n - 1][i];
				tmp += (char)(j + '0');
				v[n].push_back(tmp);
			}
			string tmp = v[n - 1][i];
			tmp += '0';
			v[n].push_back(tmp);
		}
		else {
			string tmp = v[n - 1][i];
			tmp += '0';
			v[n].push_back(tmp);
			for(int j = maxn; j >= 1; j --) {
				tmp = v[n - 1][i];
				tmp += (char)(j + '0');
				v[n].push_back(tmp);
			}
		}
	}
}

int main()
{
	int n;
	cin >> n;
	dfs(n);
	cout << v[n].size() << endl;
	for(int i = 0; i < v[n].size(); i ++) {
		vector<int> vv[10];
		int ct = 0;
		for(int j = 0; j < 10; j ++) {
			bool f = false;
			for(int k = 0; k < v[n][i].size(); k ++) {
				if(v[n][i][k] - '0' == j) vv[j].push_back(k + 1),f = true;
			}
			if(f) {
				ct ++;
				if(ct > 1) printf(",");
				printf("{");
				for(int k = 0; k < vv[j].size(); k ++) {
					printf("%d",vv[j][k]);
					if(k + 1 < vv[j].size()) printf(",");
				}
				printf("}");
			}
		}
		printf("\n");
	}
	return 0;
}

