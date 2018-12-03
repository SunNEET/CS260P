#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <fstream>

using namespace std;

string inputMode;
std::ifstream infile("input");

string binstring(int x, int n)
{
    string res = "";
    for (int i = 0; i < n; i++)
        res += "0";
    int cnt = 0;
    while (x)
    {
        res[n - 1 - cnt++] = (x & 1) + '0';
        x >>= 1;
    }
    return res;
}

void CountLCS(const string &X, const string &Y, int n, int m, int len, unordered_set<string> &res, string &str, const vector<vector<int>> &L)
{
    if (len == 0)
    {
        res.insert(str);
        return;
    }
    if (n == 0 || m == 0)
        return;
    int i = n, j = m;
    if (!L[i][j] && !L[i - 1][j] && !L[i][j - 1] && !L[i - 1][j - 1])
        return;
    if (X[i - 1] == Y[j - 1])
    {
        CountLCS(X, Y, i - 1, j - 1, len, res, str, L);
        str[len - 1] = X[i - 1];
        CountLCS(X, Y, i - 1, j - 1, len - 1, res, str, L);
    }
    else
    {
        if (L[i - 1][j] >= L[i][j - 1])
            CountLCS(X, Y, i - 1, j, len, res, str, L);
        if (L[i][j - 1] >= L[i - 1][j])
            CountLCS(X, Y, i, j - 1, len, res, str, L);
    }
}

vector<vector<int>> LCSTable(string X, string Y, int n)
{
    vector<vector<int>> L(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    return L;
}

int main()
{
    int n, x, y;
    int inputMode;
    string keepAlive = "Y";
    int maxCount = 0;

    printf("Enter mode for input (1:manual|2:file): ");
    scanf(" %d", &inputMode);

    // freopen("input", "r", stdin);
    while ((inputMode == 2 && infile >> n >> x >> y) || (inputMode == 1 && keepAlive == "Y"))
    {
        printf("----- Program Start -----\n");

        keepAlive = "N";

        printf("Enter value of n in range [3:20] : ");
        if (inputMode == 1)
            scanf(" %d", &n);
        if (n < 3 || n > 20)
        {
            printf("Invalid input n (%d)\n", n);
            printf("----- Program End   -----\n");
            continue;
            // return 0;
        }
        if (inputMode == 2)
            printf("%d\n", n);

        int M = (int)pow(2, n) - 1;

        printf("Enter value of x in range [0:%d] : ", M);
        if (inputMode == 1)
            scanf(" %d", &x);
        if (x > M)
        {
            printf("Invalid input x (%d)\n", x);
            printf("----- Program End   -----\n");
            continue;
            // return 0;
        }
        if (inputMode == 2)
            printf("%d\n", x);

        printf("Enter value of y in range [0:%d] : ", (int)pow(2, n) - 1);
        if (inputMode == 1)
            scanf(" %d", &y);
        if (y > M)
        {
            printf("Invalid input y (%d)\n", y);
            printf("----- Program End   -----\n");
            continue;
            // return 0;
        }
        if (inputMode == 2)
            printf("%d\n", y);

        int ans_x = 0, ans_y = 0, maxCnt = 0;

        string sx = binstring(x, n);
        string sy = binstring(y, n);
        unordered_set<string> res;
        string str = "";
        auto lcsTable = LCSTable(sx, sy, n);
        int len = lcsTable[n][n];

        for (int i = 0; i < len; i++)
            str += " ";
        CountLCS(sx, sy, n, n, len, res, str, lcsTable);

        printf("** STRINGLEN %d: %lu length-%d LCS's", n, res.size(), len);
        printf("from X=(%d)=%s and Y=(%d)=%s\n", x, sx.c_str(), y, sy.c_str());

        // if (res.size() > maxCnt) {
        //     maxCnt = (int)res.size();
        //     ans_x = x;
        //     ans_y = y;
        // }

        int formatCount = 1;
        for (auto e : res)
        {
            printf("LCS %2d: %s\t", formatCount, e.c_str());
            if (++formatCount % 3 == 1)
                printf("\n");
        }

        if (formatCount % 3 != 1)
            printf("\n");

        printf("----- Program End   -----\n");
        if (inputMode == 1)
        {
            char in;
            printf("Continue? (Y/N): ");
            cin >> in;
            keepAlive = string(1, toupper(in));
        }
    }

    return 0;
}