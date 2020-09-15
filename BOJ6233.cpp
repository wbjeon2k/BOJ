//BOJ 6233

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;

bitset<5050> input, cowface;
int farr[5050];

int cowflip(bitset<5050>& cface, int len, int flips) {
	int flipcnt = 0, flipcarry = 0 ;

	memset(farr, 0, sizeof(farr));

	for (int i = 0; i <= N - len; ++i) {
		if ((flipcarry + cface[i]) % 2) {
			farr[i] = 1;
			++flipcnt;
		}

		flipcarry += farr[i];

		if (i - len + 1 >= 0) flipcarry -= farr[i - len + 1];
	}

	for (int i = N - len + 1; i < N; ++i) {
		if ((flipcarry + cface[i]) % 2) return -1;

		if (i - len + 1 >= 0) flipcarry -= farr[i - len + 1];
	}
	
	return flipcnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	int longestbcnt = 0, tcnt = 0;

	for (int i = 0; i < N; ++i) {
		char C;
		cin >> C;
		if (C == 'F') {
			input[i] = 0;
		}
		else {
			input[i] = 1;
		}
	}

	int fcnt, lcnt;

	fcnt = INT_MAX, lcnt = -1;
	
	for (int i = N; i >= 1; --i) {
		cowface = input;
		int t = cowflip(cowface, i, 0);
		if (t == -1) continue;

		if (fcnt > t) {
			fcnt = t;
			lcnt = i;
		}
		else if (fcnt == t && lcnt < i) {
			lcnt = i;
		}
		
		break;
	}

	printf("%d %d\n", lcnt, fcnt);

	return 0;
}

/*
//koosaga's solution. using queue.

#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int n;
char str[5005];
int ret[5005];

int solve(int x){
	int cnt = 0, ret = 0;
	queue<int> q;
	for (int i=0; i<n; i++) {
		if((cnt&1) ^ (str[i] == 'B')) {
			cnt++;
			ret++;
			q.push(i + x - 1);
		}
		if(!q.empty() && q.front() == i) q.pop(), cnt--;
	}
	if(!q.empty()) return 1e9;
	return ret;
}

int main(){
	scanf("%d\n",&n);
	for (int i=0; i<n; i++) {
		scanf("%c\n",&str[i]);
	}
	for (int i=1; i<=n; i++) {
		ret[i] = solve(i);
	}
	int* p = min_element(ret+1,ret+n+1);
	printf("%d %d",(int)(p - ret),*p);
}
*/