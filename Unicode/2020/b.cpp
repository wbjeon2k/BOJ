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

string S;

vector<int> oneidx, zeroidx;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> S;

	int zcnt = 0, ocnt = 0;

	for (int i = 0; i < S.length(); ++i) {
		if (S[i] == '0') ++zcnt;
		else ++ocnt;
	}

	int tz, to;
	tz = zcnt, to = ocnt;

	for (int i = 0; i < S.length(); ++i) {
		if (S[i] == '0') {
			--tz;
			if (2 * tz >= zcnt) printf("0");
		}
		else {
			--to;
			if (2 * to < ocnt) printf("1");
		}
	}
	
	return 0;
}