#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

stack<int> stack1, stack2;
int input[100100];

string calc(int q) {
	string ret = "";

	if (stack1.empty()) {
		return "err";
	}

	if (q > stack1.top()) {
		if (stack2.empty() || q < stack2.top()) {
			return "err";
		}
		else {
			while (!stack2.empty() && q >= stack2.top() ) {
				stack1.push(stack2.top());
				stack2.pop();
				ret += "+";
			}
			if (stack1.empty() || stack1.top() != q) {
				return "err";
			}
			else {
				stack1.pop();
				ret += "-";
			}
		}
	}
	else if (q == stack1.top()) {
		stack1.pop();
		ret += "-";
	}
	else {
		while (!stack1.empty() && stack1.top() > q) {
			stack1.pop();
			ret += "-";
		}
		if (stack1.empty() || stack1.top() != q) {
			return "err";
		}
		else {
			stack1.pop();
			ret += "-";
		}
	}

	return ret;
}

int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &input[i]);
	}

	for (int i = N; i >0; --i) {
		stack2.push(i);
	}

	stack1.push(0);

	string ans = "";
	for (int i = 0; i < N; ++i) {
		string tmp = calc(input[i]);
		//cout << tmp << endl;
		if (tmp == "err") {
			ans = tmp;
			break;
		}
		else {
			ans += tmp;
		}
	}

	if (ans == "err") {
		printf("NO");
	}
	else {
		for (int i = 0; i < ans.size(); ++i) {
			printf("%c\n", ans[i]);
		}
	}

	return 0;


}


/*
//wookje's solution
#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;

int n, a[100001];
stack<int> stk;
vector<char> ans;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);

	int pos = 0;
	for (int i = 1; i <= n; i++) {
		stk.push(i), ans.push_back('+');
		while (!stk.empty() && stk.top() == a[pos]) {
			pos++, stk.pop(), ans.push_back('-');
		}
	}

	if (!stk.empty()) puts("NO");
	else for (auto it : ans) printf("%c\n", it);

	return 0;
}



*/