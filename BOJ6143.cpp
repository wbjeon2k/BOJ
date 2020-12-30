//BOJ6143

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>

/*debug
	ifstream cin;
	cin.open("input.txt");
*/

#define pll pair<ll, ll>
#define INF LLONG_MAX/4
#define MAXI 100100

/*
https://gist.github.com/dipu-bd/bebb1aae8a87d64d60cb338600f4fec3
https://blog.naver.com/kks227/221220566367
https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/

*/

struct suffixNode {
	int saidx; // original index in input string
	pii rank; // pair of {rank, next rank}

	bool operator < (const suffixNode& rhs) {
		return rank < rhs.rank;
	}
};

char inputstring[MAXI];
suffixNode suffixlist[MAXI], tempsort[MAXI];

int N, M, suffixarray[MAXI], idxinsl[MAXI], counting[MAXI + 1], lcp[MAXI];

//idxinsl: index of input[i] in suffixlist

void getsuffixarray() {
	N = strlen(inputstring);

	for (int i = 0; i < N; ++i) {
		suffixlist[i].saidx = i;
		suffixlist[i].rank.first = inputstring[i] - 'A';
		suffixlist[i].rank.second = (i < N - 1 ? inputstring[i + 1] - 'A' : -1);
	}

	sort(suffixlist, suffixlist + N);

	for (int t = 2; t < N; t *= 2) {


		int rank, prev_first_rank;
		//prev_first_rank : value of suffixlist[i-1].rank.first before modified
		rank = 0;

		idxinsl[suffixlist[0].saidx] = 0;

		prev_first_rank = suffixlist[0].rank.first;
		suffixlist[0].rank.first = 0;

		for (int i = 1; i < N; ++i) {

			if (make_pair(prev_first_rank, suffixlist[i - 1].rank.second) != suffixlist[i].rank) ++rank;
			prev_first_rank = suffixlist[i].rank.first;
			suffixlist[i].rank.first = rank;

			idxinsl[suffixlist[i].saidx] = i;
		}
		++rank;

		for (int i = 0; i < N; ++i) {
			int tnext = suffixlist[i].saidx + t;
			suffixlist[i].rank.second = (tnext < N ? suffixlist[idxinsl[tnext]].rank.first : -1);
			//find index of input[tnext] by idxinsl[tnext]
		}

		//radix sort

		//regard {rank, next rank} as a two digit number

		memset(counting, 0, sizeof(counting));

		for (int i = 0; i < N; ++i) counting[1 + suffixlist[i].rank.second]++;
		for (int i = 1; i <= rank; ++i) counting[i] += counting[i - 1];
		for (int i = N - 1; i >= 0; --i) {
			--counting[1 + suffixlist[i].rank.second];
			tempsort[counting[1 + suffixlist[i].rank.second]] = suffixlist[i];
		}

		memset(counting, 0, sizeof(counting));

		for (int i = 0; i < N; ++i) counting[tempsort[i].rank.first]++;
		for (int i = 1; i <= rank; ++i) counting[i] += counting[i - 1];
		for (int i = N - 1; i >= 0; --i) {
			--counting[tempsort[i].rank.first];
			suffixlist[counting[tempsort[i].rank.first]] = tempsort[i];
		}
	}

	for (int i = 0; i < N; ++i) {
		suffixarray[i] = suffixlist[i].saidx;
		idxinsl[suffixarray[i]] = i;
	}

	return;

}


void getLCP() {
	// idxinsl[suffixarray[i]] == i is guaranteed

	for (int i = 0, k = 0; i < N; ++i, k = (k > 0 ? --k : 0)) {
		if (idxinsl[i] == N - 1) continue;

		for (int j = suffixarray[idxinsl[i] + 1]; inputstring[i + k] == inputstring[j + k]; ++k);
		lcp[idxinsl[i]] = k;

	}
}

int T;

string ans = "";

int sainverse[MAXI];

void proc(int x, int y) {
	if (x == y) {
		ans += inputstring[x];
		return;
	}

	if (sainverse[x] < sainverse[2*T - 1 - y]) {
		ans += inputstring[x];
		++x;
	}
	else {
		ans += inputstring[y];
		--y;
	}

	proc(x, y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(inputstring, 0, sizeof(inputstring));

	cin >> T;

	for (int i = 0; i < T; ++i) {
		cin >> inputstring[i];
		inputstring[2 * T - 1 - i] = inputstring[i];
	}
	getsuffixarray();

	
	for (int i = 0; i < N; ++i) {
		sainverse[suffixarray[i]] = i;
	}
	//getLCP();
	
	proc(0, T - 1);

	for (int i = 0; i < ans.length(); ++i) {
		printf("%c", ans[i]);
		if ((i + 1) % 80 == 0) printf("\n");
	}
	printf("\n");
	
	
	return 0;

}

/*
//O(N^2) greedy solution.
//TASK: bcl
//LANG: C++
//USER: christos

#include<cstdio>

char S[2010], ln = 0;

void prnt(char a) {
	if (ln == 80) { printf("\n"); ln = 0; }
	printf("%c", a); ln++;
}

int main() {
	int i, j, N, pi, pj, val;
	freopen("bcl.in", "r", stdin);
	freopen("bcl.out", "w", stdout);
	scanf("%d", &N);
	for (i = 0; i < N; i++) scanf(" %c ", S + i);
	i = 0, j = N - 1;
	while (i <= j) {
		if (S[i] < S[j]) { prnt(S[i]); i++; }
		else if (S[i] > S[j]) { prnt(S[j]); j--; }
		else {
			pi = i + 1; pj = j - 1; val = S[i];
			while (pj - pi > 1 && S[pi] == S[pj]) { pi++, pj--; }
			if (S[pi] < S[pj]) prnt(S[i]), i++;
			else prnt(S[j]), j--;
		}
	}
	printf("\n");
	return 0;
}
*/