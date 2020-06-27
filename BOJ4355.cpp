//BOJ4355

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

bitset<1001000> numbers;
vector<int> primeList;
ll T, N;

void sieve() {
	numbers.set(false);
	for (int i = 2; i < 1000010; ++i) {
		if (numbers[i] == false) {
			numbers[i] = true;
			primeList.push_back(i);

			for (int j = 2 * i; j < 1000010; j += i) numbers[j] = true;
		}
	}
}

ll eulerPhi(ll n) {
	int primeidx = 0;
	ll prime, ans;

	prime = primeList[primeidx];
	ans = n;

	while (prime * prime <= n) {
		if (n % prime == 0) ans -= (ans / prime);
		while (n % prime == 0) n /= prime;
		++primeidx;
		prime = primeList[primeidx];
	}

	if (n != 1) ans -= (ans / n);

	return ans;
}

int main() {
	sieve();
	
	while (1) {
		cin >> T;
		if (T == 0) break;
		printf("%lld\n", eulerPhi(T));
	}

	return 0;
}