//BOJ17406

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int arr[55][55];

int N, M, K;

struct tup {
	int x, y, z;
};

vector<tup> rlist;
vector<int> permlist;

void prt(int n, int m) {
	for (int i = 1; i < n+1; ++i) {
		for (int j = 1; j < m+1; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void rotate(int r, int c, int s) {
	for (int i = 1; i <= s; ++i) {
		int tmp = 0;

		tmp = arr[r - i][c + i];
		for (int j = c + i; j > c-i; --j) {
			arr[r - i][j] = arr[r - i][j - 1];
		}
		for (int j = r-i; j <r+i; ++j) {
			arr[j][c-i] = arr[j+1][c-i];
		}
		for (int j = c - i; j < c+i; ++j) {
			arr[r + i][j] = arr[r + i][j + 1];
		}
		for (int j = r+i; j > r-i; --j) {
			arr[j][c+i] = arr[j-1][c+i];
		}
		arr[r - i + 1][c + i] = tmp;
	}
}


int minrow() {
	int ans = INT_MAX;
	for (int i = 1; i <= N; ++i) {
		int tmp = 0;
		for (int j = 1; j <= M; ++j) {
			tmp += arr[i][j];
		}
		ans = min(ans, tmp);
	}

	return ans;
}

int main() {
	
	cin >> N >> M >> K;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> arr[i][j];
		}
	}

	int origin[55][55];
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			origin[i][j] = arr[i][j];
		}
	}


	for (int i = 0; i < K; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		rlist.push_back({ a,b,c });
		permlist.push_back(i+1);
	}

	int ans = INT_MAX;
	do {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				arr[i][j] = origin[i][j];
			}
		}

		for (int i = 0; i < K; ++i) {
			tup t = rlist[permlist[i]-1];
			rotate(t.x, t.y, t.z);
			//prt(N, M);
		}


		ans = min(ans, minrow());
	} while (next_permutation(permlist.begin(),permlist.end()));


	printf("%d\n", ans);
	return 0;

}