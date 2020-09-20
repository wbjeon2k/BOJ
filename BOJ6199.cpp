//BOJ 6199

#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;

int N, maxi;

int dx[4] = { -1,1,1,-1 };
int dy[4] = { 1,-1,1,-1 };

vector<string> field(111);

bool isInside(const int& x, const int& y) {
	if (x<1 || x>N || y<1 || y>N) return false;
	return true;
}

int findsize(int& x, int& y, int& i, int& j, char start) {
	
	int jcnt = 0, bcnt = 0;

	if (field[x + i][y + j] == 'J') ++jcnt;
	if (field[x - j][y + i] == 'J') ++jcnt;
	if (field[x + i - j][y + i + j] == 'J') ++jcnt;


	if (field[x + i][y + j] == 'B') ++bcnt;
	if (field[x - j][y + i] == 'B') ++bcnt;
	if (field[x + i - j][y + i + j] == 'B') ++bcnt;

	if (bcnt) return 0;

	if (start == '*' && jcnt == 3) return (i * i + j * j);

	if (start == 'J' && jcnt == 3) return (i * i + j * j);
	if (start == 'J' && jcnt == 2) return (i * i + j * j);

	return 0;
}

void solve() {
	maxi = 0;

	for (int x = 1; x <= N; ++x) {
		for (int y = 1; y <= N; ++y) {

			if (field[x][y] == 'B') continue;

			for (int a = N; a >= 0; --a) {
				for (int b = N; b >= 0; --b) {

					int i = a, j = b;

					if (!isInside(x + i, y + j)) continue;
					if (!isInside(x - j, y + i)) continue;
					if (!isInside(x + i - j, y + i + j)) continue;
					if ((i * i + j * j) <= maxi) continue;

					maxi = max(maxi, findsize(x, y, i, j, field[x][y]));
				}
			}

		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		s = 'A' + s;
		field[i] = s;
	}

	solve();

	printf("%d\n", maxi);

	return 0;
}

/*
//Acka's solution.

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, ans, sq[10001], l1[7954], l2[7954], r[10000], c[10000], pcnt, ccnt;
char map[100][101];

int main()
{
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%s", map[i]);
		for(int j = 0; j < N; j++)
			if(map[i][j] == 'J'){
				r[ccnt] = i; c[ccnt++] = j;
			}
	}

	memset(sq, 0xff, sizeof(sq));
	for(int i = 0; i <= N; i++)
		sq[i * i] = i;

	int ans = 0;
	for(int sum = N * N; sum > 0; sum--){
		for(int l = 0; l * l <= sum; l++)
			if(sq[sum - l * l] >= 0){
				l1[pcnt] = l; l2[pcnt++] = sq[sum - l * l];
			}
	}

	int r1, r2, r3, c1, c2, c3;
	for(int pi = 0; !ans && pi < pcnt; pi++){
		int dr = l1[pi], dc = l2[pi];
		for(int ci = 0; ci < ccnt; ci++){
			r1 = r[ci] - dr, c1 = c[ci] - dc;
			if(r1 < 0 || c1 < 0) continue;
			if(c[ci] + dr < N && r[ci] >= dr + dc){
				r2 = r1 - dc, c2 = c1 + dr;
				r3 = r2 + dr, c3 = c2 + dc;
				if(map[r1][c1] != 'B' && map[r2][c2] != 'B' && map[r3][c3] != 'B')
					if((map[r1][c1] != 'J') + (map[r2][c2] != 'J') + (map[r3][c3] != 'J') <= 1){
						ans = dr * dr + dc * dc;
						break;
					}
			}
			if(c[ci] >= dr + dc && r[ci] + dc < N){
				r2 = r1 + dc, c2 = c1 - dr;
				r3 = r2 + dr, c3 = c2 + dc;
				if(map[r1][c1] != 'B' && map[r2][c2] != 'B' && map[r3][c3] != 'B')
					if((map[r1][c1] != 'J') + (map[r2][c2] != 'J') + (map[r3][c3] != 'J') <= 1){
						ans = dr * dr + dc * dc;
						break;
					}
			}

		}
	}

	printf("%d\n", ans);

	return 0;
}
*/