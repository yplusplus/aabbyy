#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1500010;
struct node
{
	node *l,*r;
	int val;
}a[N],*root[N];

int ct = 0;
node *newnode()
{
	a[ct].l = a[ct].r = NULL;
	a[ct].val = 0;
	return &a[ct ++];
}

node *newnode(node *x)
{
	a[ct].l = x->l;
	a[ct].r = x->r;
	a[ct].val = x->val;
	return &a[ct ++];
}

void output(int x)
{
	if(x) printf("%d\n",x);
	else printf("basic\n");
}

int map[N];
int main()
{
	int n,m;
	char s[15];
	int x,y;
	scanf("%d%d",&n,&m);
	root[1] = newnode();
	map[1] = 1;
	int order = 1;
	int pos = 2;
	while(n --) {
		scanf("%s",s);
		if(!strcmp(s,"check")) {
			scanf("%d",&x);
			output(root[map[x]]->val);
		}
		else if(!strcmp(s,"clone")) {
			scanf("%d",&x);
			root[++ order] = newnode(root[map[x]]);
			map[pos ++] = order;
		}
		else if(!strcmp(s,"relearn")) {
			scanf("%d",&x);
			if(root[map[x]]->r) {
				root[++ order] = newnode(root[map[x]]);
				root[++ order] = newnode(root[map[x]]->r);
				root[order]->l = root[order - 1];
				root[order - 1]->r = root[order];
				int y = order;
				root[++ order] = newnode(root[y]);
				map[x] = order;
			}
		}
		else if(!strcmp(s,"rollback")) {
			scanf("%d",&x);
			if(root[map[x]]->l) {
				root[++ order] = newnode(root[map[x]]);
				root[++ order] = newnode(root[map[x]]->l);
				root[order]->r = root[order - 1];
				root[order - 1]->l = root[order];
				int y = order;
				root[++ order] = newnode(root[y]);
				map[x] = order;
			}
		}
		else {
			scanf("%d%d",&x,&y);
			node *tmp = newnode();
			tmp->val = y;
			root[++ order] = newnode(root[map[x]]);
			tmp->l = root[order];
			root[order]->r = tmp;
			root[++ order] = newnode(tmp);
			map[x] = order;
		}
	}
	return 0;
}
