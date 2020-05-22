#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

string input;

bool isOper(char a) {
    return (a == '+' || a == '-' || a == '*' || a == '/');
}

int Prec(char a) {
    if (a == '*' || a == '/') {
        return 2;
    }
    
    if (a == '+' || a == '-') {
        return 1;
    }

    else return 0;
}

string process(string input) {
    stack<char> s;
    int l = input.size();
    s.push('X');

    string ans = "";

    for (int i = 0; i < l; ++i) {
        if (isOper(input[i])) {
            while (s.top() != 'X' && Prec(s.top()) >= Prec(input[i])) {
                char c = s.top();
                ans += c;
                s.pop();
            }
            s.push(input[i]);
        }
        else if (input[i] == '(') {
            s.push(input[i]);
        }
        else if (input[i] == ')') {
            while (s.top() != 'X' && s.top() != '(') {
                char c = s.top();
                ans += c;
                s.pop();
            }
            if (s.top() == '(') {
                s.pop();
            }
        }
        else {
            ans += input[i];
        }
    }

    while (s.top() != 'X') {
        ans += s.top();
        s.pop();
    }

    return ans;
}

int main()
{
    cin >> input;

    string ans = process(input);
    cout << ans;
    return 0;
}
