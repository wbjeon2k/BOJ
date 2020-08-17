//BOJ14003

//https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
//https://seungkwan.tistory.com/8
//https://jason9319.tistory.com/113

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> elements, L, P, ans;

void LIS() {

	for (int i = 0; i < N; ++i) {
		int lsize = L.size();
		if (L.size() == 0) {
			L.push_back(elements[i]);
			P.push_back(1);
		}

		else if (L[lsize - 1] < elements[i]) {
			L.push_back(elements[i]);
			P.push_back(L.size());
		}
		
		else {
			auto iter = lower_bound(L.begin(), L.end(), elements[i]);
			*iter = elements[i];
			P.push_back(iter - L.begin() + 1);
		}
	}

	return;
}

void backtrack(int pidx, int lidx) {
	if (pidx == 0) return;

	if (P[pidx - 1] == lidx) {
		ans.push_back(elements[pidx - 1]);
		backtrack(pidx - 1, lidx - 1);
	}
	else backtrack(pidx - 1, lidx);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		elements.push_back(t);
	}

	LIS();

	printf("%d\n", L.size());

	int l = 1;


	
	backtrack(N, L.size());

	//sort(ans.begin(), ans.end());

	for (int i = ans.size(); i > 0; --i) {
		printf("%d ", ans[i - 1]);
	}
	printf("\n");
	

	return 0;

}