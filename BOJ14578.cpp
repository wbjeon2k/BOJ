// BOJ14578
// derangement

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100
#define Mod 1000000007
#define ll long long

ll derange[Msize], facto[Msize];
int N;

int main() {
	derange[1] = 0;
	derange[2] = 1;
	for (ll i = 3; i < 100100; ++i) {
		derange[i] = (i - 1) * ((derange[i - 1] + derange[i - 2]) % Mod) % Mod;
	}

	facto[1] = 1;
	facto[2] = 2;
	for (ll i = 3; i < 100100; ++i) facto[i] = (i * facto[i - 1]) % Mod;

	cin >> N;
	printf("%lld\n", (facto[N] * derange[N]) % Mod);

	return 0;
}