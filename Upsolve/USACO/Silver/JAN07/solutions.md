
# USACO JAN07 Problem 'flowers' Analysis

by Bruce Merry
Firstly, the fact that FJ takes 2*T_i to take a cow home and return rather than T_i isn't really relevant - just double all the T_i values up front, and we can talk about it taking T_i time to return each cow.

Intuitively, it is beneficial to remove the most destructive cows first, and on the other hand it is also good to remove cows with low T_i so that FJ can quickly return to remove more cows. Let's try to formalise this by considering two cows A and B that are currently adjacent in an ordering, and see what happens if we exchange them. You should immediately realise that this has no effect on the destruction wrought by the other N-2 cows, since they are each in the garden for exactly the same time as before. Moving cow B ahead means that is in the garden for T[A] less, so its destruction is reduced by T[A]D[B]. Conversely, delaying picking up cow A increases its time in the garden and its destruction by T[B]D[A]. Thus, it is beneficial to swap the cows exactly when T[A]D[B] > T[B]D[A] or equivalently when T[A]/D[A] > T[B]/D[B]. This corresponds with our intuition - if B is either very destructive or very quick to take home, it should be moved ahead in the order.

We now have a sort key on which we can sort the cows. To see that simply sorting on T[A]/D[A] is optimal, consider any ordering which isn't sorted. There must be two adjacent cows with their keys out of order, and so by the argument above, they can beneficially be swapped and so this cannot be an optimal order.

```cpp

/*
ID: christos
LANG: C
TASK: flowers
*/

#include<cstdio>
#include<cstdlib>

#define MAXN 100000

int N;
struct cow {int ti, di; }cows[MAXN];

int f(const void * a,const void * b)
{
	cow x = *(cow*)a;
	cow y = *(cow*)b;
	return x.ti * y.di - x.di * y.ti;
}

int main()
{
	int i, j, l, k, s;
	FILE * fin = fopen("flowers.in", "r");
	fscanf(fin, "%d", &N);
	s=0;
	for(i = 0; i < N; ++i){
		fscanf(fin, "%d %d", &k, &l);
		cows[i].ti = k;
		cows[i].di = l;
		s += l;
	}
	fclose(fin);
	qsort(cows, N, sizeof(cow), f);
	long long ans = 0;
	for(i = 0; i < N; i++)
	{
		s -= cows[i].di;
		ans += 2 * s * cows[i].ti;
	}
	FILE * fout = fopen("flowers.out", "w");
	fprintf(fout, "%lld\n", ans);
	fclose(fout);
	return 0;
}

```

# USACO JAN07 Problem 'tallest' Analysis

by Bruce Merry
The most important point to notice is that the "see" relationships can be disjoint or one can lie inside another, but they cannot cross over. For example, "10 sees 20" and "15 sees 9" cannot both be true.

Consider all the "see" end-points (either end) which are not contained inside another "see". It is not hard to show that these cows can only see other cows from this set. Thus, all of these cows can be raised to maximum height (H) without causing any contradictions. Now consider an outer-most "see". The cows inside its range have height at most H-1, but more importantly, all the constraints on this range are internal to the range, so we can solve this range recursively using the same algorithm as for the entire range (there is a special case where some cow sees the end-point cow of the outer range, but it is easy enough to handle). A more direct implementation is to sweep over the cows, maintaining a stack of "sees" that one is current inside. The maximum height is simply H minus the number of active "sees". Interestingly, the implementation never examines the direction of the "see" relationships, nor the index of the tallest cow.

With some careful implementation, this solution can be done in O(N + R) time - but since a cow can see at most one other cow in each direction, R = O(N) and so the solution is O(N).

```cpp

/*
ID: christos
LANG: C++
TASK: tallest
*/

#include<cstdio>

#define MAXN 500000
#define MAXR 2*MAXN

int N, I, H, R;
int bucket[MAXN], order[MAXR], pairs[MAXR][2];
int interval[MAXN];

void radix_sort()
{
	int r, i;
	for(r = 0; r < 2; ++r)
	{
		for(i = 0; i < N; ++i) bucket[i] = 0;
		for(i = 0; i < R; ++i) ++bucket[ pairs[i][r] ];
		for(i = 1; i < N; ++i) bucket[i] += bucket[i-1];
		for(i = N; i > 0; --i) bucket[i] = bucket[i-1];
		bucket[0] = 0;
		for(i = 0; i < R; ++i) order[ bucket[ pairs[i][r] ]++ ] = i;
	}
}

void trim_same()
{
	int r, i;
	radix_sort();
	r = 1;
	for(i = 1; i < R; ++i)
	{
		if(pairs[order[i]][0] == pairs[order[i-1]][0] &&
		   pairs[order[i]][1] == pairs[order[i-1]][1])
			continue;
		order[ r++ ] = order[ i ];
	}
	R = r;
}

int main()
{
	int i, a, b;
	FILE * fin = fopen("tallest.in","r");
	fscanf(fin, "%d %d %d %d", &N, &I, &H, &R);
	for(i = 0; i < R; ++i)
	{
		fscanf(fin, "%d %d", &a, &b);
		--a;
		--b;
		if(a<b) {
			pairs[i][0] = a;
			pairs[i][1] = b;
		} else {
			pairs[i][0] = b;
			pairs[i][1] = a;
		}
		order[i] = i;
	}
	fclose(fin);
	trim_same();            //Each interval should be examined once
	for(i = 0; i < R; ++i)
	{
		a = pairs[ order[i] ][ 0 ];
		b = pairs[ order[i] ][ 1 ];
		--interval[a+1];
		++interval[ b ];
	}
	FILE * fout = fopen("tallest.out","w");
	a = 0;
	for(i = 0; i < N; i++)
	{
		a += interval[ i ];
		fprintf(fout, "%d\n", H + a);
	}
	fclose(fout);
	return 0;
}

```

# USACO JAN07 Problem 'lineup' Analysis

by Richard Peng
This problem is an instance of the classical RMQ (range minimum/maximum query) problem. It suffices to consider the minimum case of this problem as the maximum case can be done similarly. There are mnay ways to approach this problem, they are:

Iterate through all the elements in the range and determine the minimum. This and other variant (sort all elements, start from each end until elements in the range is encounted) runs in worst case O(NQ) time and is not expected to get full marks.
Use a segment tree, which can be implemented as a heap. For each query, combine logN segments to find the minimum of the entire segment. This runs in O(nlogn) time and is expected to get full points
Calculate the minimum/maximum for all segments with lengths being powers of two. Once the minimum of all segments of length l has been calculated. Let this value be M(a,l). Then M(a,2l)=min(M(a,l),M(a+l,l)). It's easy to see this runs in O(N) time for each length l. And since l doubles each time, at most logN iteratioins can be done, which bring the total preprocessing time to O(nlogn) with O(nlogn) space usage.
Now to find minimum of a segment, say [a,b], we first find the largest power of two which is less than the length of the segment, let it be l. Then the answer is min(M(a,l),M(b-l+1,l)). This is because the two intervals [a,a+l-1], [b-l+1,b] is guaranteed to cover the entire segment since if we have a+l-1 Overall, this runs in O(NlogN+Q) time, and is expected to get full points.
code:

```cpp

/*
ID: peng_ri1
LANG: C
TASK: lineup
*/

#include <stdio.h>

int minv[17][50000],maxv[17][50000],n;
FILE *f_in,*f_out;

int mi(int a,int b){return a<b?a:b;}
int ma(int a,int b){return a>b?a:b;}

main(){
	int i,j,siz,s1,a,b,q;
	f_in=fopen("lineup.in","r");
	f_out=fopen("lineup.out","w");
	for(fscanf(f_in,"%d%d",&n,&q),i=0;i<n;fscanf(f_in,"%d",&a),minv[0][i]=a,maxv[0][i]=a,i++);
	for(siz=2,s1=1,i=1;(siz<=n);siz*=2,s1*=2,i++)
		for(j=0;j<n;minv[i][j]=mi(minv[i-1][j],minv[i-1][j+s1]),
			maxv[i][j]=ma(maxv[i-1][j],maxv[i-1][j+s1]),j++);
	for(i=0;i<q;i++){	
		fscanf(f_in,"%d%d",&a,&b);
		a--;
		siz=b-a;
		for(j=0,s1=1;siz>1;s1=s1<<1,j++,siz=siz>>1);
		fprintf(f_out,"%d\n",ma(maxv[j][a],maxv[j][b-s1])-mi(minv[j][a],minv[j][b-s1]));
	}
	fclose(f_in);
	fclose(f_out);
}

```