//BOJ9177

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int T;
string str1, str2, str3;
int cache[444][444];
vector<vector<int>> carrylist;
//dp[a][b]: str1 에서 a 글자, str2 에서 b 글자 써서 str3의 a+b 글자 만들 수 있는가?
bool dp(int a, int b) {
	//printf("%d %d\n", a, b);

	int& ret = cache[a][b];
	if (ret != -1) return ret;

	if (a == str1.size() && b == str2.size()) {
		ret = true;
		return ret;
	}

	if (a > str1.size() || b > str2.size()) {
		ret = false;
		return ret;
	}

	ret = false;

	if (a < str1.size() && str1[a] == str3[a + b]) ret |= dp(a + 1, b);
	if (b < str2.size() && str2[b] == str3[a + b]) ret |= dp(a, b + 1);

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	int cnt = 1;
	while (T--) {
		memset(cache, -1, sizeof(cache));
		cin >> str1 >> str2 >> str3;

		if (str1.size() + str2.size() != str3.size()) {
			printf("Data set %d: no\n", cnt);
		}
		else {
			bool chk = dp(0, 0);

			if(!chk) printf("Data set %d: no\n", cnt);
			else printf("Data set %d: yes\n", cnt);
		}
		++cnt;
	}


	return 0;
}

/*
//wlgns359's code. without dp?

#include <iostream>
#include <string>
#include <time.h>

using namespace std;
string A, B, C;

bool stringCheck(int indexA, int indexB, int indexC) {
	if (indexC < 0) // completed
		return true;

	if (indexA >= 0 &&C[indexC] == A[indexA]) {
		if (stringCheck(indexA - 1, indexB , indexC - 1))
			return true;
	}

	if (indexB >= 0 && C[indexC] == B[indexB] ) {
		if (stringCheck(indexA, indexB - 1, indexC - 1))
			return true;
	}

	return false;
}

int main() {
//	clock_t startTime, endTime;
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> A >> B >> C;
		//startTime = clock();
		bool result = stringCheck(A.length() - 1, B.length() - 1, C.length() - 1);
		//endTime = clock();

		cout << "Data set " << i << ": " << (result ? "yes\n" : "no\n");
		//cout << endTime - startTime << ' ' << "\nresult : " << (result ? "Yes" : "No") << '\n';
	}
	return 0;
}

*/

/*
//first trial. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int T;
string str1, str2, str3;
int cache[444][444];
vector<vector<int>> carrylist;
//dp[a][b]: str3의 a 번째 글자를 str1의 b 번째 글자로 선택했을때 str1 완성 가능?
bool dp(int a, int b, vector<int> carry) {
	//printf("%d %d\n", a, b);

	int& ret = cache[a][b];
	if (ret != -1) return ret;

	if (b == str1.size() - 1) {
		carrylist.push_back(carry);
		ret = true;
		return ret;
	}

	ret = false;
	for (int i = a + 1; i < str3.size(); ++i) {
		if (str3[i] == str1[b + 1]) {
			vector<int> tmp = carry;
			tmp.push_back(i);
			ret = (dp(i, b + 1, tmp) || ret);
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream cin;
	cin.open("input.txt");

	cin >> T;
	int cnt = 1;
	while (T--) {
		memset(cache, -1, sizeof(cache));
		cin >> str1 >> str2 >> str3;

		if (str1.size() + str2.size() != str3.size()) {
			printf("Data set %d: no\n", cnt);
		}
		else {
			for (int i = 0; i < str3.size() ; ++i) {
				if (str3[i] == str1[0]) {
					vector<int> tmp;
					tmp.push_back(i);
					dp(i, 0, tmp);
				}
			}

			bool chk = false;
			for (int i = 0; i < carrylist.size(); ++i) {
				string tmp;
				int idx = 0;
				for (int j = 0; j < str3.size(); ++j) {
					if (idx < str1.size() && j == carrylist[i][idx] ) {
						++idx;
					}
					else {
						tmp += str3[j];
					}
				}
				if (tmp == str2) {
					chk = true;
					break;
				}
			}

			if(!chk) printf("Data set %d: no\n", cnt);
			else printf("Data set %d: yes\n", cnt);
		}
	}


	return 0;
}
*/