//BOJ11111

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 3300

int N, M;

vector<int> adjlist[MAXI];
ll dist[MAXI][MAXI], flow[MAXI][MAXI], capacity[MAXI][MAXI];

ll mcost, mflow;

int source, sink;
int board[55][55];
int value[6][6] = { {0,0,0,0,0,0},{0,10,8,7,5,1},{0,8,6,4,3,1},{0,7,4,3,2,1},{0,5,3,2,2,1},{0,1,1,1,1,0} };
//{i,j} = 55*i + j;


int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

//x,y: x행 y열
bool isinside(const int& x, const int& y) {
	if (x<1 || x>M || y<1 || y>N) return false;
	return true;
}

inline int getnode(const int& x, const int& y) {
	return (55 * x) + y;
}

void mcmf() {
	mcost = mflow = 0;

	while (1) {
		int parent[MAXI], upper[MAXI];
		bool isinq[MAXI] = { 0, };

		memset(parent, -1, sizeof(parent));
		fill(upper, upper + MAXI, INT_MAX / 2);

		queue<int> q;
		q.push(source);
		isinq[source] = true;
		upper[source] = 0;

		while (!q.empty()) {
			int here = q.front();
			q.pop();
			isinq[here] = false;

			for (int i = 0; i < adjlist[here].size(); ++i) {
				int there = adjlist[here][i];
				if (capacity[here][there] - flow[here][there] > 0 && upper[there] > upper[here] + dist[here][there]) {
					upper[there] = upper[here] + dist[here][there];
					parent[there] = here;

					if (!isinq[there]) {
						q.push(there);
						isinq[there] = true;
					}
				}
			}

		}

		if (parent[sink] == -1) break;

		ll b = INT_MAX;
		for (int i = sink; i != source; i = parent[i]) {
			b = min(b, capacity[parent[i]][i] - flow[parent[i]][i]);
		}

		for (int i = sink; i != source; i = parent[i]) {
			flow[parent[i]][i] += b;
			flow[i][parent[i]] -= b;
		}

		mflow += b;
		mcost += upper[sink] * b;

	}
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	scanf("%d %d", &M, &N);

	memset(dist, 0, sizeof(dist));
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));


	//get input
	for (int i = 1; i <= M; ++i) {
		char buf[55];
		scanf("%s", &buf);
		for (int j = 0; j < N; ++j) {
			buf[j] -= 'A';
			if (buf[j] > 4) buf[j] = 4;
			board[i][j + 1] = buf[j] + 1;
		}
	}

	source = 0, sink = MAXI - 1;

	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j) {
			int node = getnode(i, j);

			adjlist[node].push_back(sink);
			adjlist[sink].push_back(node);
			capacity[node][sink] = 1;

			int here = board[i][j];

			if ((i + j) % 2 == 0) {
				adjlist[source].push_back(node);
				adjlist[node].push_back(source);
				capacity[source][node] = 1;
				//dist=0,backward=0;

				int nx, ny;
				for (int k = 0; k < 4; ++k) {
					nx = i + dx[k];
					ny = j + dy[k];
					if (!isinside(nx, ny)) continue;

					int next = getnode(nx, ny);
					int there = board[nx][ny];

					adjlist[node].push_back(next);
					capacity[node][next] = 1;
					dist[node][next] = -value[here][there];

					adjlist[next].push_back(node);
					dist[next][node] = -dist[node][next];
				}
			}
		}
	}

	mcmf();

	printf("%lld\n", -mcost);

	return 0;

}

/*
//shiftps's solution.
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


// ref: https://github.com/koosaga/olympiad/blob/master/Library/codes/graph_optimization/mincostflow_fast.cpp

const int MAXN = 40002;

struct edg {
    int pos, cap, rev, cost;
};
vector<edg> gph[MAXN];

void clear() {
    for (int i = 0; i < MAXN; i++)
        gph[i].clear();
}

void add_edge(int s, int e, int x, int c) {
    gph[s].push_back({e, x, (int)gph[e].size(), c});
    gph[e].push_back({s, 0, (int)gph[s].size() - 1, -c});
}

int phi[MAXN], inque[MAXN], dist[MAXN];

void prep(int src, int sink) {
    memset(phi, 0x3f, sizeof(phi));
    memset(dist, 0x3f, sizeof(dist));
    queue<int> que;
    que.push(src);
    inque[src] = 1;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        inque[x] = 0;
        for (auto &i : gph[x]) {
            if (i.cap > 0 && phi[i.pos] > phi[x] + i.cost) {
                phi[i.pos] = phi[x] + i.cost;
                if (!inque[i.pos]) {
                    inque[i.pos] = 1;
                    que.push(i.pos);
                }
            }
        }
    }
    for (int i = 0; i < MAXN; i++) {
        for (auto &j : gph[i]) {
            if (j.cap > 0) j.cost += phi[i] - phi[j.pos];
        }
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(pii(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        auto l = pq.top();
        pq.pop();
        if (dist[l.second] != l.first) continue;
        for (auto &i : gph[l.second]) {
            if (i.cap > 0 && dist[i.pos] > l.first + i.cost) {
                dist[i.pos] = l.first + i.cost;
                pq.push(pii(dist[i.pos], i.pos));
            }
        }
    }
}

bool vis[MAXN];
int ptr[MAXN];

int dfs(int pos, int sink, int flow) {
    vis[pos] = 1;
    if (pos == sink) return flow;
    for (; ptr[pos] < gph[pos].size(); ptr[pos]++) {
        auto &i = gph[pos][ptr[pos]];
        if (!vis[i.pos] && dist[i.pos] == i.cost + dist[pos] && i.cap > 0) {
            int ret = dfs(i.pos, sink, min(i.cap, flow));
            if (ret != 0) {
                i.cap -= ret;
                gph[i.pos][i.rev].cap += ret;
                return ret;
            }
        }
    }
    return 0;
}

int match(int src, int sink, int sz = MAXN) {
    prep(src, sink);
    for (int i = 0; i < sz; i++)
        dist[i] += phi[sink] - phi[src];
    int ret = 0;
    while (true) {
        memset(ptr, 0, sizeof(ptr));
        memset(vis, 0, sizeof(vis));
        int tmp = 0;
        while ((tmp = dfs(src, sink, 1e9))) {
            ret += dist[sink] * tmp;
            memset(vis, 0, sizeof(vis));
        }
        tmp = 1e9;
        for (int i = 0; i < sz; i++) {
            if (!vis[i]) continue;
            for (auto &j : gph[i]) {
                if (j.cap > 0 && !vis[j.pos]) {
                    tmp = min(tmp, (dist[i] + j.cost) - dist[j.pos]);
                }
            }
        }
        if (tmp > 1e9 - 200) break;
        for (int i = 0; i < sz; i++) {
            if (!vis[i]) dist[i] += tmp;
        }
    }
    return ret;
}

string b[200];

constexpr const int _cost[6][6] = {
    {10, 8, 7, 5, 1, 1},
    {8, 6, 4, 3, 1, 1},
    {7, 4, 3, 2, 1, 1},
    {5, 3, 2, 2, 1, 1},
    {1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 0, 0}};

constexpr int cost(char u, char v) {
    return _cost[u - 'A'][v - 'A'];
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> b[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int k = i * m + j;
            add_edge(k + 1, n * m + 1, 1, 0);
            if ((i + j) & 1) continue;

            add_edge(0, k + 1, 1, 0);
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (0 > ni || ni >= n) continue;
                if (0 > nj || nj >= m) continue;
                int nk = ni * m + nj;
                int c = (cost(b[i][j], b[ni][nj]));
                add_edge(k + 1, nk + 1, 1, -c);
            }
        }
    }

    cout << -match(0, n * m + 1);

    return 0;
}
*/
