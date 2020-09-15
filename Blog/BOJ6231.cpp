//BOJ6231

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
int N, K, ans;

map<vi, int> mp;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> K;

	ans = 0;
	vi featureID(K);
	mp[featureID] = 0;

	//featureID : 1~K 까지 p 에 대해 psum[i][p] - psum[i][0] 가 적용된 누적합

	for (int i = 1; i <= N; ++i) {
		int t, x;
		cin >> t;
		x = t;
		for (int j = 0; j < K; ++j) {
			featureID[j] += t % 2;
			t /= 2;
			//누적합을 더해준다.
		}

		if ( x%2 ) {
			for (int j = 0; j < K; ++j) --featureID[j];
			//psum[i][0] 를 빼준다.
		}

		/*
		for (int j = 0; j < K; ++j) {
			printf("%d ", featureID[j]);
		}
		printf("\n");
		*/
		

		if (mp.count(featureID)) {
			//일치하는 누적합 상태가 있는지 확인. 있으면 현재 위치 - 누적합 위치가 구간 길이.
			ans = max(ans, i - mp[featureID]);
		}
		else mp[featureID] = i;
		//없으면 위치 표시.
	}

	printf("%d\n", ans);

	return 0;

}

/*
//first attempt. WA.
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100
#define ll long long

ll N, K, ans;

ll field[Msize][33], psum[Msize][33];

void fillfield() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;

	for (int i = 1; i <= N; ++i) {
		ll tmp;
		cin >> tmp;

		for (int j = 0; j < K; ++j) {
			field[i][j] = tmp % 2;
			tmp /= 2;
		}
	}

	return;
}

void getpsum() {
	for (int i = 0; i < K; ++i) psum[0][i] = 0;

	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < K; ++j) {
			psum[i][j] = psum[i - 1][j] + field[i][j];
		}
	}

	return;
}

void findmatch() {
	ans = 0;

	for (int i = K; i <= N; ++i) {
		for (int j = i - K; j > 0; j -= K) {
			bool chk = true;
			ll gap = psum[i][0] - psum[j-1][0];
			for (int k = 0; k < K; ++k) {
				if (psum[i][k] - psum[j-1][k] == gap) continue;

				chk = false;
				break;
			}
			if (chk) {
				ans = max(ans, (ll)i - j + 1);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	fillfield();
	getpsum();
	findmatch();

	printf("%lld\n", ans);

	return 0;
}
*/