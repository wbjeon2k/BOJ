# USACO MAR07 Problem 'lineup' Analysis

by Richard Peng
Consider the partial sum sequence of each of the k features built by taking the sum of all the values up to position i. The problem is equivalent to:
Given an array s[n][k], find i,j, with the biggest separation for which s[i][l]-s[j][l] is constant for all l.
The problem is now to do this efficiently. Notice that s[i][l]-s[j][l] being constant for all l is equivalent to s[i][l]-s[j][l]=s[i][1]-s[j][1] for all l, which can be rearranged to become s[i][l]-s[i][1]=s[j][l]-s[j][1] for all l. Therefore, we can construct another array a[n][k] where a[i][j]=s[i][j]-s[i][1] and the goal is to find i and j with the biggest separation for which a[i][l]=a[j][l] for all l.

This can be done by sorting all the a[i] entries, which takes O(nklogn) time (although in practice rarely will all k elements be compared). Another alternative is to go by hashing, giving an O(nk) solution. Both solutions are fairly straightforward once the final array is constructed.

Here is a hashing solution (by Richard Peng):

```cpp

#include <stdio.h>
#include <string.h>

int h[1000000],hsize,lis[100001][30],n,k;

int findid(int v[30]){
	int i,p,can,i1;
	for(p=0,i=0;i<k;i++)
		p=((p<<2)+(v[i]>>4))^(v[i]<<10);
	p=p%hsize;
	if(p<0)	p+=hsize;
	for(can=0;(!can)&&(h[p]!=-1);p++)
		for(i1=h[p],can=1,i=0;(can)&&(i<k);i++)
			can=(v[i]==lis[i1][i]);
	if(can)	p--;
	return p;
}

main(){
	int i,i1,j,ans,p,same,tem,shif,a;
	freopen("lineup.in","r",stdin);
	freopen("lineup.out","w",stdout);
	hsize=997001;
	for(i=0;i<1000000;i++)	h[i]=-1;
	for(scanf("%d%d",&n,&k),k--,i=0;i<k;lis[0][i]=0,i++);
	h[findid(lis[0])]=0;
	for(ans=0,i=1,i1=0;i<=n;i++,i1++){
		scanf("%d",&a);
		for(shif=a%2,a=(a>>1),j=0;j<k;j++,a=(a>>1))
			lis[i][j]=lis[i1][j]+(a%2)-shif;
		p=findid(lis[i]);
		if(h[p]==-1)	h[p]=i;
		if((tem=i-h[p])>ans)	ans=tem;
	}
	printf("%d\n",ans);
	return 0;
}

```

# USACO MAR07 Problem 'ranking' Analysis

by Richard Peng
To simplify notation, we use X->Y to denote the existence of a path of queries leading from a to b, from which we could deduce cow X is ranked higher than cow Y.

An obvious upper bound for the number of queries to ask is the number of pairs of cows for which we have neither of X->Y and Y->X. It's slightly less obvious that this is also the lower bound.

Suppose there exist a set of queries in which the relationship between X and Y is not queried and from the original data we could not deduce X->Y or Y->X. Then we could answer the queries in a way so X and Y's ranking end up being adjacent to each other (by making all other cows rank either lower or higher than both of X and Y). In such a case, it's clear a comparison between X and Y is necessary as otherwise, we could switch the position of X and Y without altering the results of the queries.

The code for this problem is straight forward DFS to check which cows can be 'reached' by a set of information already given for each cow. Each round of DFS runs in O(M) time, giving a runtime of O(MN)

Here is Brian Dean's code:

```cpp

#include <stdio.h>
#define MAX_N 1000
#define MAX_M 10000

typedef struct
{
  int dest;
  int next_edge;
} Edge;

char TC[MAX_N][MAX_N];
char beenthere[MAX_N];
int N, M, first_edge[MAX_N];
Edge edges[MAX_M];

void DFS(int s, int i)
{
  int e;
  TC[s][i] = 1;
  beenthere[i] = 1;
  e = first_edge[i];
  while (e != -1) {
    if (!beenthere[edges[e].dest])
      DFS(s, edges[e].dest);
    e = edges[e].next_edge;
  }
}

int main(void)
{
  int i, j, k, m;
  FILE *fp;

  fp = fopen ("ranking.in", "r");
  fscanf (fp, "%d %d", &N, &M);
  for (i=0; i<N; i++) first_edge[i] = -1;
  m = 0;
  for (k=0; k<M; k++) {
    fscanf (fp, "%d %d", &i, &j);
    TC[i-1][j-1] = 1;
    edges[m].dest = j-1;
    edges[m].next_edge = first_edge[i-1];
    first_edge[i-1] = m++;
  }
  fclose (fp);

  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) beenthere[j] = 0;
    DFS(i, i);
  }

  k = 0;
  for (i=0; i<N; i++)
    for (j=i+1; j<N; j++) 
      if (TC[i][j]==0 && TC[j][i]==0) k++;

  fp = fopen ("ranking.out", "w");
  fprintf (fp, "%d\n", k);
  fclose (fp);
  return 0;
}

```

# USACO MAR07 Problem 'cowturn' Analysis

by Richard Peng
We reduce the problem to finding whether we could reverse all cows given a preset turn length of k.

We consider turns by the the position of the leftmost cow they affect. The 1st cow can only be turned by the first turn, so the first turn is uniquely determined. The 2nd cow can only be turned by the 1st and 2nd turn, but the 1st turn is already uniquely determined, so the 2nd turn is also fixed. If we proceed 'up' the sequence this way, we could see all the turns are uniquely determined by the configurations of the cows and the turns before them.

We now need to track how many times a cow is turned by the flips before it. This is equivalent to a XOR sum of all the turn bits within k of it. This can be tracked using the standard method of keeping a pointer of whether the sequence start and moving that pointer accordingly as the location of the 'current' cow moves.

This runs in O(n) time per iteration, which gives a O(n^2) algorithm in the worst case.

Code by Brian Dean:

```cpp

#include <stdio.h>
#define MAX_N 5000

int Boundary[MAX_N+1], Parity[MAX_N+1], N;

int check(int k)
{
  int i, count=0;
  for (i=0; i<N; i++) Parity[i] = Boundary[i];
  for (i=0; i<=N-k; i++) {
    count += Parity[i];
    Parity[i+k] ^= Parity[i];
  }
  while (i<N) if (Parity[i++]) return MAX_N+1;
  return count;
}
  
int main(void)
{
  FILE *fp = fopen("cowturn.in", "r");
  int i, v, minmoves = MAX_N+1, best_k;
  char c, dir='F';

  fscanf (fp, "%d", &N);
  for (i=0; i<N; i++) {
    fscanf (fp, " %c", &c);
    if (c!=dir) { dir=c; Boundary[i] = 1; }
  }
  if (dir=='B') Boundary[N] = 1;
  fclose (fp);

  for (i=1; i<=N; i++) {
    v = check(i);
    if (v < minmoves) { best_k = i; minmoves = v; }
  }
  
  fp = fopen ("cowturn.out", "w");
  fprintf (fp, "%d %d\n", best_k, minmoves);
  fclose (fp);
  return 0;
}

```