# USACO NOV06 Problem 'badhair' Analysis

by Richard Peng

Define N[i] to be the first cow to the right of cow i which is taller than cow i. It's quite obvious that calculating N[i] for all i is equivalent to solving the problem.

An easy observation is that if h[i]>h[j], n[i]>j, then n[i]>=n[j] since if n[i]h[i]>h[j], contradicting with the definition of n[j]. Therefore, we could start n[i] as i+1 and while h[n[i]] < h[i], replace n[i] by n[n[i]].

The proof that this algorithm runs in O(N) time is non-trivial. First note that we could not have i < j < n[i] < n[j] since that would imply h[j] > h[n[i]] > i. Therefore, once we have calculated n[i], all the n values between i and n[i] will never be accessed again by j < i. This is equivalent to shortening the array each time by n[i]-i, so an easy amortized analysis could show the total amount of work done is O(N)

(There also is a different solution using stacks, but this solution appears to be much more straightforward)

Code (by Brian Dean):

```cpp
#include <stdio.h>

#define MAX_N 100000
int N, h[MAX_N], n[MAX_N];

unsigned int solve(void) {
  unsigned int T = 0;
  int i, c;

  for (i=N-1; i>=0; i--) {
    c = 0; n[i] = i+1;
    while (n[i] < N && h[n[i]] < h[i]) {
      c += n[n[i]] - n[i];
      n[i] = n[n[i]];
    }
    T += c;
  }
  return T;
}

int main(void) {
  FILE *fp;
  int i;

  fp = fopen ("badhair.in", "r");
  fscanf (fp, "%d", &N);
  for (i=0; i<N; i++) fscanf (fp, "%d", &h[i]);
  fclose (fp);
  
  fp = fopen ("badhair.out", "w");
  fprintf (fp, "%u\n", solve());
  fclose (fp);

  return 0;
}
```

# USACO NOV06 Problem 'rndnum' Analysis
by rho

First note that you only need to count the number of round numbers not exceeding Start-1 and subtract that from the number of round numbers not exceeding Finish. So we are only concerned with counting the number of round numbers not exceeding some number X. Since X can be up to a two billion, we cannot count round numbers one by one.

Consider X in binary. Let N be the number of digits in X.

Let A(x,y) be the number of binary strings with x '0's and y '1's that begin with 0. Let B(x,y) be the number of binary strings with x '0's and y '1's that begin with 1. Let C(x,y) be the number of binary strings with x '0's and y '1's that begin with 0 where each string represents a number not exceeding the number represented by the last x+y digits of X. Let D(x,y) be the number of binary strings with x '0's and y '1's that begin with 1 where each string represents a number not exceeding the number represented by the last x+y digits of X.

We update A, B, C, D using dynamic programming bottom up for each x+y=k, incrementing k until k = N.

The desired result is the sum of all D(x,y) where x+y = N and x>=y, plus the sum of all B(x,y) with x+y=y.

Do this procedure for both Finish and Start-1 and subtract to get answer.

Here is Bruce Merry's solution (which might differ from above explanation):

```cpp

#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

static int choose[64][64];

static int rndnum(int b, int z, unsigned int top) {
    int ans = 0;

    if (z > b || top == 0) return 0;
    if (top >= (1U << b)) {
        for (int j = max(z, 0); j <= b; j++)
            ans += choose[b][j];
        return ans;
    }

    ans += rndnum(b - 1, z - 1, top);
    unsigned int h = 1U << (b - 1);
    if (top > h && b > z)
        ans += rndnum(b - 1, z, top - h);
    return ans;
}

static int rndnumrange(int b, int z, unsigned int start, unsigned int end) {
    if (start >= end) return 0;
    return rndnum(b, z, end) - rndnum(b, z, start);
}

int main() {
    for (int i = 0; i < 64; i++) {
        choose[i][0] = choose[i][i] = 1;
        for (int j = 1; j < i; j++)
            choose[i][j] = choose[i - 1][j - 1] + choose[i - 1][j];
    }

    ifstream in("rndnum.in");
    ofstream out("rndnum.out");
    unsigned int f, l;
    int ans = 0;
    in >> f >> l;
    for (int i = 1; i <= 31; i++) {
        unsigned int f1 = max(f, 1U << (i - 1));
        ans += rndnumrange(i, (i + 1) / 2, f1, l + 1);
    }
    out << ans << "\n";
    return 0;
}

```