#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;

bitset<4004000> sieve;
vector<int> primeList;

void gensieve() {
	sieve.set();
	//sieve[1] = 0;
	//primeList.push_back(1);
	
	for (int i = 2; i <= 4000000; ++i) {
		if (sieve[i]) {
			primeList.push_back(i);
			for (int j = 2 * i; j <= 4000000; j += i) sieve[j] = 0;
		}
	}

}

int main() {
	

	//ifstream cin;
	//cin.open("input.txt");

	gensieve();

	cin >> N;

	int s = 0, e = 0, psum = 0, cnt = 0;

	while (1) {
		if (psum >= N) {
			psum -= primeList[s];
			++s;
		}
		else if (e == primeList.size()) break;
		else if (psum < N) {
			psum += primeList[e];
			++e;
		}

		if (psum == N) ++cnt;
	}

	printf("%d\n", cnt);

	return 0;
}