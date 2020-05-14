//unfinished
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100
#define pii pair<int,int>

int idx = 0;
int traverse[2 * Msize];
int traverseLoc[Msize];
vector<int> traverseDepth(2 * Msize, INT_MAX - 100);
vector< vector<pii>> adjList;
vector< vector<int>> tree;
int parentNode[Msize];
bool visited[Msize];

void buildtreebfs() {
   
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int here = q.front();
        q.pop();
        visited[here] = true;

        for (int i = 0; i < adjList[here].size(); ++i) {
            int there = adjList[here][i].first;
            if (!visited[there]) {
                tree[here].push_back(there);
                parentNode[there] = here;
                q.push(there);
            }
        }
    }

    return ;
}

void dfs(int here, int depth) {
    traverseLoc[here] = idx;
    traverse[idx] = here;
    traverseDepth[idx] = depth;
    ++idx;

    for (int i = 0; i < tree[here].size(); ++i) {
        int child = tree[here][i];
        dfs(child, depth + 1);
        traverse[idx] = here;
        traverseDepth[idx] = depth;
        ++idx;
    }

    return;
}

struct segtree {
    int n;
    vector<pii> stree;

    segtree(const vector<int>& a) {
        n = a.size();
        stree.resize(4 * n);
        init(a, 0, n - 1, 1);
    }

    pii init(const vector<int>& a, int left, int right, int node) {
        if (left == right) {
            stree[node] = make_pair( a[left], left );
            return stree[node];
        }

        int mid = (left + right) / 2;

        pii linit = init(a, left, mid, node * 2);
        pii rinit = init(a, mid + 1, right, node * 2 + 1);
        stree[node] = min(linit, rinit);
        return stree[node];
    }

    pii query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (left > nodeRight || right < nodeLeft) {
            return { INT_MAX - 100, 0 };
        }

        if (left <= nodeLeft && right >= nodeRight) {
            return stree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;
        pii lquery = query(left, right, node * 2, nodeLeft, nodeMid);
        pii rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);

        return min(lquery, rquery);
    }

    pii querycall(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

pii findRoute(int node, int lca, pii carry) {
    //printf("node %d lca %d\n", node ,lca);
    if (node == lca) return carry;

    //if (cnt == 0) carry = { -1, INT_MAX };

    int maxi = carry.first, mini = carry.second;
    int parent = parentNode[node];
    //printf("%d\n", parent);
    for (int i = 0; i < adjList[node].size(); ++i) {
        if (adjList[node][i].first == parent) {
            maxi = max(maxi, adjList[node][i].second);
            mini = min(mini, adjList[node][i].second);
            break;
        }
    }

    carry.first = maxi; carry.second = mini;
    return findRoute(parent, lca,carry);
}

int main()
{
    memset(visited, 0, sizeof(visited));
    memset(parentNode, 0, sizeof(parentNode));
    memset(traverse, 0, sizeof(traverse));
    memset(traverseLoc, 0, sizeof(traverseLoc));
    adjList.resize(Msize);
    tree.resize(Msize);

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N-1; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adjList[a - 1].push_back({ b - 1,c });
        adjList[b - 1].push_back({ a - 1,c });
    }

    buildtreebfs();

    idx = 0;
    dfs(0, 0);
    segtree S(traverseDepth);

    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);

        int lu = traverseLoc[a - 1];
        int lv = traverseLoc[b - 1];
        if (lu > lv) swap(lu, lv);


        pii qlca = S.querycall(lu, lv);
        int lca = traverse[qlca.second];
        //printf("lca %d\n", lca);

        pii t = findRoute(a-1, lca, { -1, INT_MAX });
        int maxi=-1, mini = INT_MAX;

        maxi = max(maxi, t.first);
        mini = min(mini, t.second);

        t = findRoute(b-1, lca, { -1, INT_MAX });

        maxi = max(maxi, t.first);
        mini = min(mini, t.second);

        printf("%d %d\n", mini, maxi);
    }

    return 0;
}
