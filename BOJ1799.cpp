//BOJ1799

//이분 매칭으로도 해결 가능.

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
int input[11][11], up[33], down[33];
int white, black;

//up white: x + y == 2k+1, black: x+y == 2k
//down white: x-y+N == 2k, black: x-y+N == 2k+1

void bishop(int x, int y, int cnt) {
	bool isWhite = (x + y) % 2;

	if (y > N) {
		//when N==5
		//(1,7)->(2,2)
		//(2,6)->(3,1)
		++x;
		if (y % 2)y = 2;
		else y = 1;
	}

	if (x > N) {
		if (isWhite) white = max(white, cnt);
		else black = max(black, cnt);

		return;
	}

	if (input[x][y] == 1 && !up[x + y] && !down[x - y + N]) {
		//(x,y) 에 비숍 놓을때
		up[x + y] = 1;
		down[x - y + N] = 1;
		bishop(x, y + 2, cnt + 1);
		up[x + y] = 0;
		down[x - y + N] = 0;
	}

	bishop(x, y + 2, cnt);
	

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> input[i + 1][j + 1];
		}
	}

	bishop(1, 1, 0);
	bishop(1, 2, 0);

	printf("%d\n", white + black);

	return 0;
}

/*
//1st trial. TLE.
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct board {
	vector<vector<int>> mat;

	board() {
		mat.resize(11);
		for (int i = 0; i < 11; ++i) mat[i].resize(11, 0);
	}

	board(vector<vector<int>> init) {
		for (int i = 0; i < 11; ++i) mat[i] = init[i];
	}

	board operator = (board rhs) {
		for (int i = 0; i < 11; ++i) {
			mat[i] = rhs.mat[i];
		}
		return *this;
	}

	bool canbishop(int x, int y) {
		if (mat[x][y] == 2 || mat[x][y] == 0) return false;

		for (int i = 1; i <= 10; ++i) {
			if (i + x <= 10 && i + y <= 10 && mat[x + i][y + i] == 2) return false;
			if (i + x <= 10 && y - i >= 1 && mat[x + i][y - i] == 2) return false;
			if (x - i >= 1 && i + y <= 10 && mat[x - i][y + i] == 2) return false;
			if (x - i >= 1 && y - i >= 1 && mat[x - i][y - i] == 2) return false;
		}

		return true;
	}

	void bprint(int n) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				printf("%d ", mat[i][j]);
			}
			printf("\n");
		}
	}

};

board putbishop(int x, int y, board& b) {
	board ret = b;

	ret.mat[x][y] = 2;

	for (int i = 1; i <= 10; ++i) {
		if (i + x <= 10 && i + y <= 10) (ret.mat[x + i][y + i] == 2 ? 2 : 0);
		if (i + x <= 10 && y - i >= 1) (ret.mat[x + i][y - i] == 2 ? 2 : 0);
		if (x - i >= 1 && i + y <= 10) (ret.mat[x - i][y + i] == 2 ? 2 : 0);
		if (x - i >= 1 && y - i >= 1) (ret.mat[x - i][y - i] == 2 ? 2 : 0);
	}

	return ret;
}


board input;
int N;


int maxput(board b) {
	int ret = 0;
	for (int i = 1; i <= 10; ++i) {
		for (int j = 1; j <= 10; ++j) {
			if (b.canbishop(i, j)) ret = max(ret, 1 + maxput(putbishop(i, j, b)));
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> input.mat[i + 1][j + 1];
		}
	}



	int ans = 0;
	ans = maxput(input);

	printf("%d\n", ans);

	return 0;
}
*/