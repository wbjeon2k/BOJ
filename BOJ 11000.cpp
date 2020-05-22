#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

vector<pii> input;
int N;

struct pcomp {
	bool operator()(const pii& a, const pii& b) {
		if (a.second > b.second) {
			return true;
		}

		return false;
	}
};


priority_queue<pii, vector<pii>, pcomp> pq;

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		input.push_back({ a,b });
	}

	sort(input.begin(), input.end());

	pq.push(input[0]);

	for (int i = 1; i < input.size(); ++i) {
		if (input[i].first >= pq.top().second) {
			pq.pop();
			pq.push(input[i]);
		}
		else {
			pq.push(input[i]);
		}
	}

	printf("%d", pq.size());

	return 0;

}

/* 
//TC gen
#include <bits/stdc++.h>
using namespace std;

int chk[101];
int main() {
	memset(chk,-1,sizeof(chk));
	printf("100\n");
	for(int i=0;i<100;++i){
		int t = rand()%100 + 1;
		while(chk[t] != -1){
			t = rand()%100 + 1;
		}

		printf("%d %d\n", t, t + rand()%25 + 1);
	}
	return 0;
}

*/

/*
//queued_q's solution.
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
using lld = long long;
using pii = pair<int, int>;
using pll = pair<lld, lld>;

////////////////////////////////////////////////////////////////
int N;
vector<pii> A;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ////////////////////////////////

  cin >> N;
  A.resize(N);
  for (int i=0; i<N; i++) cin >> A[i].first >> A[i].second;
  sort(A.begin(), A.end());

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i=0; i<N; i++) {
	if (pq.empty() || pq.top() > A[i].first) {
	  pq.push(A[i].second);
	} else {
	  pq.pop();
	  pq.push(A[i].second);
	}
  }

  cout << pq.size() << endl;

  ////////////////////////////////
  return 0;
}

*/