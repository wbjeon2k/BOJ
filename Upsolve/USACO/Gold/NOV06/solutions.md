# USACO NOV06 Problem 'plank' Analysis

by Richard Peng

This problem is the classical Huffman code problem, which asks for the minimum cost of placing all the vertices on the leaves of a binary tree where the cost is defined as weight of node* depth of node. It's quite clear these two problems are equivalent as each combining of two boards is equivalent to moving the two nodes up one level in their position in the tree.

The algorithm used to find the minimum cost of the Huffman tree is quite simple: take the two nodes with the least weight, combine them and insert the new node back into the list of nodes. Repeat until one node is left in the tree. Under C++, the algorithm can be implemented using the STL priority_queue in O(NlogN) time. With C and Pascal, the easiest way to implement it is as follows: sort all the weights in incremental order, keep two lists, the first containing all the uncombined weights and the second containing all the weights combined. Note that as the algorithm processes, the weight of the combined node is always increasing, so we could insert the new node to the end of the 2nd list in constant time. When we want to find the minimum pair of nodes, it suffices to check the 3 combinations of where the two nodes come from (1st, 2nd of one of the lists, 1st of both lists). This algorithm takes O(NlogN) for the sorting phase and O(N) in the combining phase.

Code (C++, by Bruce Merry):

```cpp

#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    priority_queue<ll, vector<ll>, greater<ll> > q;
    ifstream in("plank.in");
    ofstream out("plank.out");
    int N;

    in >> N;
    for (int i = 0; i < N; i++) {
        ll x;
        in >> x;
        q.push(x);
    }

    ll cost = 0;
    for (;;) {
        ll a = q.top();
        q.pop();
        if (q.empty()) break;
        ll b = q.top();
        q.pop();
        cost += a + b;
        q.push(a + b);
    }
    out << cost << "\n";
    return 0;
}

```

# USACO NOV06 Problem 'cowfood' Analysis

by Richard Peng

This problem is a classical state compression DP problem. Since the forbidden component has length 2, only the configuration of the previous row determines whether the current row is valid. There are 2^n, which is worst case 4096 possible configurations per each row (the total is much lower as no two neighboring grids on the same row can both be planted) and its possible to transfer from one row to another if and only if there does not exist a column where both rows have occupied squares. Clever usage of bit operators can help reduce the amount of code.

The runtime of the code is O(2^(2n)*n) although in practice it's much less. In the original version of the problem, the exact result rather than the answer mod 10^8 was required, which would have made the problem a bit more difficult to code.
Code (by Bruce Merry):

```cpp

#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

#define MAXR 12
#define MAXC 12
#define MAX2C (1 << MAXC)
#define MOD 100000000

int main() {
    ifstream in("cowfood.in");
    ofstream out("cowfood.out");
    int infertile[MAXR + 1] = {0};
    int dp[MAXR + 1][MAX2C];
    int R, C, C2;
    vector<int> valid;

    in >> R >> C;
    C2 = 1 << C;
    fill(infertile, infertile + R, 0);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            int x;
            in >> x;
            if (!x) infertile[i + 1] |= 1 << j;
        }

    for (int i = 0; i < C2; i++)
        if (!(i & (i << 1))) valid.push_back(i);

    fill(dp[0], dp[0] + C2, 1);
    for (int i = 1; i <= R; i++) {
        fill(dp[i], dp[i] + C2, 0);
        for (int j = 0; j < C2; j++) {
            if (~j & infertile[i]) continue;
            for (size_t k = 0; k < valid.size(); k++) {
                int u = valid[k];
                if (u & j) continue;
                dp[i][j] += dp[i - 1][u | infertile[i - 1]];
                dp[i][j] %= MOD;
            }
        }
    }

    out << dp[R][infertile[R]] << "\n";
    return 0;
}

```

# USACO NOV06 Problem 'block' Analysis

by Richard Peng

Define d(p,k) to be the length of the kth shortest path to vertex p. Then note that for this algorithm, the only relavent distances we have to consider are d(p,1) and d(p,2).

The sketch for the proof of correctness would be if d(i,3) was used for one of the paths, then the two paths with the path leading up to d(i,3) replaced by the paths leading up to d(i,1) and d(i,2) respectively would have lesser costs, contradicting with the claim the resulting path is one of the two shortest paths.

Notice that the state with the minimum distance to the source cannot have its distance reduced as all paths have positive lengths. Therefore, we could 'expand' this vertex by adding new states of the results of travelling to its neighbors from this vertex. By the above claim, it's not necessary to expand from the same vertex more than twice.

Therefore, we could store all the the distances in a priority queue, as long as there are elements in the queue, take out the minmum, if its vertex has not been 'expanded' twice, expand it and add all the new distances to the priority queue.

Since at most 2V expansions can be done, at most 2E nodes can be in the queue at a time, resulting in a runtime of O(ElogE) where E is the number of edges.

```cpp

#include <algorithm>
#include <queue>
#include <stdio.h>
using namespace std;

int ans[6000][2],t[6000];
int li[100000][3],deg[6000],*e[6000],*c[6000],n,m;

struct dat{
	int p,dis;
	bool operator <(const dat &b) const { return dis > b.dis;}
};

priority_queue<dat> q;
main(){
	FILE *f_in,*f_out;
	int i,j,p,d;
	f_in=fopen("block.in","r");
	f_out=fopen("block.out","w");
	for(fscanf(f_in,"%d%d",&n,&m),memset(deg,0,sizeof(deg)),i=0;i<m;
		fscanf(f_in,"%d%d%d",&li[i][0],&li[i][1],&li[i][2]),
		li[i][0]--,li[i][1]--,deg[li[i][0]]++,deg[li[i][1]]++,i++);
	for(i=0;i<n;e[i]=new(int[deg[i]]),c[i]=new(int[deg[i]]),deg[i]=0,i++);
	for(i=0;i<m;
		e[li[i][0]][deg[li[i][0]]]=li[i][1],
		c[li[i][0]][deg[li[i][0]]]=li[i][2],deg[li[i][0]]++,
		e[li[i][1]][deg[li[i][1]]]=li[i][0],
		c[li[i][1]][deg[li[i][1]]]=li[i][2],deg[li[i][1]]++,i++);

	for(memset(t,0,sizeof(t)),q.push((dat){0,0});!q.empty();q.pop()){
		p=q.top().p;	d=q.top().dis;
		if(t[p]<2){
			ans[p][t[p]]=d;	t[p]++;
			for(i=0;i<deg[p];i++)	if(t[e[p][i]]<2){
				q.push((dat){e[p][i],d+c[p][i]});
			}
		}
	}
	fprintf(f_out,"%d\n",ans[n-1][1]);
	fclose(f_in);
	fclose(f_out);
}

```