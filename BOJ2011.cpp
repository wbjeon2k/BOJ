#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int input[5050];
int dp[5050];
int Mod = 1000000;
int F = 1000000 + 10;
int N;

int calc(int x) {
	int& ret = dp[x];
	if (ret != -1) {
		return ret;
	}
	if (x > N) {
		ret = 0;
		return ret;
	}

	if (input[x] < 10) {
		if (input[x] * 10 + input[x + 1] <= 26 && input[x+1] < 10) {
			ret = (calc(x + 1)% Mod + calc(x + 2)% Mod)%Mod;
		}
		else {
			ret = calc(x + 1) % Mod;
		}
	}
	else {
		ret = calc(x + 1) % Mod;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);

	string s;
	cin >> s;

	bool chk = true;
	int t = 1;
	for (int i = 1; i <= s.size(); ++i) {
		if (s[i - 1] - '0' == 0) {
			if (i >= 2) {
				if (s[i - 2] != '1' && s[i - 2] != '2') {
					chk = false;
				}
				else {
					input[t-1] = input[t-1] * 10;
				}
			}
			else {
				chk = false;
			}
		}
		else {
			input[t] = s[i - 1] - '0';
			++t;
		}
		
	}

	N = t;

	
	if (chk) {
		memset(dp, -1, sizeof(dp));
		dp[N] = 1;
		calc(1);
		printf("%d", dp[1]);
	}
	else {
		printf("0");
	}

	return 0;
}

/* djm03178's solution, sliding window?
#include <stdio.h>

int main(void)
{
	char str[5001];
	int a[5001] = { 0 }, *c, d[5000] = { 0 }, i;
	c = a + 1;
	scanf("%s", str);

	if (str[0] == '0')
	{
		printf("0");
		return 0;
	}

	c[-1] = 1;
	c[0] = 1;

	for (i = 1; str[i] != 0; i++)
	{
		if (str[i - 1] == '1' || (str[i - 1] == '2' && str[i] < '7'))
			c[i] = c[i - 2];
		if (str[i] != '0')
			c[i] += c[i - 1];
		c[i] = c[i] % 1000000;
	}
	printf("%d", c[i - 1]);
}
*/