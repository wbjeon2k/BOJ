#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int label=0;
    vector<Node*> children;
    vector<int> cost;
};

Node tree[10010];

int max1[10010], max2[10010];

int costCalc(Node* root) {
    int t = root->children.size();
    int idx = root->label;
    if (t == 0) {
        return 0;
    }

    for (int i = 0; i < t; ++i) {
        int tmp = costCalc(root->children[i]) + root->cost[i];
        if (max1[idx] < tmp) {
            max2[idx] = max1[idx];
            max1[idx] = tmp;
        }
        else if (max2[idx] < tmp) {
            max2[idx] = tmp;
        }
    }

    return max1[idx];

}

int main()
{
    int N;
    scanf("%d", &N);

    memset(max1, 0, sizeof(max1));
    memset(max2, 0, sizeof(max2));


    for (int i = 1; i < N; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        tree[a].label = a;
        tree[a].children.push_back(&tree[b]);
        tree[a].cost.push_back(c);
    }

    costCalc(&tree[1]);

    int ans = 0;

    for (int i = 1; i < N; ++i) {
        ans = max(ans, max1[i] + max2[i]);
    }

    printf("%d", ans);

    return 0;
}

/*
//Nada's solution. 굳이 tree traversal 실습이 아니면 bfs가 역시 편하다.
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef pair <int, int> ii;
vector <ii> e[10002];
bool ch[10002];
int d[10002], n;

queue <int> q;

void bfs(int s){
    q.push(s);
    fill(d, d+n+1, 0);
    fill(ch, ch+n+1, 0);
    ch[s] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i=0; i<e[v].size(); i++){
            int p = e[v][i].first;
            int c = e[v][i].second;
            if(!ch[p]){
                ch[p] = 1;
                d[p] = d[v] + c;
                q.push( p );
            }
        }
    }
}

int main(){
    int a, b, c, mx=1;
    scanf("%d", &n);
    while(~scanf("%d %d %d", &a, &b, &c)){
        e[a].push_back(ii(b, c));
        e[b].push_back(ii(a, c));
    }

    bfs( 1 );
    for(int i=1; i<=n; i++)
        if(d[mx]<d[i]) mx = i;
    bfs( mx );

    int re = 0;
    for(int i=1; i<=n; i++)
        if(re < d[i]) re = d[i];
    printf("%d\n", re);
}


*/