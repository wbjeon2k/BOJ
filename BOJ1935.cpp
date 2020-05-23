#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int N;
int operand[30];
stack<double> s;

int main()
{
    scanf("%d", &N);
    string input;
    cin >> input;

    for (int i = 0; i < N; ++i) {
        scanf("%d", &operand[i]);
    }

    double ans = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            s.push(operand[input[i] - 'A']);
        }
        else {
            double b = s.top();
            s.pop();
            double a = s.top();
            s.pop();
            if (input[i] == '+') {
                s.push(a + b);
            }
            else if (input[i] == '-') {
                s.push(a - b);
            }
            else if (input[i] == '*') {
                s.push(a * b);
            }
            else if (input[i] == '/') {
                s.push(a / b);
            }
        }
    }

    ans = s.top();

    printf("%.2f", ans);

    return 0;
}
