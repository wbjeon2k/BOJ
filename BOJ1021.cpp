#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct cirq {
	int num;
	vector<int> q;
};

cirq mode2(int a, cirq cq) {
	cirq ans;
	vector<int>q = cq.q;
	int cnt = 0;
	while (q.front() != a) {
		int t = q.front();
		q.erase(q.begin());
		q.push_back(t);
		++cnt;
	}
	q.erase(q.begin());
	ans.num = cnt;
	ans.q = q;
	return ans;
}

cirq mode3(int a, cirq cq) {
	cirq ans;
	vector<int>q = cq.q;
	int cnt = 0;
	while (q.front() != a) {
		int t = q.back();
		q.pop_back();
		q.insert(q.begin(), t);
		++cnt;
	}
	q.erase(q.begin());
	ans.num = cnt;
	ans.q = q;
	return ans;
}


cirq calc(int a, cirq cq) {
	cirq ans;
	if (cq.q.front() == a) {
		ans = cq;
		ans.num = 0;
		ans.q.erase(ans.q.begin());
	}
	else {
		cirq m2 = mode2(a, cq);
		cirq m3 = mode3(a, cq);
		
		if (m2.num > m3.num) {
			ans = m3;
		}
		else {
			ans = m2;
		}
	}

	return ans;
}


int main() {	
	int N, M;
	scanf("%d %d", &N, &M);

	int input[100];
	for (int i = 0; i < M; ++i) {
		scanf("%d", &input[i]);
	}

	vector<int>inputq;
	for (int i = 1; i <= N; ++i) {
		inputq.push_back(i);
	}

	cirq init;
	init.num = 0;
	init.q = inputq;

	int ans = 0;
	for (int i = 0; i < M; ++i) {
		cirq t1 = calc(input[i], init);
		ans += t1.num;
		init.num = t1.num;
		init.q= t1.q;
	}

	printf("%d", ans);
	

	return 0;
}