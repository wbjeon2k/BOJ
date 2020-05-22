#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int pcache[2502][2502];
int dcache[2502];
string input;
int M = INT_MAX;

int isPalin(int a, int b) {
    int& ret = pcache[a][b];
    if (ret != -1) {
        return ret;
    }

    ret = 0;
    if (a == b) {
        ret = 1;
        return ret;
    }
    if (b == a + 1 && input[a]==input[b]) {
        ret = 1;
        pcache[b][a] = 1;
        return ret;
    }
    if (input[a] == input[b] && isPalin(a + 1, b - 1) == 1) {
        ret = 1;
        pcache[b][a] = 1;
        return ret;
    }

    return ret;
}

int psum(int a) {
    int& ret = dcache[a];
    if (ret != -1) {
        return ret;
    }

    ret = a;
    for (int i = a; i >= 1; --i) {
        if (isPalin(a, i) == 1) {
            ret = min(ret, 1 + psum(i-1));
        }
    }
    
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);

    memset(pcache, -1, sizeof(pcache));
    memset(dcache, -1, sizeof(dcache));


    cin >> input;
    input = "0" + input;
    for (int i = 1; i < input.size() - 1; ++i) {
        for (int j = input.size()-1; j > 0; --j) {
            isPalin(i, j);
        }
    }

    dcache[0] = 0;

    if (input.size() == 1) {
        printf("0");
    }
    else {
        printf("%d", psum(input.size() - 1));
    }
    

    return 0;
}

/*
//koosaga's solution.
//EER tree data structure
//https://medium.com/@alessiopiergiacomi/eertree-or-palindromic-tree-82453e75025b

#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 2550;

namespace eertree{
	int nxt[MAXN][26];
	int par[MAXN], len[MAXN], slink[MAXN], ptr[MAXN], diff[MAXN], series[MAXN], piv;
	void clear(int n = MAXN){
		memset(par, 0, sizeof(int) * n);
		memset(len, 0, sizeof(int) * n);
		memset(slink, 0, sizeof(int) * n);
		memset(nxt, 0, sizeof(int) * 26 * n);
		piv = 0;
	}
	void init(int n, char *a){
		par[0] = 0;
		par[1] = 1;
		a[0] = -1;
		len[0] = -1;
		piv = 1;
		int cur = 1;
		for(int i=1; i<=n; i++){
			while(a[i] != a[i - len[cur] - 1]) cur = slink[cur];
			if(!nxt[cur][a[i]]){
				nxt[cur][a[i]] = ++piv;
				par[piv] = cur;
				len[piv] = len[cur] + 2;
				int lnk = slink[cur];
				while(a[i] != a[i - len[lnk] - 1]){
					lnk = slink[lnk];
				}
				if(nxt[lnk][a[i]]) lnk = nxt[lnk][a[i]];
				if(len[piv] == 1 || lnk == 0) lnk = 1;
				slink[piv] = lnk;
				diff[piv] = len[piv] - len[lnk];
				if(diff[piv] == diff[lnk]) series[piv] = series[lnk];
				else series[piv] = piv;
			}
			cur = nxt[cur][a[i]];
			ptr[i] = cur;
		}
	}
	int query(int s, int e){
		int pos = ptr[e];
		while(len[pos] >= e - s + 1){
			if(len[pos] % diff[pos] == (e - s + 1) % diff[pos] &&
			   len[series[pos]] <= e - s + 1) return true;
			pos = series[pos];
			pos = slink[pos];
		}
		return false;
	}
	vector<pi> minimum_partition(int n){ // (odd min, even min)
		vector<pi> dp(n + 1);
		vector<pi> series_ans(n + 10);
		dp[0] = pi(1e9 + 1, 0);
		for(int i=1; i<=n; i++){
			dp[i] = pi(1e9 + 1, 1e9);
			for(int j=ptr[i]; len[j] > 0;){
				int slv = slink[series[j]];
				series_ans[j] = dp[i - (len[slv] + diff[j])];
				if(diff[j] == diff[slink[j]]){
					series_ans[j].first = min(series_ans[j].first, series_ans[slink[j]].first);
					series_ans[j].second = min(series_ans[j].second, series_ans[slink[j]].second);
				}
				auto val = series_ans[j];
				dp[i].first = min(dp[i].first, val.second + 1);
				dp[i].second = min(dp[i].second, val.first + 1);
				j = slv;
			}
		}
		return dp;
	}
};

int n;
char str[MAXN];

int main(){
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for(int i=1; i<=n; i++) str[i] -= 'a';
	eertree::init(n, str);
	auto ans = eertree::minimum_partition(n)[n];
	cout << min(ans.first, ans.second) << endl;
}


*/

/*
//*dotorya's solution.
//longest palindromic subsequence https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/
#include <algorithm>
#include <ctype.h>
#include <functional>
#include <limits.h>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef pair <char, char> pcc;
typedef pair <int, char> pic;
typedef pair <int, ll> pil;
typedef pair <ll, int> pli;

const int IT_MAX = 32768;
const int MOD = 10000;
const int INF = 2034567891;
const ll LL_INF = 1234567890123456789ll;

char in[2550];
char tmp[5050];
int lps[5050];
int dp[2550];

bool isPalindrome(int s, int e) {
	int m = s + e + 1;
	if (m - lps[m] <= 2 * s) return true;
	else return false;
}
int main() {
	scanf("%s", in);
	int L = 0, i, j;
	for (L = 0; in[L] != 0; L++) tmp[2 * L + 1] = in[L];
	for (i = 0; i <= 2 * L; i += 2) tmp[i] = '$';

	int r = 0, p = 0;
	for (int i = 1; i <= 2*L; i++){
		if (i <= r) lps[i] = min(lps[2 * p - i], r - i);
		else lps[i] = 0;
		while (i > lps[i] && i + lps[i] + 1 <= 2*L && tmp[i - lps[i] - 1] == tmp[i + lps[i] + 1]) lps[i]++;
		if (r < i + lps[i]) r = i + lps[i], p = i;
	}

	for (i = 0; i < L; i++) {
		dp[i] = INF;
		if (isPalindrome(0, i)) dp[i] = 1;
		for (j = 1; j <= i; j++) if (isPalindrome(j, i)) dp[i] = min(dp[i], dp[j - 1] + 1);
	}
	printf("%d", dp[L - 1]);
	return 0;
}
//*/

*/