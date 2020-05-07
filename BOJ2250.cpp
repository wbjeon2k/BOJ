#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int label;
    int level= -1;
    bool isLeft = false;
    Node* parent = NULL;
    Node* left = NULL;
    Node* right = NULL;
};

Node tree[10010];
int pos[10010];
int sub[10010];
int lv[1000][2];

int subsize(Node* n) {
    

    if (n == NULL) { 
        return 0;
    }

    if (sub[n->label] != -1) {
        return sub[n->label];
    }

    sub[n->label] = subsize(n->left) + subsize(n->right) + 1;

    return sub[n->label];
}

int LOC(Node* n) {

    
    if (n == NULL) {
        return 0;
    }

    if (pos[n->label] != -1) {
        return pos[n->label];
    }

    if (n->isLeft) {
        pos[n->label] = LOC(n->parent) - subsize(n->right) - 1;
    }
    else {
        pos[n->label] = LOC(n->parent) + subsize(n->left) + 1;
    }

    if (pos[n->label] < lv[n->level][0]) {
        lv[n->level][0] = pos[n->label];
    }
    if (pos[n->label] > lv[n->level][1]) {
        lv[n->level][1] = pos[n->label];
    }

    return pos[n->label];
}

int leveler(Node* n) {
    if (n->parent == NULL) {
        n->level = 1;
        return n->level;
    }

    if (n->level != -1) {
        return n->level;
    }

    n->level = leveler(n->parent) + 1;
    return n->level;
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        tree[a].label = a;
        
        if (b != -1) {
            tree[a].left = &tree[b];
            tree[b].label = b;
            tree[b].parent = &tree[a];
            tree[b].isLeft = true;
        }

        if (c != -1) {
            tree[a].right = &tree[c];
            tree[c].label = c;
            tree[c].parent = &tree[a];
        }
        
    }

    memset(pos, -1, sizeof(pos));
    memset(sub, -1, sizeof(sub));
    
    for (int i = 0; i < 1000; ++i) {
        lv[i][0] = INT_MAX - 10000;
        lv[i][1] = 0;
    }

    for (int i = 1; i <= N; ++i) {
        leveler(&tree[i]);
    }

    for (int i = 1; i <= N; ++i) {
        LOC(&tree[i]);
    }

    int ans = -1;
    int lans = 0;
    for (int i = 0; i < 1000; ++i) {
        if (lv[i][1] - lv[i][0] > ans) {
            lans = i;
            ans = lv[i][1] - lv[i][0];
        }
    }

    printf("%d %d", lans, ans+1);

    return 0;
}

/*
//degurii's solution.  역시 tree traversal 연습 용도가 아니면 graph 알고리즘이 편하다
#include <iostream>
using namespace std;
using pii = pair<int, int>;
#define INF 0x3f3f3f3f

int n, root;
pii p[10001], k[10001];
int m;
int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }
void dfs(int now, int level) {
    int l = p[now].first;
    int r = p[now].second;

    if(l != -1)
        dfs(l, level + 1);
    m++;
    k[level] = { min(k[level].first, m), max(k[level].second, m) };
    if(r != -1)
        dfs(r, level + 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    root = n * (n + 1) / 2;
    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        cin >> p[x].first >> p[x].second;
        if (p[x].first != -1)
            root -= p[x].first;
        if (p[x].second != -1)
            root -= p[x].second;
        k[i].first = INF;
        k[i].second = -INF;
    }
    k[n + 1] = { INF, -INF };
    dfs(root, 1);

    int ans = -1, breadth = -1;
    for (int i = 1; k[i] != pii{INF, -INF}; i++) {
        if (breadth < k[i].second - k[i].first + 1) {
            breadth = k[i].second - k[i].first + 1;
            ans = i;
        }
    }

    cout << ans << ' ' << breadth;
}

*/