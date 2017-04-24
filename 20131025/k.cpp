#include <bits/stdc++.h>
using namespace std;

int get_val(char c)
{
	if(c >= '2' && c <= '9') return c - '0';
	else if(c == 'T') return 10;
	else if(c == 'J') return 11;
	else if(c == 'Q') return 12;
	else if(c == 'K') return 13;
	return 14;
}

bool check(string s,string str)
{
	if(s[1] != str[1]) return false;
	if(get_val(s[0]) + 1 != get_val(str[0])) return false;
	return true;
}

bool check(int n,vector<string> v[])
{
	if(n != 4) return false;
	for(int i = 0; i < 4; i ++) {
		if(v[i].size() != 13) return false;
		for(int j = 0; j < 12; j ++)
			if(!check(v[i][j],v[i][j + 1])) return false;
	}
	return true;
}

int main()
{
	int n = 4;
	vector<string> v[55],vv[55];
	for(int i = 0; i < 4; i ++) {
		string s;
		for(int j = 0; j < 13; j ++) {
			cin >> s;
			v[i].push_back(s);
		}
	}
	int ans = 0;
	while(1) {
		if(check(n,v)) break;
		bool flag = false;
		int id = -1;
		ans ++;
		/*
		if(ans < 5) {
			printf("%d %d\n",n,ans);
			for(int i = 0; i < n; i ++) {
				for(int j = 0; j < v[i].size(); j ++)
					cout << v[i][j] << " ";
				cout << endl;
			}
		}*/
		for(int i = 0; i < n && !flag; i ++) {
			for(int j = 0; j < n; j ++) {
				if(i == j) continue;
				for(int k = 0; k < v[j].size(); k ++) {
					if(check(v[j][k],v[i][0])) {
						flag = true;
						vector<string> tmp;
						for(int r = 0; r <= k; r ++) tmp.push_back(v[j][r]);
						for(int r = 0; r < v[i].size(); r ++) tmp.push_back(v[i][r]);
						v[i].clear();
						for(int r = 0;r < tmp.size(); r ++) v[i].push_back(tmp[r]);
						tmp.clear();
						for(int r = k + 1; r < v[j].size(); r ++) tmp.push_back(v[j][r]);
						v[j].clear();
						for(int r = 0; r < tmp.size(); r ++) v[j].push_back(tmp[r]);
						break;
					}
				}
				if(flag) break;
			}
		}
		if(flag) {
			vector<string> tmp;
			int cnt = 0;
			for(int i = 0; i < n; i ++) {
				if(v[i].size() == 0) continue;
				tmp.clear();
				for(int j = 0; j < v[i].size(); j ++)
					tmp.push_back(v[i][j]);
				v[i].clear();
				for(int j = 0; j < tmp.size(); j ++)
					v[cnt].push_back(tmp[j]);
				cnt ++;
			}
			n = cnt;
			continue;
		}
		for(int i = 0; i < n && !flag; i ++) {
			for(int j = 0; j + 1 < v[i].size(); j ++) {
				if(!check(v[i][j],v[i][j + 1])) {
					v[n].clear();
					for(int k = 0; k <= j; k ++)
					   v[n].push_back(v[i][k]);
					vector<string> tmp;
					for(int k = j + 1; k < v[i].size(); k ++)
						tmp.push_back(v[i][k]);
					v[i].clear();
					for(int k = 0; k < tmp.size(); k ++)
						v[i].push_back(tmp[k]);
					flag = true;
					n ++;
					break;
				}
			}
		}	
	}
	printf("%d\n",ans);
	return 0;
}

