#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

string input, bomb;
vector<char> s;

int main()
{
    cin >> input >> bomb;

    for (int i = 0; i < input.size(); ++i) {
        bool chk = false;
        s.push_back(input[i]);

        if (s.size() >= bomb.size()) {
            for (int j = 0; j < bomb.size(); ++j) {
                vector<char>::iterator it = s.end() - bomb.size() + j;
                if (*it == bomb[j]) {
                    chk = true;
                }
                else {
                    chk = false;
                    break;
                }
            }
        }
        

        if (chk) {
            for (int j = 0; j < bomb.size(); ++j) {
                s.pop_back();
            }
        }
    }

    if (s.empty()) {
        printf("FRULA");
    }
    else {
        for (int i = 0; i < s.size(); ++i) {
            printf("%c", s[i]);
        }
        printf("\n");
    }
}

/*
//YunGoon's solution.
#include <cstdio>
#include <cstring>

int main()
{
    char a[1000001], b[37];
    scanf("%s %s", a, b);

    int pos = 0, len = strlen(b)-1;
    for (int i = 0; a[i]; ++i)
    {
        a[pos++] = a[i];
        if (a[i] == b[len])
        {
            int j, t = pos-1;

            for (j = len; j >= 0; --j)
                if (t < 0 || a[t] != b[j]) break;
                else t--;

            if (j < 0) pos -= len+1;
        }
    }

    a[pos] = 0;
    puts(pos ? a : "FRULA");
    return 0;
}
*/