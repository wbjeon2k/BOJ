#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>

/*debug
	ifstream cin;
	cin.open("input.txt");
*/

int N, K;

int input[300300];

priority_queue<pii> pq;
pii used = { -1,-1 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < K; ++i) {
		int t;
		cin >> t;
		input[i] = t;

		pq.push({ t,i + 1 });
	}

	bool chk = true;
	

	for (int i = 0; i < K; ++i) {
		if ((input[i]-1) * 2 >= N) {
			printf("-1");
			return 0;
		}
	}

	int before = -1;
	vector<int> anslist;
	while (!pq.empty()) {
		pii colornow = pq.top();
		pq.pop();

		if (used != make_pair(-1, -1) && used.first != 0) pq.push(used);
		if (colornow.second == before) {
			chk == false;
			break;
		}

		anslist.push_back(colornow.second);
		colornow.first -= 1;
		before = colornow.second;

		used = colornow;
	}

	if (chk) {
		for (int i = 0; i < anslist.size(); ++i) {
			printf("%d ", anslist[i]);
		}
	}
	else printf("-1");

	return 0;
}