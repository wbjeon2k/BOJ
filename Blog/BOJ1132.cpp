// BOJ 1132

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,ll>

int N;
vector<string> slist;
ll cnt[13][30], numberlist[30];
//i 번쨰 자리 j 번째 알파벳 개수
bool headchk[11];
//headchk: 맨 앞자리가 0이 될 수 없기 때문에 맨 앞에 오는 알파벳들 확인.

string agenerator(int n) {
	string ret = "";
	for (int i = 0; i < n; ++i) {
		ret += "a";
	}
	return ret;
}

int main() {
	cin >> N;
	memset(headchk, 0, sizeof(headchk));

	//12자리로 전부 맞춘다.
	for (int i = 0; i < N; ++i) {
		string s, t;
		cin >> s;
		headchk[s[0] - 'A'] = true;
		t = agenerator(12 - s.size());
		slist.push_back(t + s);
	}

	//문자열 순서대로 정렬.
	sort(slist.begin(), slist.end());

	memset(cnt, 0, sizeof(cnt));
	memset(numberlist, 0, sizeof(numberlist));
	

	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < N; ++j) {
			if (slist[j][i] == 'a') continue;
			++cnt[i][slist[j][i] - 'A'];
		}
	}

	//각 알파벳별로 가중치 구한다.
	vector<pll> anslist;
	for (int i = 0; i < 11; ++i) {
		ll tmp = 0;
		ll pow10 = 1;
		for (int j = 11; j >= 0; --j) {
			tmp += (cnt[j][i])*pow10;
			pow10 *= 10;
		}
		if (tmp == 0) continue;
		anslist.push_back({ tmp,i });
	}

	sort(anslist.begin(), anslist.end());

	int zidx = 100, minval, minidx;

	if (headchk[anslist[0].second] && anslist.size() == 10) {
		//10가지 알파벳이 모두 쓰이는 경우 아니면 맨 앞자리 0인지 확인 할 필요 없음.
		for (int i = 0; i < 10; ++i) {
			if (headchk[anslist[i].second]) continue;
			zidx = i;
			break;
		}
	}

	int idx = 9;
	for (int i = anslist.size() - 1; i >= 0; --i) {
		//가중치 큰 순서대로 큰 숫자 부여.
		if (i == zidx) {
			numberlist[anslist[i].second] = 0;
			continue;
		}
		numberlist[anslist[i].second] = idx;
		--idx;
	}

	
	long long ans = 0;
	long long pow10 = 1;
	for (int i = 11; i >= 0; --i) {
		for (int j = 0; j < N; ++j) {
			if (slist[j][i] == 'a') continue;
			ans += numberlist[slist[j][i] - 'A']*pow10;
		}
		pow10 *= 10;
	}

	printf("%lld\n", ans);

	return 0;
}