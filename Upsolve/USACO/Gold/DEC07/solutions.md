# USACO DEC07 Problem 'sightsee' Analysis

by Brian Dean

This problem involves a graph in which each edge e has an associated length L(e) and fun value F(e). Our goal is to find a directed cycle C minimizing L(C) / F(C), where L(C) denotes the total length of all edges in C and F(C) denotes the total fun value of all edges in C (note: the actual problem asks us to maximize F(C) / L(C), but I've converted it to a minimization problem since this is more common when we discuss shortest path type problems).

To solve this problem quickly, we employ a common trick: binary search on the answer. Let us make a guess that the answer is X. By running one instance of the Bellman-Ford shortest path algorithm (in O(LP) time), we will be able to tell if this guess is too high or too low, thereby homing in on the correct answer. The one feature of the Bellman-Ford algorithm we use here is the fact that it can detect whether or not a negative-length direct cycle exists in a graph (we won't go into how this is done here, since this is a common algorithm).

How can negative cycle detection tell us if our guess X is too high or too low? Well, we would like to check if the minimum value of L(C)/F(C) over all cycles C is less than X (i.e., if there exists a cycle C such that L(C)/F(C) <= X). If so, then our guess is too high; otherwise it is too low. But asking whether there exists a cycle C such that L(C)/F(C) <= X is the same as asking whether there exists a cycle C such that L(C) <= X F(C), which is the same as asking whether there exists a cycle C such that L(C) - X F(C) <= 0. So if we define the cost of each edge e as Z(e) = L(e) - X F(e), then this turns into a negative cycle detection problem with respect to the Z(e)'s!

Below is Chinese Junior Danqi Chen's full-credit beautifully formatted PASCAL solution (this is precisely as she submitted it) which might or might not match the description above.

```cpp

  program sightsee;

    const
      finp  =  'sightsee.in';
      fout  =  'sightsee.out';
      maxn  =  1000 + 5;
      eps   =  1e-4;

    type
       nodeptr  =  ^node;
          node   =  record
             p, len  :   longint;
             next    :   nodeptr;
          end;

    var
       hash        :   array [1 .. maxn] of boolean;
       queue, edge :   array [1 .. maxn] of longint;
       dist        :   array [1 .. maxn] of extended;
       a           :   array [1 .. maxn] of nodeptr;
       cost        :   array [1 .. maxn] of longint;
       n, m        :   longint;    

    procedure create(x, y, c  :  longint);
      var
         tmp      :   nodeptr;
      begin
         new(tmp); tmp ^.p := y; tmp ^. len := c;
         tmp ^.next := a[x]; a[x] := tmp;
      end;

    procedure init;
      var
         i        :   longint;
         x, y, c  :   longint;
      begin
         read(n, m);
         for i := 1 to n do read(cost[i]);
         for i := 1 to n do a[i] := nil;
         for i := 1 to m do 
           begin
             read(x, y, c);
             create(x, y, c);
           end;
      end;
 
    function nxt(i  :  longint):  longint;
      begin
         if i = maxn then nxt := 1 else nxt := i + 1;
      end;

    function check(limit  :  extended):  boolean;
      var
         h, t, i :   longint;
         tmp     :   nodeptr;
         v       :   extended;
      begin
         check := true;
         fillchar(hash, sizeof(hash), false);
         h := 0; t := 0;
         for i := 1 to n do 
           begin
             inc(t); queue[t] := i; hash[i] := true;
             dist[i] := 0; edge[i] := 0;
           end;
         while (h <> t) do
           begin
             h := nxt(h);
             tmp := a[queue[h]];
             while (tmp <> nil) do
               begin
                 v := tmp ^. len * limit - cost[tmp^.p];
                 if (dist[queue[h]] + v < dist[tmp^.p]) then
                   begin
                     dist[tmp^.p] := dist[queue[h]] + v;
                     edge[tmp^.p] := edge[queue[h]] + 1;
                     if edge[tmp ^. p] > n then exit; 
                     if not hash[tmp^.p] then
                       begin
                         t := nxt(t);
                         queue[t] := tmp^. p;
                         hash[tmp ^.p] := true;
                       end;
                   end;
                 tmp := tmp ^. next;
               end;
              hash[queue[h]] := false;
           end;
         check := false;
      end;

    procedure work;
      var
         l, r, mid  :  extended;
      begin
         l := 0; r := 1000;
         while (r - l > eps) do
           begin
             mid := (l + r) / 2;
             if check(mid) then l := mid else r := mid;
           end;
         writeln(l : 0 : 2);
      end;

    begin
       assign(input, finp); reset(input);
       assign(output, fout); rewrite(output);
         init;
         work;
       close(input); close(output);
    end.

```


# USACO DEC07 Problem 'gourmet' Analysis

by Richard Peng
The greedy solution works for this task. The first observation is if we sort the requests and grasses by decreasing order of green-ness, the set of grass we need to consider for each request is precisely the set of all grass that hasn't been used yet that has a higher greenness. So we can add grasses to the set as we 'sweep' by them and remove the grasses as we use them.

Let's just consider the prices. The claim is that at each moment, we can pick the cheapest grass that will satisfy the cow. This is true since suppose we pick a more expensive grass and use the cheaper one later, we can swap the choices while keeping both cows satisfied without increasing the total cost.

Now the problem becomes a data structure problem, we need to support the following operations: insertion, deletion, find the first element with key bigger than a given value and we want to do each operation in O(logn) time.

This can be done using STL set. It's also possible to do this without STL using a binary index tree by first assigning values from 1 to n to the prices, then construct a full binary tree with the prices at leafs and track on each node whether the subtree below has values. Both give O(nlogn) solutions.

Below is an extraordinarily compact full-credit solution submitted by Belarus's Gennady Korotkevich:

```cpp
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

#define __int64 long long

using namespace std;

vector < pair <int,int> > c,f;
set < pair <int,int> > a;

int main () {
    FILE *in  = fopen ("gourmet.in","r");
    FILE *out = fopen ("gourmet.out","w");
    int n, m, i, q, w;
    fscanf (in, "%d%d", &n, &m);
    for (i=0; i<n; i++) {
       fscanf (in, "%d%d", &q, &w);
       c.push_back (make_pair (w, q));
    }
    for (i=0; i<m; i++) {
        fscanf (in, "%d%d", &q, &w);
        f.push_back (make_pair (w, q));
    }
    sort (c.begin (), c.end ());
    sort (f.begin (), f.end ());
    int r = m - 1;

    __int64 ans = 0;
    a.clear ();
    for  (i=n-1;i>=0;i--) {
        while (1) {
            if (r < 0) break;
            if (f[r].first >= c[i].first) {
                a.insert (make_pair (f[r].second, r));
                r--;
            }
            else break;
        }
        set< pair <int,int> >::iterator d =
                          a.lower_bound (make_pair (c[i].second, -1));
        if  (d == a.end ()) {
            fprintf (out, "-1\n");
            return 0;
        }
        ans +=  (*d).first;
        a.erase (d);
    }
    fprintf (out, "%Ld\n", ans);
    return 0;
}
```

# USACO DEC07 Problem 'bclgold' Analysis

by Christos Tzamos
This problem can be solved with dynamic programming on the intervals of cows but there is also a simple greedy strategy.

Between the two cows in the edges, you must always pick the cow with the smallest initial letter. If both cows have the same initial letter in order to decide you must look a little bit deeper and check the second cows in the line's edges or the third ones if those are equal and so on until you find two cows that are different. Then you pick the cow from the side of the smallest one.

This process can be summarized as follows.

At any given interval [a,b] with string S([a,b]) you choose:

Cow a if S([a,b]) < rev( S([a,b]) )
Cow b otherwise
where rev(S) is the reverse string e.g. rev("abc") = "cba"

This can be implemented in O(N^2) but we can achieve O(NlogN) by using suffix arrays.

Here are the two implementations:

```cpp

The O(N^2)
/*
TASK: bcl
LANG: C++
USER: christos
*/
#include<cstdio>

char S[2010],ln=0;

void prnt(char a) {
	if(ln==80) {printf("\n");ln=0;}
	printf("%c",a);ln++;
}

int main() {
	int i,j,N,pi,pj,val;
	freopen("bcl.in" ,"r",stdin );
	freopen("bcl.out","w",stdout);
	scanf("%d",&N);
	for(i=0;i<N;i++) scanf(" %c ",S+i);
	i=0,j=N-1;
	while(i<=j) {
		if(S[i]<S[j])		{prnt(S[i]);i++;}
		else if(S[i]>S[j])	{prnt(S[j]);j--;}
		else {
			pi=i+1;pj=j-1;val=S[i];
			while( pj-pi>1 && S[pi]==S[pj]) {pi++,pj--;}
			if(S[pi]<S[pj]) prnt(S[i]),i++;
			else prnt(S[j]),j--;
		}
	}
	printf("\n");
	return 0;
}

And the O(NlogN)
/*
TASK: bcl
LANG: C++
USER: christos
*/
#include<cstdio>
#include<cstring>
#include<cstdlib>

#define MAXN 500050

char S[2*MAXN];
int N,ln=0;
int o[2][2*MAXN], t[2*MAXN][2];
int A[2*MAXN], B[2*MAXN], C[2*MAXN], D[2*MAXN];

void prnt(char a) {
	if(ln==80) {printf("\n");ln=0;}
	printf("%c",a);ln++;
}

int main() {
	
	int i, j, jj, x, k;
	
	freopen("bcl.in" ,"r",stdin );
	freopen("bcl.out","w",stdout);
	scanf("%d",&N);
	for(i=0;i<N;i++) {
		scanf(" %c ",S+i);
		S[N+i] = S[i];
	}

	memset(A, 0, sizeof(A));
	for (i = 0; i < 2*N; ++i) A[(int)(S[i]-'A')] = 1;
	for (i = 1; i < 26; ++i) A[i] += A[i-1];
	for (i = 0; i < 2*N; ++i) o[0][i] = A[(int)(S[i]-'A')];
	x=0;
	for (j = 0, jj = 1, k = 0; jj < N && k < 2*N; ++j, jj <<= 1) {

		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));

		for (i = 0; i < N; ++i) {
			++A[ t[i][0] = o[x][i] ];
			++B[ t[i][1] = (i+jj<N) ? o[x][i+jj] : 0 ];
		}
		
		for (i = N; i < 2*N; ++i) {
			++A[ t[i][0] = o[x][i] ];
			++B[ t[i][1] = (i-jj>=N) ? o[x][i-jj] : 0 ];
		}

		for (i = 1; i <= 2*N; ++i) {
			A[i] += A[i-1];
			B[i] += B[i-1];
		}

		for (i = 2*N-1; i >= 0; --i)
			C[--B[t[i][1]]] = i;

		for (i = 2*N-1; i >= 0; --i)
			D[--A[t[C[i]][0]]] = C[i];

		x ^= 1;
		o[x][D[0]] = k = 1;
		for (i = 1; i < 2*N; ++i)
			o[x][D[i]] = (k += (t[D[i]][0] != t[D[i-1]][0] || t[D[i]][1] != t[D[i-1]][1]));

	}
	i=0,j=N-1;
	while(i<=j) {
		if(S[i]<S[j])		{prnt(S[i]);i++;}
		else if(S[i]>S[j])	{prnt(S[j]);j--;}
		else if(o[x][i]<o[x][N+j]) {prnt(S[i]);i++;}
		else {prnt(S[j]);j--;}
	}
	printf("\n");
	return 0;
}

```