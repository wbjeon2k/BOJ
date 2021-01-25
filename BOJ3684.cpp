//BOJ3864

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
const int MAXI=41000;

char inputstring[MAXI];
int lcp[MAXI], suffixarray[MAXI];

namespace SA { //special thanks to cubelover
	using namespace std;
	const int MAXI = 1 << 18 | 5;
	const int n_char = 128;

	int T[MAXI]; //tmp counting array for radix sort
	void radix_sort(const int* A, const int* V, int* F, int n, int m) {
		fill(T, T + m + 1, 0);
		for (int i = 0; i < n; i++) ++T[V[A[i]]];
		for (int x = 1; x <= m; x++) T[x] += T[x - 1];
		for (int i = n; i--;) F[--T[V[A[i]]]] = A[i];
	}

	int G[MAXI]; //group number
	int tG[MAXI]; //tmp group number
	// arr[i] : 0 - based starting index of lexicographically i-th suffix
	void suffix_array(const char* S, int* arr, int n) {
		for (int i = 0; i < n; i++) {
			G[i] = S[i]; //first priority : char value
			tG[i] = i; //second priority : starting index
		}
		radix_sort(tG, G, arr, n, n_char); //preprocess : sort by character value
		for (int i = 1, k = 1; i < n && k < n; i <<= 1) {
			for (k = 0; k < i; k++) tG[k] = k - i + n; //second priority : short strings are needn't to be compared
			for (int j = 0; j < n; j++) {
				if (arr[j] >= i) {
					tG[k++] = arr[j] - i; //second priority : x + i - th character's priority
				}
			}
			radix_sort(tG, G, arr, n, n);
			tG[arr[0]] = k = 1;
			for (int j = 1; j < n; j++) {
				if (G[arr[j]] != G[arr[j - 1]] || G[arr[j] + i] != G[arr[j - 1] + i]) ++k;
				tG[arr[j]] = k;
			}
			for (int j = 0; j < n; j++) G[j] = tG[j];
		}
	}

	int* R = tG; //to save memory
	void lcp_array(const int* sfx, const char* S, int* L, int n) {
		for (int i = 0; i < n; i++) R[sfx[i]] = i;
		for (int i = 0, j = 0; i < n; i++) {
			if (R[i]) { // to avoid making lcp for the least string lexicographically
				while (S[i + j] == S[sfx[R[i] - 1] + j]) ++j;
				L[R[i]-1] = j;
			}
			if (j) --j; //Fact : if lcp(i,i-1) >= 1, lcp(i+1,i) >= lcp(i,i-1) - 1. Which guarantees O(n) complexity.
		}
	}
}

int t, start, cnt, ans;
pii tmp = { -1,-1 };

bool ispossible(int m) {
	//길이 m 인 문자열 t-1 번 이상 등장하면 true.
	//O(N)
	bool chk = false;
	cnt = 0;
	int tstart = start = 0;
	for (int i = 0; i < strlen(inputstring) - 1; ) {
		//lcp[i]: i 번째 suffix 와 i+1 번째 suffix 겹치는 길이.
		if (lcp[i] < m) ++i;
		else {
			cnt = 0;
			int l, now;
			l = now = i;
			while (lcp[now] >= m) {
				tstart = max(tstart, suffixarray[now]);
				++now;
				++cnt;
			}
			tstart = max(tstart, suffixarray[now]);
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			if (cnt >= t - 1) {
				chk = true;
				start = max(start, tstart);
			}

			tstart = -1;
			i = now;
		}

	}

	if (chk) tmp = { m,start };

	return chk;
}

void getans() {
	//parametric search.
	//길이 mid 인 문자열 t-1 번 이상 등장하면 true.
	
	int hi = strlen(inputstring), lo = 0;

	bool chk = false;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (ispossible(mid)) {
			lo = mid;
			chk = true;
		}
		else hi = mid;
	}
	ispossible(lo);
	ispossible(hi);

	if(chk) ans = tmp.first;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	while (1) {
		
		tmp = { -1,-1 };
		memset(suffixarray, 0, sizeof(suffixarray));
		memset(lcp, 0, sizeof(lcp));

		scanf("%d", &t);
		if (t == 0) break;
		scanf("%s", &inputstring);
		SA::suffix_array(inputstring, suffixarray, strlen(inputstring));
		SA::lcp_array(suffixarray, inputstring, lcp, strlen(inputstring));

		ans = -1;
		getans();

		if (t == 1) {
			printf("%d 0\n", strlen(inputstring));
			//예외처리. 한 번만 나오는 가장 긴 문자열은 입력 그 자체.
		}
		else if (ans > 0) {
			printf("%d %d\n", tmp.first, tmp.second);
		}
		else printf("none\n");

	}

	return 0;

}
