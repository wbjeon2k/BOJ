# USACO FEB08 Problem 'grading' Analysis

by Richard Peng
There are greedy approaches to this problem. Although it's fairly intuitive, the proof I'm aware of is rather involved. So here is a O(N^2) DP solution based on the first step in the proof of correctness of the greedy solution.

The only observation we require is there is an optimal solution where the elevations are a subset of the heights of elevations provided. To see this, suppose in the optimal solution, there is an elevation that is not the same as one of the A_is. Then consider the 'plateau' formed by that height, we can move it either up/down depends on how many A_is in that range are above/below it to get a better answer. As we move, we might encounter another plateau (so if we move past it, our answer is no longer monotone). In that case, we just merge those 2 'plateau's and continue our argument. This can happen only finitely many times since the size of our plateau is always increasing.

From this, we could easily construct a DP solution where the state is the current position being considered and the height that was assigned to it. Transitions can be done in O(n) since we're only consider elevations less or equal to the current elevation for the previous position.

Jeff Wang's code is shown below:

```cpp

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

int N, incr[2][2000], A[2000], V[2000], result;

inline int absv(int x) { return (x >= 0) ? x : -x; }

void go() {
    sort(V, V+N);
    int i, j, swi = 0;
    
    for(i=0; i<N; i++) incr[swi][i] = (A[0] <= V[i]) ? 0 : A[0]-V[i];
    
    for(i=1; i<N; i++)
    {
        swi = 1-swi;
        incr[swi][0] = incr[1-swi][0] + absv(A[i]-V[0]);
        
        for(j=1; j<N; j++)
            incr[swi][j] = min(incr[swi][j-1], incr[1-swi][j] + absv(A[i]-V[j]));
    }
    
    for(i=0; i<N; i++)
        result = min(result, incr[swi][i]);
}
int main()
{
    FILE* in = fopen("grading.in", "r");
    FILE* out = fopen("grading.out", "w");
    
    fscanf(in, "%d\n", &N);
    
    result = 1000000000;
    int i;
    
    for(i=0; i<N; i++) { fscanf(in, "%d\n", &A[i]); V[i] = A[i]; }
    go();
        
    for(i=0; i<N; i++) { A[i] *= -1; V[i] *= -1; }
    go();
    
    fprintf(out, "%d\n", result);
}
```