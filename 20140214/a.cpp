#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int N = 22;
struct Node {
    int id;
    vector<Node *> c;
    Node() {}
    Node(int a) : id(a) { c.clear(); }
} *root;

map<string, int> id;
vector<DB> prob;
int n;

int get_id(const string &s) {
    if (id.find(s) != id.end()) return id[s];
    return id[s] = id.size() - 1;
}

string get_name(const string &s) {
    string t;
    for (int i = 6; s[i] != '<'; i++) t += s[i];
    return t;
}

DB get_val(const string &s) {
    string t; DB r;
    for (int i = 13; s[i] != '<'; i++) t += s[i];
    sscanf(t.c_str(), "%lf", &r);
    return r;
}

void build(Node *&rt, bool type) {
    if (type) {
        string name, val;
        cin >> name >> val;
        DB tmp = get_val(val);
        name = get_name(name);
        rt = new Node(get_id(name));
        prob[id[name]] = tmp;
        cin >> name;
    } else {
        string op;
        cin >> op;
        if (op[7] == 'o') rt = new Node(-1);
        else rt = new Node(-2);
        for (int i = 0; ; i++) {
            cin >> op;
            if (op[1] == '/') break;
            rt->c.push_back(0);
            if (op[1] == 'n') build(rt->c[i], 0);
            else build(rt->c[i], 1);
        }
    }
}

bool dfs(Node *&rt, int st) {
    if (rt->id >= 0) return (st & 1 << rt->id) != 0;
    if (rt->id == -1) {
        bool ok = 0;
        vector<Node *> &c = rt->c;
        for (int i = 0, sz = c.size(); i < sz; i++) ok |= dfs(c[i], st);
        return ok;
    } else {
        bool ok = 1;
        vector<Node *> &c = rt->c;
        for (int i = 0, sz = c.size(); i < sz; i++) ok &= dfs(c[i], st);
        return ok;
    }
}

DB get_tot() {
    int st = 1 << n;
    DB sum = 0;
    for (int i = 0; i < st; i++) {
        DB cur = 1;
        for (int j = 0; j < n; j++) {
            if (i & 1 << j) cur *= prob[j];
            else cur *= 1 - prob[j];
        }
        if (dfs(root, i)) sum += cur;
    }
    return sum;
}

int main() {
    //freopen("in", "r", stdin);
    cout << setiosflags(ios::fixed) << setprecision(3);
    string op;
    while (cin >> op) {
        id.clear();
        prob.resize(N);
        build(root, 0);
        n = id.size();
        cout << get_tot() << endl;
        cin >> op;
    }
    return 0;
}
