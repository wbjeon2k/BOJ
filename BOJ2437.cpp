// BOJ 2437

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<int> weightlist, possible;
int N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	cin >> N;
	
	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		weightlist.push_back(t);
	}

	sort(weightlist.begin(), weightlist.end());

	bool chk = false;
	int tsum = 0;
	for (int i = 0; i < weightlist.size(); ++i) {
		//printf("tsum%d\n", tsum);
		if (tsum + 1 < weightlist[i]) {
			printf("%d\n", tsum + 1);
			chk = true;
			break;
		}
		tsum += weightlist[i];
	}

	if (!chk) {
		printf("%d\n", tsum + 1);
	}

	return 0;
}

/*
//1st trial. TLE
// BOJ 2437

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<int> weightlist, possible;
map<int, int> chk;
int N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	cin >> N;

	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		weightlist.push_back(t);
	}

	sort(weightlist.begin(), weightlist.end());

	possible.push_back(0);
	for (int i = 0; i < N; ++i) {
		int psize = possible.size();
		for (int j = 0; j < psize; ++j) {
			int t = possible[j] + weightlist[i];
			if (chk[t] == 1) continue;
			chk[t] = 1;
			possible.push_back(t);
		}
	}

	sort(possible.begin(), possible.end());

	for (int i = 0; i < possible.size() - 1; ++i) {
		if (possible[i + 1] - possible[i] != 1) {
			printf("%d\n", possible[i] + 1);
			break;
		}

		if (i == possible.size() - 2) {
			printf("%d\n", possible[i + 1] + 1);
			break;
		}
	}

	return 0;
}
*/