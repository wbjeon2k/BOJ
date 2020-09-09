//BOJ6217

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

vector<pii> input;
int seestack[10010];
int N, I, H, R;

bool comp(pii& a, pii& b) {
	if (a.first < b.first) return true;
	if (a.first == b.first && a.second < b.second) return true;

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> I >> H >> R;

	for (int i = 0; i < R; ++i) {
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		input.push_back({ a,b });
	}

	sort(input.begin(), input.end(), comp);

	for (int i = 0; i < R; ++i) {
		if (i > 0 && input[i] == input[i - 1]) continue;
		if (input[i].second - input[i].first < 2) continue;

		--seestack[input[i].first + 1];
		++seestack[input[i].second];
	}


	int cnt = 0;

	for (int i = 1; i <= N; ++i) {
		cnt += seestack[i];
		printf("%d\n", H + cnt);
	}

	return 0;
}

/*
//koosaga's solution.
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int dx[10005];
set<pi> st;

int main(){
	int n, h, q;
	scanf("%d %*d %d %d",&n,&h,&q);
	while(q--){
		int s, e;
		scanf("%d %d",&s,&e);
		if(st.find(pi(s, e)) != st.end()) continue;
		st.insert(pi(s, e));
		if(s > e) swap(s, e);
		dx[s+1]--;
		dx[e]++;
	}
	dx[1] += h;
	dx[n+1] -= h;
	for(int i=1; i<=n; i++){
		dx[i] += dx[i-1];
		printf("%d\n", dx[i]);
	}
}
*/

/*
//xiaowuc1's solution.
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef vector<int> vi;
// END NO SAD

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> matrix;
typedef pair<ll, ll> pll;

bool piisort(pii a, pii b) {
  return abs(a.first-a.second) > abs(b.first-b.second);
}

pii l[10000];
int ret[10000];
void solve() {
  int n, _, h, k;
  cin >> n >> _ >> h >> k;
  for(int i = 0; i < k; i++) {
	cin >> l[i].first >> l[i].second;
	l[i].first--;
	l[i].second--;
  }
  sort(l, l+k, piisort);
  for(int i = 0; i < n; i++) {
	ret[i] = h;
  }
  for(int i = 0; i < k; i++) {
	if(l[i].first < l[i].second) {
	  for(int a = l[i].first+1; a < l[i].second; a++) ret[a] = ret[l[i].first]-1;
	}
	else {
	  for(int a = l[i].first-1; a > l[i].second; a--) ret[a] = ret[l[i].first]-1;
	}
  }
  for(int i = 0; i < n; i++) cout << ret[i] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  solve();
}
*/

/*
//USACO's official solution.
#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>

#define MAXN 500000
#define MAXR 2*MAXN

int N, I, H, R;
int bucket[MAXN], order[MAXR], pairs[MAXR][2];
int interval[MAXN];

void radix_sort()
{
	int r, i;
	for (r = 0; r < 2; ++r)
	{
		for (i = 0; i < N; ++i) bucket[i] = 0;
		for (i = 0; i < R; ++i) ++bucket[pairs[i][r]];
		for (i = 1; i < N; ++i) bucket[i] += bucket[i - 1];
		for (i = N; i > 0; --i) bucket[i] = bucket[i - 1];
		bucket[0] = 0;
		for (i = 0; i < R; ++i) order[bucket[pairs[i][r]]++] = i;
	}
}

void trim_same()
{
	int r, i;
	radix_sort();
	r = 1;
	for (i = 1; i < R; ++i)
	{
		if (pairs[order[i]][0] == pairs[order[i - 1]][0] &&
			pairs[order[i]][1] == pairs[order[i - 1]][1])
			continue;
		order[r++] = order[i];
	}
	R = r;
}

int main()
{
	int i, a, b;
	scanf("%d %d %d %d", &N, &I, &H, &R);
	for (i = 0; i < R; ++i)
	{
		scanf("%d %d", &a, &b);
		--a;
		--b;
		if (a < b) {
			pairs[i][0] = a;
			pairs[i][1] = b;
		}
		else {
			pairs[i][0] = b;
			pairs[i][1] = a;
		}
		order[i] = i;
	}

	trim_same();            //Each interval should be examined once
	for (i = 0; i < R; ++i)
	{
		a = pairs[order[i]][0];
		b = pairs[order[i]][1];
		--interval[a + 1];
		++interval[b];
	}

	a = 0;
	for (i = 0; i < N; i++)
	{
		a += interval[i];
		printf( "%d\n", H + a);
	}
	return 0;
}
*/

/*
//1st trial. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>

vector<pii> adjList(10010);
bool visited[10010];
int depth[10010];
int N, I, H, R;

void dfs(int here, int dep) {
	visited[here] = true;

	int mini, maxi;
	mini = adjList[here].first;
	maxi = adjList[here].second;

	for (int i = mini + 1; i < maxi; ++i) {
		if (visited[i]) continue;

		dfs(i, dep + 1);
	}

	visited[here] = false;
	depth[here] = max(depth[here],dep);
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> I >> H >> R;

	for (int i = 1; i < 10010; ++i) {
		adjList[i].first = i;
		adjList[i].second = i;
	}

	for (int i = 0; i < R; ++i) {
		int a, b;
		cin >> a >> b;

		if (adjList[a].first > b) adjList[a].first = b;
		if (adjList[a].second < b) adjList[a].second = b;

		if (adjList[b].first > a) adjList[b].first = a;
		if (adjList[b].second < a) adjList[b].second = a;
		
	}

	memset(depth, 0, sizeof(depth));
	memset(visited, 0, sizeof(visited));
	dfs(I, 0);

	for (int i = 1; i <= N; ++i) {
		if (!visited[i]) {
			dfs(i, 0);
		}
	}

	for (int i = 1; i <= N; ++i) {
		printf("%d\n", H - depth[i]);
	}

	return 0;
}

*/