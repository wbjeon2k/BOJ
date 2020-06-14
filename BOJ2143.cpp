//BOJ2143
//using equal range
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int A[1010], B[1010], T, N, M;
int intervalA[1010], intervalB[1010];
vector<int> psumA, psumB;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	cin >> M;
	for (int i = 1; i <= M; ++i) {
		cin >> B[i];
	}

	for (int i = 1; i <= N; ++i) {
		int tmp = A[i];
		psumA.push_back(A[i]);
		for (int j = i + 1; j <= N; ++j) {
			tmp += A[j];
			psumA.push_back(tmp);
		}
	}

	for (int i = 1; i <= M; ++i) {
		int tmp = B[i];
		psumB.push_back(B[i]);
		for (int j = i + 1; j <= M; ++j) {
			tmp += B[j];
			psumB.push_back(tmp);
		}
	}

	sort(psumA.begin(), psumA.end());
	sort(psumB.begin(), psumB.end());

	ll cnt = 0;
	for (int i = 0; i < psumA.size(); ++i) {
		auto tmp = equal_range(psumB.begin(), psumB.end(), T - psumA[i]);
		ll a = tmp.second - tmp.first;
		cnt += a;
	}


	printf("%lld", cnt);
	return 0;

}




/*
//using two pointer algorithm
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int A[1010], B[1010], T, N, M;
int intervalA[1010], intervalB[1010];
vector<int> psumA, psumB;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	cin >> M;
	for (int i = 1; i <= M; ++i) {
		cin >> B[i];
	}

	for (int i = 1; i <= N; ++i) {
		int tmp = A[i];
		psumA.push_back(A[i]);
		for (int j = i+1; j <= N; ++j) {
			tmp += A[j];
			psumA.push_back(tmp);
		}
	}

	for (int i = 1; i <= M; ++i) {
		int tmp = B[i];
		psumB.push_back(B[i]);
		for (int j = i + 1; j <= M; ++j) {
			tmp += B[j];
			psumB.push_back(tmp);
		}
	}

	sort(psumA.begin(), psumA.end());
	sort(psumB.begin(), psumB.end());

	int s = 0, e = psumB.size() - 1;
	ll cnt = 0;
	while (1) {
		
		int intervalsum = psumA[s] + psumB[e];
		if (intervalsum > T) {
			--e;
		}
		else if (intervalsum < T) {
			++s;
		}
		else if (intervalsum == T) {
			ll a=1, b=1;
			while (s < psumA.size()-1 && psumA[s] == psumA[s+1]) {
				s++;
				a++;
			}
			while (e > 0 && psumB[e] == psumB[e - 1]) {
				e--;
				b++;
			}
			cnt += a * b;
			++s;
		}

		if (s > psumA.size() - 1 || e < 0) break;
	}
	

	printf("%lld", cnt);
	return 0;

}

*/