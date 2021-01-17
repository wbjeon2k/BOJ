//BOJ3736

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

#define MAXI 20020
#define INF INT_MAX / 2

//ll sad[MAXI][MAXI], capacity[MAXI][MAXI], flow[MAXI][MAXI];
//ll group[MAXI];

vector<vector<int>> adjlist(MAXI);

int N, M;
ll mcost, mflow;
int source, sink;

vector<int> lmatch, rmatch, dist;

bool dfs(int here) {
    for (int i = 0; i < adjlist[here].size(); ++i) {
        int there = adjlist[here][i];
        if (!rmatch[there] || (dist[there] == dist[here] + 1 && dfs(rmatch[there]))) {
            lmatch[here] = there;
            rmatch[there] = here;
            return true;
        }
    }

    return false;
}

void hopcroftkarp() {
    mflow = 0;
    lmatch = vector<int>(MAXI, 0);
    rmatch = vector<int>(MAXI, 0);
    dist = vector<int>(MAXI, 0);

    while (1) {
        queue<int> q;

        for (int i = 1; i <= N; ++i) {
            if (lmatch[i] == 0) {
                dist[i] = 0;
                q.push(i);
            } else
                dist[i] = INF;
        }

        while (!q.empty()) {
            int here = q.front();
            q.pop();

            for (int i = 0; i < adjlist[here].size(); ++i) {
                int there = adjlist[here][i];
                if (rmatch[there] && dist[rmatch[there]] == INF) {
                    dist[there] = dist[here] + 1;
                    q.push(there);
                }
            }
        }

        int f = 0;
        for (int i = 1; i <= N; ++i) {
            if (lmatch[i] == 0 && dfs(i)) ++f;
        }
        if (f == 0) break;
        mflow += f;
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(NULL);

    //FILE* pFile = NULL;
    //pFile = fopen("d:\\Text.txt", "r");

    while (1) {
        adjlist.resize(MAXI);
        if (scanf("%d", &N) < 0) break;

        for (int i = 1; i <= N; ++i) {
            int s, e, t;
            scanf("%d : (%d)", &s, &t);
            ++s;
            for (int j = 0; j < t; ++j) {
                scanf("%d", &e);
                ++e;
                adjlist[s].push_back(e);
            }
        }

        hopcroftkarp();

        printf("%lld\n", mflow);

        adjlist.clear();
    }

    return 0;
}

/*
//jh05013's solution.
#include <bits/stdc++.h>
using namespace std;
void OJize(){cin.tie(NULL);ios_base::sync_with_stdio(false);}

// 1-indexed
const int INF = 0x3f3f3f3f;
struct Hopk{
	int n, m; vector<vector<int>> adj; vector<int> pu, pv, dist;
	Hopk(int N, int M):n(N),m(M),adj(N+1),pu(N+1),pv(M+1),dist(N+1,-1){}
	void connect(int a, int b){adj[a].push_back(b);}
	bool bfs(){
		queue<int> Q;
		for(int u=1; u<=n; u++){
			if(!pu[u]) dist[u] = 0, Q.push(u);
			else dist[u] = INF;
		}
		dist[0] = INF;
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			if(dist[u] >= dist[0]) continue;
			for(int v: adj[u]) if(dist[pv[v]] == INF){
				dist[pv[v]] = dist[u] + 1;
				Q.push(pv[v]);
			}
		}
		return dist[0] != INF;
	}
	bool dfs(int u){
		if(!u) return true;
		for(int v: adj[u])if(dist[pv[v]] == dist[u]+1 && dfs(pv[v])){
			pv[v] = u, pu[u] = v;
			return true;
		}
		dist[u] = INF;
		return false;
	}
	int send(){
		int match = 0;
		while(bfs()) for(int u=1; u<=n; u++) if(!pu[u]) match+= dfs(u);
		return match;
	}
};

bool tc(){
	int n; cin>>n;
	if(!cin) return false;
	Hopk G(n, n);
	for(int i=0; i<n; i++){
		string ig1; char ig2; cin>>ig1>>ig2;
		int m; cin>>m>>ig2;
		for(int j=0; j<m; j++){
			int x; cin>>x;
			G.connect(i+1, x-n+1);
		}
	}
	cout << G.send() << '\n';
	return true;
}

int main(){OJize();
	while(tc());
}
*/
