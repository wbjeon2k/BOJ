#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Jewel pair<int,int> // size, cost
#define Bag pair<int ,Jewel> // size, jewel
#define pii pair<int,int>// size,index

struct Jcomp {
	bool operator()(pii a, pii b) {
		if (a.second < b.second) {
			return true;
		}
		else if (a.second == b.second && a.first > b.first) {
			return true;
		}
		else return false;
		
	}
};
priority_queue < pii, vector<pii>, Jcomp> pq;
multiset<pii> baglist;
Bag bagarray[300300];

int N, K;

int main() {
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);

		pii tmp;
		tmp.first = a;
		tmp.second = b;

		pq.push(tmp);
	}

	for (int i = 1; i <= K; ++i) {
		int a;
		scanf("%d", &a);
		bagarray[i].first = a;
		baglist.insert({a,i});
	}

	long long ans = 0;

	while (!pq.empty() && !baglist.empty()) {
		pii tmp = pq.top();
		pq.pop();

		int jsize = tmp.first;
		
		multiset<pii>::iterator iter = baglist.lower_bound({ jsize,0 });
		
		if (iter!= baglist.end() && bagarray[(*iter).second].second.second < tmp.second) {
			int idx = (*iter).second;
			ans -= bagarray[idx].second.second;
			ans += tmp.second;
			bagarray[idx].second = tmp;
			baglist.erase(iter);
		}
	}

	printf("%lld", ans);

	return 0;
}

/*
//koosaga's solution. using array instead of priority queue.
#include <cstdio>
#include <set>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

multiset<int> s;

int n,k;
pi x[300005];

bool cmp(pi a, pi b){return a.second > b.second;}


int main(){
	scanf("%d %d",&n,&k);
	for (int i=0; i<n; i++) {
		scanf("%d %d",&x[i].first,&x[i].second);
	}
	for (int i=0; i<k; i++) {
		int t;
		scanf("%d",&t);
		s.insert(t);
	}
	sort(x,x+n,cmp);
	long long res = 0;
	for (int i=0; i<n; i++) {
		multiset<int> ::iterator it = s.lower_bound(x[i].first);
		if(it != s.end()){
			s.erase(it);
			res += x[i].second;
		}
	}
	printf("%lld",res);
}

*/

/*
//my first attempt. TLE. O(NK)
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

struct jewel {
	int w = INT_MAX - 10000, c = 0;
};

struct jcomp {
	bool operator() (jewel a, jewel b) {
		if (a.c < b.c) {
			return true;
		}

		if (a.c == b.c && a.w > b.w) {
			return true;
		}

		return false;
	}
};

struct bag {
	int size;
	jewel j;
};

bool bcomp(bag a, bag b) {
	if (a.size > b.size) {
		return true;
	}

	return false;
}

vector<bag> baglist;
priority_queue<jewel, vector<jewel>, jcomp> pq;

int N, K;

int main()
{
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);

		jewel tmp;
		tmp.c = b;
		tmp.w = a;
		pq.push(tmp);
	}

	for (int i = 0; i < K; ++i) {
		int t = 0;
		scanf("%d", &t);
		bag tmp;
		tmp.size = t;
		baglist.push_back(tmp);
	}

	sort(baglist.begin(), baglist.end(), bcomp);

	long long ans = 0;

	while (!pq.empty()) {
		jewel tmp = pq.top();
		pq.pop();

		for (int i = 0; i < baglist.size(); ++i) {
			if (tmp.c > baglist[i].j.c && tmp.w <= baglist[i].size) {
				ans -= baglist[i].j.c;
				baglist[i].j = tmp;
				ans += baglist[i].j.c;
				break;
			}
		}
	}


printf("%lld\n", ans);

return 0;

}


*/