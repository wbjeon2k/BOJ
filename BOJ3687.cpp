//BOJ3687

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> cache[11][111];
int pieces[11] = { 6,2,5,5,4,5,6,3,7,6,0 };

ll digits(ll n) {
	ll ret = 0;

	while (1) {
		n /= 10;
		++ret;
		if (n == 0) break;
	}

	return ret;
}

ll pow10(ll c, ll n) {
	ll ret = c;
	for (int i = 0; i < n; ++i) {
		ret *= 10;
	}

	return ret;
}

bool bigger(vector<int> a, vector<int> b) {
	if (a.size() > b.size()) return true;
	if (a.size() < b.size()) return false;

	if (a.size() == b.size()) {
		int s = a.size();
		for (int i = s - 1; i >= 0; --i) {
			if (a[i] > b[i]) return true;
			if (a[i] < b[i]) return false;
		}
	}
}

vector<int> dp(int c, int n) {
	if (n < 0) {
		return vector<int>(100,9);
	}

	if (n == 0) {
		return vector<int>();
	}

	vector<int>& ret = cache[c][n];
	if (ret.size() != 0) return ret;

	if (n == 1) {
		ret = vector<int>(100,9);
		return ret;
	}


	ret = vector<int>(100,9);
	for (int i = 0; i < 10; ++i) {
		vector<int> tmp = dp(i, n - pieces[c]);
		tmp.push_back(c);
		if (bigger(ret, tmp)) ret = tmp;
	}

	return ret;
}


void printMax(int n) {
	if (n % 2) {
		printf("7");
		n -= 3;
	}
	else {
		printf("1");
		n -= 2;
	}

	while (n != 0) {
		printf("1");
		n -= 2;
	}
	return;
}

void printMini(vector<int>& a) {
	for (int i = a.size() - 1; i >= 0; --i) {
		printf("%d", a[i]);
	}
	return;
}

int main() {

	for (int i = 0; i < 10; ++i) {
		dp(i, 100);
	}

	//ifstream cin;
	//cin.open("input.txt");

	int T;
	cin >> T;

	while (T--) {
		int a;
		cin >> a;
		vector<int> mini = vector<int>(100, 9);
		for (int i = 1; i < 10; ++i) {
			vector<int> tmp = dp(i, a);
			if (bigger(mini, tmp)) mini = tmp;
		}
		printMini(mini);
		printf(" ");
		printMax(a);
		printf("\n");
	}

	


	return 0;
}

/*
//portableangel's solution.
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int d[2][101];

int a[10]={6,2,5,5,4,5,6,3,7,6};

int f(int b, int s) {
	if(s==0) return 0;
	if(d[b][s]>=0) return d[b][s];
	int res=(b?0:100);
	for(int i=0;i<=9;i++) if(a[i]<=s) {
		if(b) res=max(res,f(b,s-a[i])+1);
		else res=min(res,f(b,s-a[i])+1);
	}
	return d[b][s]=res;
}

int main() {
	int t;
	scanf("%d",&t);
	memset(d,-1,sizeof(d));
	while(t--) {
		int n;
		scanf("%d",&n);
		int cur=n; bool z=true;
		while(cur) {
			int mn=100;
			for(int i=(z?1:0);i<=9;i++) if(a[i]<=cur) {
				mn=min(mn,f(0,cur-a[i]));
			}
			for(int i=(z?1:0);i<=9;i++) if(a[i]<=cur) {
				if(f(0,cur-a[i])==mn) {
					printf("%d",i);
					cur-=a[i];
					break;
				}
			}
			z=false;
		}
		printf(" ");
		cur=n; z=true;
		while(cur) {
			int mx=0;
			for(int i=9;i>=(z?1:0);i--) if(a[i]<=cur) {
				mx=max(mx,f(1,cur-a[i]));
			}
			for(int i=9;i>=(z?1:0);i--) if(a[i]<=cur) {
				if(f(1,cur-a[i])==mx) {
					printf("%d",i);
					cur-=a[i];
					break;
				}
			}
			z=false;
		}
		puts("");
	}
}
*/

/*
//jason9319's solution.
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int t,n;
long long dp[102] = { 0,0,1,7,4,2,6,8,10,18,22,20,28,68,88 };
int main()
{
	scanf("%d", &t);
	for (int i = 15; i < 101; i++)
	{
		dp[i] = dp[i - 7] * 10 + dp[7];
		if ((i + 1) % 6 == 0)
		{
			dp[i] = min(dp[i], (long long)pow(10, i / 6) * 2);
		}
	}
	while (t--)
	{
		scanf("%d", &n);
		printf("%lld ", dp[n]);
		int k = n;
		if (k % 2)
		{
			printf("7");
			k -= 3;
		}
		for (int i = 0; i < k / 2; i++)
			printf("1");
		printf("\n");
	}
	return 0;
}
*/

/*
//1st attempt
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll cache[11][111];
int pieces[11] = {6,2,5,5,4,5,6,3,7,6, };

ll digits(ll n) {
	ll ret = 0;

	while (1) {
		n /= 10;
		++ret;
		if (n == 0) break;
	}

	return ret;
}

ll pow10(ll c, ll n) {
	ll ret = c;
	for (int i = 0; i < n; ++i) {
		ret *= 10;
	}

	return ret;
}

bool bigger(vector<int> a, vector<int> b) {

}

ll dp(int c, int n) {
	ll& ret = cache[c][n];
	if (ret != -1) return ret;

	if (n == 0) {
		ret = 0;
		return ret;
	}

	if (n < 0) {
		ret = LLONG_MAX;
		return ret;
	}

	ll mini = LLONG_MAX;
	for (int i = 0; i < 10; ++i) {
		ll tmp = dp(i, n - pieces[i]);
		ll first = digits(tmp);
		if (first == 19) {
			tmp = LLONG_MAX;
		}
		
		if (tmp == 0) {
			tmp += i;
		}
		if (tmp != LLONG_MAX) {
			tmp += pow10(c, first);
		}
		mini = min(mini, tmp);
	}

	ret = mini;
	return ret;
}


void printMax(int n) {
	if (n % 2) {
		printf("7");
		n -= 3;
	}
	else {
		printf("1");
		n -= 2;
	}

	while (n != 0) {
		printf("1");
		n -= 2;
	}
	return;
}

int main() {
	memset(cache, -1, sizeof(cache));

	for (int i = 0; i < 10; ++i) {
		dp(i, 100);
	}

	int T;
	cin >> T;
	while (T--) {
		int a;
		cin >> a;
		ll tmp = LLONG_MAX;
		for (int i = 1; i < 10; ++i) {
			tmp = min(tmp, dp(i, a));
		}
		printf("%lld ", tmp);
		printMax(a);
		printf("\n");
	}


	return 0;
}
*/