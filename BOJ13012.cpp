//BOJ13012

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
#define MAXI 55

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


suffixNode suffixlist[MAXI], tempsort[MAXI];

int N, M, suffixarray[MAXI], idxinsl[MAXI], counting[MAXI + 1], lcp[MAXI];

//idxinsl: index of input[i] in suffixlist

vector<int> getsuffixarray(string inputstring) {
	N = inputstring.length();
	//memset()

	for (int i = 0; i < N; ++i) {
		suffixlist[i].saidx = i;
		suffixlist[i].rank.first = inputstring[i] - 'a';
		suffixlist[i].rank.second = (i < N - 1 ? inputstring[i + 1] - 'a' : -1);
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

	vector<int> ret;

	for (int i = 0; i < N; ++i) {
		suffixarray[i] = suffixlist[i].saidx;
		ret.push_back(suffixarray[i]);
		idxinsl[suffixarray[i]] = i;
	}

	return ret;

}

bool ispossible(string s) {
	if (s.length() == 0) return false;

	vector<int> sa = getsuffixarray(s);

	bool ret = false;

	if (s[sa[0]] > 'a') return true;

	for (int i = s.length() - 1; i > 0; --i) {
		char prev, now;
		// now: 현재 i 번째 접미사의 첫글자, prev: i-1 번째 접미사의 첫 글자
		prev = s[sa[i - 1]];
		now = s[sa[i]];

		if (now <= prev) continue; // 같다면 넘어간다
		else if (now > prev + 1) {
			//차이가 한 글자 이상 난다면 무조건 바꿀 수 있다
			ret = true;
			return ret;
		}
		else if (now == prev + 1) {
			//현재 접미사의 첫 글자를 바꿨을 때 이전 접미사의 첫 글자와 같아지는 경우
			//각 접미사의 두 번째 글자부터 시작하는 접미사의 위치를 비교한다.
			int nowsec, prevsec, nidx, pidx;
			nowsec = sa[i] + 1;
			prevsec = sa[i - 1] + 1;
			nidx = pidx = -1;
			for (int j = 0; j < s.length(); ++j) {
				if (sa[j] == prevsec) pidx = j;
				if (sa[j] == nowsec) nidx = j;
			}

			if (nidx < pidx) continue;
			//nidx 나 pidx 가 -1 인 경우는 마지막 글자부터 시작하는 1자리 접미사인 경우.
			//이 때 두 번째 글자부터 시작하는 접미사는 0자리 이므로, 무조건 사전순으로 앞에 와야한다.

			ret = true;
			return ret;
		}
	}

	
	//사전순으로 정렬한 첫 접미사가 a 보다 큰 알파벳으로 시작한다면 무조건 a로 교체할 수 있다.

	return ret;
}

//https://www.youtube.com/watch?v=pe65s8s05sU&feature=youtu.be

int main() {
	
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	string s;
	cin >> s;
	if (ispossible(s)) printf("1");
	else printf("0");

	return 0;

}