#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int>> minHeap;

int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		int t;
		scanf("%d", &t);
		minHeap.push(t);
	}

	int ans = 0;
	while (minHeap.size() > 1) {
		int a, b;
		a = minHeap.top();
		minHeap.pop();
		b = minHeap.top();
		minHeap.pop();

		ans += a + b;
		minHeap.push(a + b);
	}

	

	printf("%d", ans);

	return 0;

}
