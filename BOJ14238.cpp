//BOJ14238

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool cache[55][55][55][4][4];
int A, B, C, N;

char anslist[55];

bool dp(int a, int b, int c, int prev1, int prev2) {
	if (a == A && b == B && c == C) return true;

	if (a > A || b > B || c > C) return false;

	if (cache[a][b][c][prev1][prev2]) return false;
	cache[a][b][c][prev1][prev2] = true;


	if (dp(a + 1, b, c, 1, prev1)) {
		anslist[a + b + c] = 'A';
		return true;
	}

	if (prev1 != 2 && dp(a, b+1, c, 2, prev1)) {
		anslist[a + b + c] = 'B';
		return true;
	}

	if (prev1 != 3 && prev2 != 3 && dp(a, b, c+1, 3, prev1)) {
		anslist[a + b + c] = 'C';
		return true;
	}

	return false;
}

int main() {
	memset(cache, 0, sizeof(cache));
	A = B = C = N = 0;


	string s;
	cin >> s;

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == 'A') ++A;
		if (s[i] == 'B') ++B;
		if (s[i] == 'C') ++C;
	}

	N = A + B + C;

	if (!dp(0, 0, 0, 0, 0)) printf("-1");
	else {
		for (int i = 0; i < N; ++i) printf("%c", anslist[i]);
		printf("\n");
	}
	

	return 0;
}

/*
//1st attempt. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int cache[10][55][55][55];

/*
state: 1~9
AA AB AC
BA BB BC
CA CB CC


struct tup {
	int s, a, b, c;

	bool operator==(const tup& rhs) {
		if (s == rhs.s && a == rhs.a && b == rhs.b && c == rhs.c) return true;
		else return false;
	}
};



/*
front:
1:123
2:46
3:78
4:123
5:
6:78
7:12
8:4
9:

void bfs() {
	queue<tup> q;

	q.push({ 1,2,0,0 });
	q.push({ 2,1,1,0 });
	q.push({ 3,1,0,1 });
	q.push({ 4,1,1,0 });
	q.push({ 6,0,1,1 });
	q.push({ 7,1,0,1 });
	q.push({ 8,0,1,1 });

	while (!q.empty()) {
		tup here = q.front();
		q.pop();

		int s = here.s, a = here.a, b = here.b, c = here.c;

		if (a > 50 || b > 50 || c > 50) continue;

		cache[s][a][b][c] = true;

		if (s == 1) {
			if (cache[1][a + 1][b][c] == -1) {
				cache[1][a + 1][b][c] = true;
				q.push({ 1,a + 1,b,c });
			}

			if (cache[2][a][b+1][c] == -1) {
				cache[2][a][b + 1][c] = true;
				q.push({ 2,a,b + 1,c });
			}
			
			if (cache[3][a][b][c+1] == -1) {
				cache[3][a][b][c + 1] = true;
				q.push({ 3,a,b,c + 1 });
			}
			
		}

		if (s == 2) {
			if (cache[4][a + 1][b][c] == -1) {
				cache[4][a + 1][b][c] = true;
				q.push({ 4,a + 1,b,c });
			}

			if (cache[6][a][b][c+1] == -1) {
				cache[6][a][b][c+1] = true;
				q.push({ 6,a,b,c+1 });
			}

		}

		if (s == 3) {
			if (cache[7][a + 1][b][c] == -1) {
				cache[7][a + 1][b][c] = true;
				q.push({ 7,a + 1,b,c });
			}

			if (cache[8][a][b + 1][c] == -1) {
				cache[8][a][b + 1][c] = true;
				q.push({ 8,a,b + 1,c });
			}
		}

		if (s == 4) {
			if (cache[1][a + 1][b][c] == -1) {
				cache[1][a + 1][b][c] = true;
				q.push({ 1,a + 1,b,c });
			}

			if (cache[2][a][b + 1][c] == -1) {
				cache[2][a][b + 1][c] = true;
				q.push({ 2,a,b + 1,c });
			}

			if (cache[3][a][b][c + 1] == -1) {
				cache[3][a][b][c + 1] = true;
				q.push({ 3,a,b,c + 1 });
			}

		}

		if (s == 6) {
			if (cache[7][a + 1][b][c] == -1) {
				cache[7][a + 1][b][c] = true;
				q.push({ 7,a + 1,b,c });
			}

			if (cache[8][a][b + 1][c] == -1) {
				cache[8][a][b + 1][c] = true;
				q.push({ 8,a,b + 1,c });
			}
		}

		if (s == 7) {
			if (cache[1][a + 1][b][c] == -1) {
				cache[1][a + 1][b][c] = true;
				q.push({ 1,a + 1,b,c });
			}

			if (cache[2][a][b + 1][c] == -1) {
				cache[2][a][b + 1][c] = true;
				q.push({ 2,a,b + 1,c });
			}

		}

		if (s == 8) {
			if (cache[4][a + 1][b][c] == -1) {
				cache[4][a + 1][b][c] = true;
				q.push({ 4,a + 1,b,c });
			}
		}
	}
}

/*
back:
1:123
2:46
3:78
4:123
5:
6:78
7:12
8:4
9:


tup baselist[7] = {
	{ 1,2,0,0 },
	{ 2,1,1,0 },
	{ 3,1,0,1 },
	{ 4,1,1,0 },
	{ 6,0,1,1 },
	{ 7,1,0,1 },
	{ 8,0,1,1 }
};

string basecase[10] = {
	"XXX",
	"AA", "AB", "AC",
	"BA", "BB", "BC",
	"CA", "CB", "CC",
};

bool backtrack(int s, int a, int b, int c) {
	if (a + b + c < 3) {
		tup here = { s,a,b,c };
		for (int i = 0; i < 6; ++i) {
			if (here == baselist[i]) {
				printf("%c%c", basecase[s][0], basecase[s][1]);
				return true;
			}
		}
		return false;
	}

	if (s == 1) {
		if (backtrack(1, a - 1, b, c)) {
			printf("A");
			return true;
		}
		if (backtrack(4, a - 1, b, c)) {
			printf("A");
			return true;
		}
		if (backtrack(7, a - 1, b, c)) {
			printf("A");
			return true;
		}
		return false;
	}

	if (s == 2) {
		if (backtrack(1, a, b-1, c)) {
			printf("B");
			return true;
		}
		if (backtrack(4, a, b-1, c)) {
			printf("B");
			return true;
		}
		if (backtrack(7, a, b-1, c)) {
			printf("B");
			return true;
		}
		return false;
	}

	if (s == 3) {
		if (backtrack(1, a, b, c-1)) {
			printf("C");
			return true;
		}
		if (backtrack(4, a, b, c-1)) {
			printf("C");
			return true;
		}
		return false;
	}

	if (s == 4) {
		if (backtrack(2, a - 1, b, c)) {
			printf("A");
			return true;
		}
		if (backtrack(8, a - 1, b, c)) {
			printf("A");
			return true;
		}
		return false;
	}

	if (s == 6) {
		if (backtrack(2, a, b, c - 1)) {
			printf("C");
			return true;
		}
		return false;
	}

	if (s == 7) {
		if (backtrack(3, a - 1, b, c)) {
			printf("A");
			return true;
		}
		if (backtrack(6, a - 1, b, c)) {
			printf("A");
			return true;
		}
		return false;
	}

	if (s == 8) {
		if (backtrack(3, a, b - 1, c)) {
			printf("B");
			return true;
		}
		if (backtrack(6, a, b - 1, c)) {
			printf("B");
			return true;
		}
		return false;
	}

	return false;
}

int main() {
	memset(cache, -1, sizeof(cache));

	bfs();

	string s;
	cin >> s;

	int numa, numb, numc;
	numa = numb = numc = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == 'A') ++numa;
		if (s[i] == 'B') ++numb;
		if (s[i] == 'C') ++numc;
	}

	bool chk = false;
	for (int i = 1; i < 10; ++i) {
		if (cache[i][numa][numb][numc] == 1) {
			chk = true;
			backtrack(i, numa, numb, numc);
			break;
		}
	}

	if (!chk) {
		printf("-1\n");
	}

	return 0;
}

*/