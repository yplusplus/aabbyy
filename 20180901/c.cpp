#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
#include <string.h>
#include <iostream>

#define pb push_back
#define mp make_pair
#define _cls(a) memset(a,-1,sizeof(a));
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define ll long long

using namespace std;

queue<int> card_pool;
vector<int> card[1000];
int n,m;

int draw(int num, int start) {
    int ret = 0;
    for(int i = 0; i < n; ++i) {
        if(card_pool.empty()) {
            return ret;
        }
        int idx = (start+i)%n;
        for(int j = 0; j < num && !card_pool.empty(); ++j) {
            card[idx].pb(card_pool.front());
            card_pool.pop();
            ret = 1;
        }
    }
    return ret;
}

int send(int idx, int cur_card) {

   if(cur_card==-1) {
        int t = 0;
        for(int i = 0; i < card[idx].size();++i) {
            if(card[idx][i] < card[idx][t]) {
                t =i;
            }
        }
        cur_card = card[idx][t];
        if( t != card[idx].size()-1)
            swap(card[idx][t], card[idx][card[idx].size()-1]);
        card[idx].pop_back();
        return cur_card;
    }

    for(int i = 0; i < card[idx].size();++i) {
        int next_card = cur_card+1;
        if(card[idx][i] == next_card) {
            cur_card = card[idx][i];
            if( i != card[idx].size()-1)
                swap(card[idx][i], card[idx][card[idx].size()-1]);
            card[idx].pop_back();
            return cur_card;
        }
    }

    if(cur_card!=12) { 
        for(int i = 0; i < card[idx].size();++i) {
            if(card[idx][i] == 12) {
                cur_card = card[idx][i];
                if( i != card[idx].size()-1)
                    swap(card[idx][i], card[idx][card[idx].size()-1]);
                card[idx].pop_back();
                return cur_card;
            }
        }
    }
    return -1;
}

int get_res(int idx) {
    int sum = 0;
    for(int i =0; i < card[idx].size();++i) {
        int x = card[idx][i];
        x =x+3;
        if (x>13) {
            x = x-13;
        }
        //printf("card idx = %d x = %d\n",card[idx][i],x);
        sum += x;
    }
    return sum;
}

void play() {

    draw(5,0);
    int idx = 0;
    int cur = -1;
    int skip_num = 0;
    while(1) {
        idx %=n;
        int next_c = send(idx,cur);
        //printf("idx = %d play %d\n",idx,next_c);
        if(next_c != -1){
            cur = next_c;
            skip_num = 0;
            if(card[idx].size()==0) {
                return;
            }
            idx++;
            continue;
        }
        idx++;
        skip_num++;
        if(skip_num==n-1) {
            //printf("skip draw(), %d\n", idx);
            draw(1, idx);
            skip_num = 0;
            cur = -1;
        }
    }
}


int main() {
    int T;
    cin>>T;
    fr(t,0,T){
        cin>>n>>m;
        fr(i,0,m) {
            int t;
            cin>>t;
            t=(t-3+13)%13;
            card_pool.push(t);
        }
        play();
        printf("Case #%d:\n",t+1);
        for(int i = 0; i < n; ++i) {
            int sum = get_res(i);
            if(sum==0) {
                cout<<"Winner"<<endl;
            }
            else {
                cout<<sum<<endl;
            }
            card[i].clear();
        }
        while(!card_pool.empty()) {
            card_pool.pop();
        }
    }
}
