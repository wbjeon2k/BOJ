# BOJ6208

Say that we've built some the first few sections of our roller coaster, and say that these first few sections have a total length of 10 (stretching from position 0 to position 10). Suppose that they cost us $15 and gave us a fun of 20. If there was a different way to build up to position 10 which cost $15 and which gives a fun of 19, would we want to use it, ever? No, because we could just substitute the more fun components with a fun of 20 for the less fun ones, and then we could finish the roller coaster exactly the same as we were going to.

The key point here is that if we've built up to position 10, it doesn't matter how we got there: the only things that matter are how much money we spent and how fun it was. This allows us to use the technique of Dynamic Programming.

We make a table "FUN" of size L+1 by B+1 (where L is the total length of the roller coaster and B is the total budget). The entry at FUN[i][j] will be the maximum amount to fun we can have gotten so far after having built up to position i and spent j dollars. We start by initializing the table to minus infinity and then FUN[0][0] to 0. This indicates that we don't know yet how to have any fun, except that we know that we can have no fun and get no where by building nothing.

We now walk through the table FUN[i][j] from the left (at position i=0) to the right (at position i=L). For each position i, we loop through all of the different roller coaster components k that can be built starting at position i. The width of component k is Wk and the cost is Ck and the fun Fk. For each amount of money j that we could have already spent, if we can build component k within our budget (i.e. if j+Ck <= B), then we see if doing so yields a more fun partial coaster at position i+Wk and cost j+Ck then we already have in the table at FUN[i+Wk][j+Ck]. That is, we check to see if FUN[i][j] + Fk > FUN[i+Wk][j+Ck]. If it is, then we update FUN[i+Wk][j+Ck] with the higher value. Since we only ever update a value to the right of where we are now, and since we walk through the table from left to right, we will have the best (correct) value by the time we walk to a table entry.

After we're done with this, we just need to read off the most fun coaster from among the entries at FUN[L][j] for all costs j with 0 <= j <= B. If these values are all minus infinity, then we know that we can't actually get from the start by building components, and thus we can't actually build the coaster, and we output -1.

```cpp
#include <stdlib.h>
#include <stdio.h>

const int MAXL = 1001 + 100;
const int MAXN = 20000 + 200;
const int MAXB = 1001 + 100;

int len, n, budget;

struct component {
  int start;
  int width;
  int fun;
  int cost;
} coaster[MAXN];

int comp_cmp(const void *p1, const void *p2){
  return((((component*)p1)->start) - (((component*)p2)->start));
}

int best[MAXL][MAXB];

int main(){

  FILE *fin = fopen("coaster.in", "r");
  fscanf(fin, "%d %d %d", &len, &n, &budget);
  for(int i = 0; i < n; ++i){
    fscanf(fin, "%d %d %d %d", &coaster[i].start, &coaster[i].width,
                     &coaster[i].fun, &coaster[i].cost);
  }
  fclose(fin);

  //fprintf(stderr, "line %d\n", __LINE__);

  for(int i = 0; i <= len; ++i){
    for(int j = 0; j <= budget; ++j){
      best[i][j] = -1;
    }
  }
  for(int i = 0; i <= budget; ++i){
    best[0][i] = 0;
  }

  qsort(coaster, n, sizeof(component), comp_cmp);

  for(int i = 0; i < n; ++i){
    for(int c = 0; c <= budget-1; ++c){
      if(best[coaster[i].start][c] == -1) continue;
      best[coaster[i].start + coaster[i].width][c + coaster[i].cost] >?= best[coaster[i].start][c] + coaster[i].fun;
    }
  }

  FILE *fout = fopen("coaster.out", "w");
  fprintf(fout, "%d\n", best[len][budget]);
  fclose(fout);

  return(0);
}

```

# BOJ6209

USACO DEC06 Problem 'jump' Analysis
by Alex Schwendner
Suppose that we ask a different question. Say that we need the shortest distance between any two rocks to be at least W, and we want to know how many rocks we have to remove. If the answer to this is R(W), and R(W) <= M (where M is the number of rocks that we're allowed to remove in the original problem) then we know that the answer to the original problem is at least W, since we've just demonstrate a solution.

So we require that the distance between any two consecutive rocks is at least W. We walk through the rocks left to right, greedily counting how many rocks we will have to remove. For each rock, if its distance from the last rock that we've kept is at least W, then we keep this rock. If not, then we remove this rock.

We claim that this will give us the best solution. Say that we have the best solution for the first K rocks and are considering adding the K+1-st rock. If we can just add the K+1-st rock, we do. If it's too close to the previous rock, then a solution including the K+1-st rock could not include the previous rock. But, since we already had the best solution for all of the rocks before that one, we couldn't have any more rocks earlier in the river. Thus, we just add a rock and subtract a rock, and don't do any better.

Now, since we can figure out, for each W, if our answer is at least W, we can do binary search to find the answer. We start with A=0 and B=L. A will always be less or equal to the answer, and B will always be greater than or equal to the answer. While A and B are different, we pick a number C halfway between A and B. If we can do W=C, we know that the answer is at least C, so we set A=C. Otherwise, we set B=C-1. When we get A=B, we're done, and we know that that's our answer.

```cpp

#include <stdlib.h>
#include <stdio.h>

const int MAXROCKS = 200000;

int len, rocks, r;

int rock[MAXROCKS];

int intcmp(const void *p1, const void *p2){
  return(*(int*)p1 - *(int*)p2);
}

int main(){

  FILE* fin = fopen("jump.in", "r");
  fscanf(fin, "%d %d %d", &len, &rocks, &r);
  for(int i = 0; i < rocks; ++i){
    fscanf(fin, "%d", &rock[i]);
  }
  fclose(fin);

  qsort(rock, rocks, sizeof(int), intcmp);

  int a = 0;
  int b = len;

  while(a < b){
    int c = (a + b + 1) / 2;

    int p = 0;
    int hits = 0;
    for(int i = 0; i < rocks; ++i){
      if(rock[i] - p < c){
	++hits;
      } else {
	p = rock[i];
      }
    }

    if(hits > r){
      b = c-1;
    } else {
      a = c;
    }
  }

  FILE *fout = fopen("jump.out", "w");
  fprintf(fout, "%d\n", a);
  fclose(fout);


  return(0);
}

```