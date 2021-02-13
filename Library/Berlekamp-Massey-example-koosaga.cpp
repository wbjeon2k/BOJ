//icpc.me/18920
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
using lint = long long;
lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		lint t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, lint n){
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	lint ret = 0;
	for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}
int guess_nth_term(vector<int> x, lint n){
	if(n < x.size()) return x[n];
	vector<int> v = berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v, x, n);
}

int trie[105][26], fail[105], term[105], sz;

int n,k;
int dp[1005][105];

int f(int x, int p){
	if(term[p]) return 0;
    if(x == 0) return 1;
    if(~dp[x][p]) return dp[x][p];
    int ret = 0;
    for (int i=0; i<26; i++) {
        int q = p;
        while (q && !trie[q][i]) {
            q = fail[q];
        }
        q = trie[q][i];
        ret += f(x - 1, q);
        ret %= mod;
    }
    return dp[x][p] = ret;
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        char str[105];
        scanf("%s",str);
        int p = 0;
        for (int j=0; str[j]; j++) {
            if(!trie[p][str[j] - 'a']){
                trie[p][str[j] - 'a'] = ++sz;
            }
            p = trie[p][str[j] - 'a'];
        }
        term[p]++;
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        for (int i=0; i<26; i++) {
            if(trie[qf][i] == 0) continue;
            q.push(trie[qf][i]);
            if(qf == 0){
                fail[trie[qf][i]] = qf;
                continue;
            }
            int p = fail[qf];
            while (p && !trie[p][i]) {
                p = fail[p];
            }
            if(trie[p][i]) p = trie[p][i];
            fail[trie[qf][i]] = p;
            term[trie[qf][i]] += term[p];
        }
    }
    vector<int> v;
    for(int i=0; i<205; i++) v.push_back(f(i, 0));
    printf("%d\n",guess_nth_term(v, k));
}