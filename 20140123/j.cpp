#include <bits/stdc++.h>
using namespace std;

const int N = 555;
int cur_time, n, m;

struct Treatment {
	int p, d, arr, id;
	Treatment(int p, int d, int arr, int id) : p(p), d(d), arr(arr), id(id) {}
	bool operator < (const Treatment &x) const {
		if (p != x.p) return p < x.p;
		return arr > x.arr;
	}
};

struct Patient {
	int arr, id;
	vector<Treatment> treatments;
	int cnt, done_time;
	void init(int arr_time, int _id) {
		id = _id;
		arr = arr_time;
		treatments.clear();
		cnt = done_time  = 0;
	}
	void add_treatment(int p, int d) {
		treatments.push_back(Treatment(p, d, arr, id));
	}
	bool operator < (const Patient &x) const {
		if (done_time != x.done_time) return done_time < x.done_time;
		return arr < x.arr;
	}
} p[N];

struct Doctor {
	int t, id;
	Doctor(int t, int id) : t(t), id(id) {}
	bool operator < (const Doctor &x) const {
		return t > x.t;
	}
};

void solve() {
	priority_queue<Doctor> doctor;
	priority_queue<Treatment> wait;
	for (int i = 0; i < n; i++) doctor.push(Doctor(cur_time, m));
	int cnt = 0, pos = 0, done = 0;
	while (1) {
		cur_time = doctor.top().t;
		while (!doctor.empty() && cur_time == doctor.top().t) {
			Doctor dc = doctor.top(); doctor.pop();
			cnt++;
			int id = dc.id;
			if (id == m) continue;
			if (p[id].cnt < p[id].treatments.size()) {
				wait.push(p[id].treatments[p[id].cnt]);
			//cout << "add = " << cur_time << endl;
			} else {
				done++;
			}
		}
		if (done == m) break;
		while (pos < m && p[pos].arr <= cur_time) {
			wait.push(p[pos].treatments[0]);
			//cout << "add = " << cur_time << endl;
			pos++;
		}
		while (cnt > 0 && !wait.empty()) {
			cnt--;
			Treatment t = wait.top(); wait.pop();
			p[t.id].cnt++;
			p[t.id].done_time = cur_time + t.d;
			doctor.push(Doctor(cur_time + t.d, t.id));
		}
		//if (cnt < n && pos < m && p[pos
		if (cnt == 0) continue;
		cur_time = 1 << 30;
		if (doctor.size()) cur_time = min(cur_time, doctor.top().t);
		if (pos < m) cur_time = min(cur_time, p[pos].arr);
		while (cnt) {
			cnt--;
			doctor.push(Doctor(cur_time, m));
		}
	}
	sort(p, p + m);
	for (int i = 0; i < m; i++) {
		printf("Patient %d released at clock = %d\n", p[i].arr, p[i].done_time);
	}
}

int main() {
	int Case = 1;
	while (~scanf("%d%d", &n, &cur_time), n + cur_time) {
		m = 0;
		int arr_time;
		while (scanf("%d", &arr_time) && arr_time != -1) {
			p[m].init(arr_time, m);
			int a, b;
			while (scanf("%d%d", &a, &b), a + b) {
				p[m].add_treatment(a, b);
			}
			m++;
		}
		//cout << "input ok" << endl;
		printf("Case %d:\n", Case++);
		solve();
	}
	return 0;
}
