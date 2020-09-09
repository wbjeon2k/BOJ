# USACO FEB07 Problem 'lexicon' Analysis

by Richard Ho
This is a dynamic programming task.

For each prefix of the given string, we want to know the minimum number of letters to remove to get a sequence of provided words. Let best[k] be this minimum number for the prefix of length k.

We can update "best" bottom-up starting with best[i]=i for all 0 <= i <= L. We consider each prefix from length 0 to length L. For each prefix, we want to consider which words we can place immediately following the prefix. To place a word, we go along the string starting right after the prefix and match letter for letter until we use up all the letters in the word. For each word that has a match in the string, number of letters we need to drop to use that word is determined by how far along the string we scanned to match the word. So we can update the prefix of that length if it is more optimal. Also, we can skip (remove) the letter following the current prefix if that more optimal.

For each of the L prefixes, we will need to go through some of the W words and scan up to L letters to see where the word matches, giving us something around O(W*L*L). The bounds in the input are small enough that this approach runs in time.

Optional: We can make the scanning much faster if we store at each location where the next appearance of each letter is. That way each scan only takes O(length of word) for a combined O(W*L*25). The following solution does not exploit this optimization.

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("lexicon.in", "r"), *out = fopen("lexicon.out", "w");
char data[2000];
char words[2000][100];
int w,n;
int best[2001];

void tryword(int pos, int wnum)
 {
	int i,p=pos,t=0;
	for (i=0;i<strlen(words[wnum]);i++)
	{
		while (data[p]!=words[wnum][i])
		{
			p++;t++;
			if (p>=n) return;
		} p++;
	}
	if (best[pos]+t<best[p]) best[p]=best[pos]+t;
}

int main(void)
 {
	int i,j;
	fscanf(in,"%i %i",&w,&n);
	i=0; char c;
	for (i=0;i<n;i++)
	{
		fscanf(in,"%c",&c);
		while (!isalpha(c)) fscanf(in,"%c",&c);
		data[i]=c;
	} data[i]='\0';
	fscanf(in,"%c",&c);
	for (i=0;i<w;i++) fscanf(in,"%s",&words[i][0]);
	for (i=0;i<=n;i++) best[i]=i;
	for (i=0;i<n;i++)
	{
		for (j=0;j<w;j++)
			if (i+strlen(words[j])<=n)
				if (data[i]==words[j][0])
					tryword(i,j);
		if (best[i]+1<best[i+1]) best[i+1]=best[i]+1;
	}
	fprintf(out,"%i\n",best[n]);
	fclose(in); fclose(out); return 0;
}
```

# USACO FEB07 Problem 'silvlily' Analysis

by Richard Ho
We can treat this as a shortest path problem. At each square we keep track of how many lilypads we have to place to get there and how many jumps it took. We first want to minimize the lilypads and then minimize the jumps (moving onto a lilypad only takes one jump), while moving onto a blank square takes one lilypad + one jump.
We use BFS to update this information as we traverse the various routes. If a jump brings us to a square taking the same number of lilypads and jumps as it already says on the square, we can add the number of ways to that square. If we did better, we replace the number of ways to that square and add to queue. If we did worse, we don't update it. Below is code that matches this description.

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("silvlily.in", "r"), *out = fopen("silvlily.out", "w");
int m,n,d[50][50];
struct p {int x, y;};
class node
{
public:
	int bestlily;
	int bestjump;
	long long nways;
	node() {bestlily=-1; bestjump=-1; nways=0;}
};
node grid[50][50];
bool inq[50][50];
#define QSIZE 10000
p q[QSIZE];
int qstart,qend;

void enq(int x, int y)
{
	if (!inq[x][y])
	{
		inq[x][y]=true;
		q[qend].x=x;
		q[qend].y=y;
		qend++; qend%=QSIZE;
	}
}

void updateq(int x, int y, int bl, int bj, long long pways)
{
	if (grid[x][y].bestlily==-1 || bl<grid[x][y].bestlily)
	{
		grid[x][y].bestlily=bl;
		grid[x][y].bestjump=bj;
		grid[x][y].nways=pways;
		enq(x,y); return;
	}
	if (grid[x][y].bestlily==bl && bj<grid[x][y].bestjump)
	{
		grid[x][y].bestlily=bl;
		grid[x][y].bestjump=bj;
		grid[x][y].nways=pways;
		enq(x,y); return;
	}
	if (grid[x][y].bestlily==bl && bj==grid[x][y].bestjump)
	{
		grid[x][y].nways+=pways;
		return;
	}
}
int dirs[8][2]={{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
void processqhead(void)
{
	int x=q[qstart].x,y=q[qstart].y,nx,ny;
	for (int i=0;i<8;i++)
	{
		nx=x+dirs[i][0];
		ny=y+dirs[i][1];
		if (nx>=0 && ny>=0 && nx<m && ny<n)
		{
			if (d[nx][ny]!=2)
			
updateq(nx,ny,grid[x][y].bestlily+(d[nx][ny]==1?0:1),grid[x][y].bestjump+1,grid[x][y].nways);
		}
	}
	inq[x][y]=false;
	qstart++; qstart%=QSIZE;
}


int main(void)
{
	int i,j;
	p a,b;
	fscanf(in,"%i %i",&m,&n);
	for (i=0;i<m;i++) for (j=0;j<n;j++) fscanf(in,"%i",&d[i][j]);
	for (i=0;i<m;i++) for (j=0;j<n;j++)
	{
		if (d[i][j]==3) {d[i][j]=1; a.x=i;a.y=j;}
		if (d[i][j]==4) {d[i][j]=1; b.x=i;b.y=j;}
		inq[i][j]=false;
	}
	qstart=0; qend=0;
	updateq(a.x,a.y,0,0,1);
	while (qstart!=qend)
	{
		processqhead();
	}
	if (grid[b.x][b.y].bestlily==-1) fprintf(out,"-1\n");
	else
fprintf(out,"%i\n%i\n%lld\n",grid[b.x][b.y].bestlily,grid[b.x][b.y].bestjump,grid[b.x][b.y].nways);
	fclose(in); fclose(out); return 0;
}

```

# USACO FEB07 Problem 'sparty' Analysis

by Richard Ho
The solution to this task is equivalent to doing single source shortest path (Dijkstra) on farm X then doing it again with edges reversed. Add the forward and backward times of each farm and take maximum of these sums.

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("sparty.in", "r"), *out = fopen("sparty.out", "w");
int n,m,p;
int d[1000][1000];

void store(int a, int b, int c) {
	a--;b--;
	if (d[a][b]==-1 || c<d[a][b]) d[a][b]=c;
}

bool visited[1000];
int best1[1000];
int best2[1000];
void dijk1(void) {
	int i,t,bt;
	for (i=0;i<n;i++) {visited[i]=false; best1[i]=-1;}
	best1[p]=0;
	bool done;
	while(true) {
		done=true; bt=-1;
		for (i=0;i<n;i++) {
			if (!visited[i]&&best1[i]!=-1) {
				if (bt==-1 || best1[i]<bt) {t=i;bt=best1[i];}
				done=false;
			}
		}
		if (done) break;
		for (i=0;i<n;i++) {
			if (d[t][i]!=-1)
				if (best1[i]==-1 || best1[t]+d[t][i]<best1[i])
					best1[i]=best1[t]+d[t][i];
		}
		visited[t]=true;
	}
}
void dijk2(void) {
	int i,t,bt;
	for (i=0;i<n;i++) {visited[i]=false; best2[i]=-1;}
	best2[p]=0;
	bool done;
	while(true) {
		done=true; bt=-1;
		for (i=0;i<n;i++) {
			if (!visited[i]&&best2[i]!=-1) {
				if (bt==-1 || best2[i]<bt) {t=i;bt=best2[i];}
				done=false;
			}
		}
		if (done) break;
		for (i=0;i<n;i++) {
			if (d[i][t]!=-1)
				if (best2[i]==-1 || best2[t]+d[i][t]<best2[i])
					best2[i]=best2[t]+d[i][t];
		}
		visited[t]=true;
	}
}

int main(void) {
	int i,j,a,b,c;
	fscanf(in,"%i %i %i",&n,&m,&p); p--;
	for (i=0;i<n;i++) for (j=0;j<n;j++) d[i][j]=-1;
	for (i=0;i<m;i++) {
		fscanf(in,"%i %i %i",&a,&b,&c);
		store(a,b,c);
	}
	dijk1();
	dijk2();
	int r=0;
	for (i=0;i<n;i++)
	{
		if (best1[i]+best2[i]>r)
			r=best1[i]+best2[i];
	}
	fprintf(out,"%i\n",r);
	fclose(in); fclose(out); return 0;
}

```