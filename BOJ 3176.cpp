#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define Msize 100100

vector<vector<pii>> adjList;
vector<vi> tree;
int depth[Msize];
int parent[Msize][30];
int maxi[Msize][30];
int mini[Msize][30];
bool visited[Msize];

int N, K;

void dfsmaketree(int here, int dep) {
    visited[here] = true;
    depth[here] = dep;
    
    for (int i = 0; i < adjList[here].size(); ++i) {
        int there = adjList[here][i].first;
        int dist = adjList[here][i].second;
        if (!visited[there]) {
            parent[there][0] = here;
            maxi[there][0] = dist;
            mini[there][0] = dist;
            tree[here].push_back(there);
            dfsmaketree(there, dep + 1);
        }
    }
}

void proctree() {
    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j <= N; ++j) {
            parent[j][i] = parent[parent[j][i - 1]][i - 1];
            maxi[j][i] = max(maxi[j][i-1], maxi[parent[j][i - 1]][i - 1]);
            //maxi[j][i] 는 2^(i-1) 까지 최대 or  2^(i-1) 에서 2^i 까지 최대
            mini[j][i] = min(mini[j][i-1], mini[parent[j][i - 1]][i - 1]);
        }
    }
}

pii lca(int x, int y) {
    int a = x, b = y;
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
 
    int ansmin = INT_MAX - 10000;
    int ansmax = -ansmin;

    for (int i = 19; i >=0; --i) {
        if (depth[a] - depth[b] >= (1 << i)) {
            ansmin = min(ansmin, mini[a][i]);
            ansmax = max(ansmax, maxi[a][i]);
            a = parent[a][i];
        }
    }

    if (a == b) {
        //printf("lca %d %d\n", a, b);
        return { ansmax, ansmin };
    }

    for (int i = 19; i >= 0; --i) {
        if (parent[a][i] != parent[b][i]) {
            ansmin = min(ansmin, min( mini[a][i], mini[b][i]));
            ansmax = max(ansmax, max(maxi[a][i], maxi[b][i]));
            a = parent[a][i];
            b = parent[b][i];
        }
    }

    ansmin = min(ansmin, min(mini[a][0], mini[b][0]));
    ansmax = max(ansmax, max(maxi[a][0], maxi[b][0]));

    //printf("lca %d %d\n", parent[a][0], parent[b][0]);

    return { ansmax, ansmin };
}

int main() {
    memset(visited, 0, sizeof(visited));
    memset(parent, 0, sizeof(parent));
    memset(maxi, 0, sizeof(maxi));
    memset(mini, 0, sizeof(mini));
    memset(depth, 0, sizeof(depth));

    adjList.resize(Msize);
    tree.resize(Msize);

    scanf("%d", &N);


    for (int i = 0; i < N - 1; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adjList[a].push_back({ b, c });
        adjList[b].push_back({ a, c });
    }

    dfsmaketree(1, 0);
    proctree();

    scanf("%d", &K);
    for (int i = 0; i < K; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        pii ans = lca(a, b);
        printf("%d %d\n", ans.second, ans.first);
    }

    return 0;
}

//first trial TLE
/*
/#define _CRT_SECURE_NO_WARNINGS
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

*/

/*
//koosaga's solution.
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n;
vector<pi> graph[100005];
int depth[100005];
int pa[100005][17], minv[100005][17], maxv[100005][17];

void dfs(int x, int p, int e, int d){
    if(x != 1){
        pa[x][0] = p;
        minv[x][0] = e;
        maxv[x][0] = e;
        depth[x] = d;
        for (int i=1; (1<<i) <= d; i++) {
            pa[x][i] = pa[pa[x][i-1]][i-1];
            minv[x][i] = min(minv[pa[x][i-1]][i-1],minv[x][i-1]);
            maxv[x][i] = max(maxv[pa[x][i-1]][i-1],maxv[x][i-1]);
        }
    }
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i].second == p) continue;
        dfs(graph[x][i].second,x,graph[x][i].first,d+1);
    }
}

inline void query(int a, int b){
    int diff = depth[b] - depth[a];
    int minr = 1e9, maxr = 0;
    for (int i=0; diff; i++) {
        if(diff&1){
            minr = min(minr,minv[b][i]);
            maxr = max(maxr,maxv[b][i]);
            b = pa[b][i];
        }
        diff >>= 1;
    }
    for (int i=16; i>=0; i--) {
        if(pa[a][i] != pa[b][i]){
            minr = min(minr,minv[a][i]);
            maxr = max(maxr,maxv[a][i]);
            minr = min(minr,minv[b][i]);
            maxr = max(maxr,maxv[b][i]);
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    if(a != b){
        minr = min(minr,minv[a][0]);
        maxr = max(maxr,maxv[a][0]);
        minr = min(minr,minv[b][0]);
        maxr = max(maxr,maxv[b][0]);
    }
    printf("%d %d\n",minr,maxr);
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        graph[a].push_back(pi(c,b));
        graph[b].push_back(pi(c,a));
    }
    dfs(1,0,0,0);
    int q;
    scanf("%d",&q);
    while (q--) {
        int a,b;
        scanf("%d %d",&a,&b);
        if(depth[a] > depth[b]) swap(a,b);
        query(a,b);
    }
}
*/