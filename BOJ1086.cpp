//BOJ1086

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> input;
int pow10modK[800], inputmodK[20], slength[20];
ll cache[1 << 15][100];

int N, K;

void dp() {
	//점화식: 나머지 n인 수를 status로 만들 수 있는 경우의 수

	cache[0][0] = 1;
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < K; ++j) {
			for (int k = 0; k < N; ++k) {
				if ((i & (1 << k)) == 0) {
					//ab + cd = (ab*100 + cd)modK
					int rem = (j * pow10modK[slength[k]] + inputmodK[k]) % K;
					int nextidx = i;
					nextidx |= (1 << k);
					cache[nextidx][rem] += cache[i][j];
				}
			}
		}
	}
	
}

ll gcd(ll a, ll b) {
	if (b > a) swap(a, b);
	
	while (a != 0 && b != 0) {
		ll q, r;
		q = (a / b);
		r = a - b * q;
		a = b;
		b = r;
	}

	if (a == 0) return b;
	else if (b == 0) return a;
}

int main() {
	memset(cache, 0, sizeof(cache));

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N;

	for (int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		slength[i] = s.size();
		input.push_back(s);
	}
	cin >> K;

	pow10modK[0] = 1;
	for (int i = 1; i < 800; ++i) {
		pow10modK[i] = (pow10modK[i - 1] * 10) % K;
		//10^n 승의 modK를 미리 계산
	}

	for (int i = 0; i < N; ++i) {
		int t = input[i].length();
		int mod = 0;
		for (int j = 0; j < t; ++j) {
			int digit = input[i][t - j - 1] - '0';
			mod += digit * pow10modK[j];
			mod %= K;
		}
		inputmodK[i] = mod;
		//input 수들의 modK를 미리 계산
	}

	dp();
	int status = (1 << N) - 1;
	ll ans = cache[status][0];

	ll factN = 1;
	for (int i = 1; i <= N; ++i) factN *= i;

	ll g = gcd(factN, ans);
	printf("%lld/%lld", ans/g, factN/g);
	//기약분수 출력
	

	return 0;
}

/*
//2nd attempt: fail
//BOJ1086

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> input;
int pow10modK[800], inputmodK[20], slength[20];
ll cache[16][1 << 15];

int N, K;

ll dp(int n, int status, int carry, int lengthcarry) {
	//점화식: N modK==0 인 N을 input[n]을 맨 끝에 붙여서 만들 수 있는 경우의 수

	ll& ret = cache[n][status];

	if (ret != -1) return ret;

	carry *= pow10modK[slength[n]];
	carry += inputmodK[n];
	carry %= K;
	lengthcarry += slength[n];
	status &= ~(1 << n);

	if (status == 0) {

		// 나머지의 합이 0인지 아닌지 확인
		//printf("n%d s%d c%d l%d\n", n, status, carry, lengthcarry);
		if (carry % K == 0) return 1;
		else return 0;
	}

	ret = 0;
	for (int i = 14; i >= 0; --i) {
		if (status & (1 << i)) {
			ret += dp(i, status, carry, lengthcarry);
		}
	}

	return ret;
}

ll gcd(ll a, ll b) {
	if (b > a) swap(a, b);

	while (a != 0 && b != 0) {
		ll q, r;
		q = (a / b);
		r = a - b * q;
		a = b;
		b = r;
	}

	if (a == 0) return b;
	else if (b == 0) return a;
}

int main() {
	memset(cache, -1, sizeof(cache));

	ifstream cin;
	cin.open("input.txt");

	cin >> N;
	int ntot = 0;
	for (int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		slength[i] = s.size();
		input.push_back(s);
	}
	cin >> K;

	pow10modK[0] = 1;
	for (int i = 1; i < 800; ++i) {
		pow10modK[i] = (pow10modK[i - 1] * 10) % K;
		//10^n 승의 modK를 미리 계산
	}

	for (int i = 0; i < N; ++i) {
		int t = input[i].length();
		int mod = 0;
		for (int j = 0; j < t; ++j) {
			int digit = input[i][t - j - 1] - '0';
			mod += digit * pow10modK[j];
			mod %= K;
		}
		inputmodK[i] = mod;
		//input 수들의 modK를 미리 계산
	}

	int starting = (1 << N) - 1;
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		memset(cache, -1, sizeof(cache));
		ans += dp(i, starting, 0, 0);
	}
	//점화식: N modK==0 인 N을 n 자리로 만들 수 있는 경우의 수
	//ntot: 모든 정수들의 자리 합
	ll factN = 1;
	for (int i = 1; i <= N; ++i) factN *= i;

	ll g = gcd(factN, ans);
	printf("%lld/%lld", ans, factN);
	//기약분수 출력


	return 0;
}
*/

/*
//1st attempt. MLE
//BOJ1086

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> input;
int pow10modK[800], inputmodK[20], slength[20];
ll cache[800][1 << 15];

int N, K;

ll dp(int n, int status, int carry) {
	//점화식: N modK==0 인 N을 n 자리로 만들 수 있는 경우의 수
	ll& ret = cache[n][status];

	if (ret != -1) return ret;

	if (n == 0) {
		// 나머지의 합이 0인지 아닌지 확인
		if (carry % K == 0) return 1;
		else return 0;
	}

	ret = 0;
	for (int i = 14; i >= 0; --i) {
		int newstat = status;
		if (newstat & (1 << i)) {
			newstat &= ~(1 << i);
			int newcarry = carry + inputmodK[i] * pow10modK[n - slength[i]];
			ret += dp(n - slength[i], newstat, newcarry);
			//i 번째 수를 사용한다면
			//i 번째 수의 길이만큼을 뺀것이 n - slength[i]
		}
	}

	return ret;
}

ll gcd(ll a, ll b) {
	if (b > a) swap(a, b);

	while (a != 0 && b != 0) {
		ll q, r;
		q = (a / b);
		r = a - b * q;
		a = b;
		b = r;
	}

	if (a == 0) return b;
	else if (b == 0) return a;
}

int main() {
	memset(cache, -1, sizeof(cache));

	cin >> N;
	int ntot = 0;
	for (int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		slength[i] = s.size();
		ntot += s.size();
		input.push_back(s);
	}
	cin >> K;

	pow10modK[0] = 1;
	for (int i = 1; i < 800; ++i) {
		pow10modK[i] = (pow10modK[i - 1] * 10) % K;
		//10^n 승의 modK를 미리 계산
	}

	for (int i = 0; i < N; ++i) {
		int t = input[i].size();
		int mod = 0;
		for (int j = 0; j < t; ++j) {
			int digit = input[i][t - j - 1] - '0';
			mod += digit * pow10modK[j];
			mod %= K;
		}
		inputmodK[i] = mod;
		//input 수들의 modK를 미리 계산
	}

	int starting = (1 << N) - 1;
	ll ans = dp(ntot, starting, 0);
	//점화식: N modK==0 인 N을 n 자리로 만들 수 있는 경우의 수
	//ntot: 모든 정수들의 자리 합
	ll factN = 1;
	for (int i = 1; i <= N; ++i) factN *= i;

	ll g = gcd(factN, ans);
	printf("%lld/%lld", ans/g, factN/g);
	//기약분수 출력


	return 0;
}

*/