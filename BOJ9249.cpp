//BOJ9249

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 501000

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
		suffixlist[i].rank.first = inputstring[i] - '$';
		suffixlist[i].rank.second = (i < N - 1 ? inputstring[i + 1] - '$' : -1);
		//ascii code of A is smaller than a. inputstring[i] - 'a' is buggy with strings including capital letters.
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

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	string s, e;
	cin >> s >> e;
	s += "$";
	s += e;

	for (int i = 0; i < s.size(); ++i) inputstring[i] = s[i];
	inputstring[s.size()] = '\0';

	getsuffixarray();
	getLCP();

	int start, maxlen, dummy;
	start = 0, maxlen = -1;
	dummy = s.size() - e.size() - 1;
	for (int i = 0; i < s.size() - 1; ++i) {
		if ((suffixarray[i] > dummy&& suffixarray[i + 1] < dummy) || (suffixarray[i] < dummy && suffixarray[i + 1] > dummy)) {
			if (lcp[i] > maxlen) {
				maxlen = lcp[i];
				start = i;
			}
		}
	}

	printf("%d\n", maxlen);
	for (int i = suffixarray[start]; i < suffixarray[start] + maxlen; ++i) {
		printf("%c", s[i]);
	}
	printf("\n");


	return 0;

}
