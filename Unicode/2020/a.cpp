#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>

/*debug
	ifstream cin;
	cin.open("input.txt");
*/

int N;

vector<int> input, sorted;

int bisearch(int q) {
	int lo = 0, hi = N - 1;

	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (sorted[mid] > q) hi = mid;
		else if (sorted[mid] < q) lo = mid + 1;
		else return mid;
	}

	return lo;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		input.push_back(t);
	}

	sorted = input;
	sort(sorted.begin(), sorted.end());

	bool chk = true;


	for (int i = 0; i < N; ++i) {
		int test = input[i];
		int idx = bisearch(test);
		//printf("idx %d\n", idx);
		if ((idx - i) % 2) {
			chk = false;
			break;
		}
	}

	if (chk) printf("YES");
	else printf("NO");
	return 0;
}