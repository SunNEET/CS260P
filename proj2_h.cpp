/* Dynamic Programming implementation of LCS problem */
#include <iostream>
#include <set>
#include <cmath>
#include <cstring>

using namespace std;

// Maximum string length
#define N 100

int L[N][N];

string binstring(const int n, int x)
{
    string res = "";

    for (int i = 0; i < n; i++)
        res += "0";
    int count = 0;
    while (x)
    {
        res[n - 1 - count] = (x & 1) + '0';
        x >>= 1;
        count++;
    }
    return res;
}

/* Returns set containing all LCS for X[0..m-1], Y[0..n-1] */
set<string> findLCS(string X, string Y, int m, int n)
{
    // construct a set to store possible LCS
    set<string> s;

    // If we reaches end of either string, return
    // a empty set
    if (m == 0 || n == 0)
    {
        s.insert("");
        return s;
    }

    // If the last characters of X and Y are same
    if (X[m - 1] == Y[n - 1])
    {
        // recurse for X[0..m-2] and Y[0..n-2] in
        // the matrix
        set<string> tmp = findLCS(X, Y, m - 1, n - 1);

        // append current character to all possible LCS
        // of substring X[0..m-2] and Y[0..n-2].
        for (auto str : tmp)
            s.insert(str + X[m - 1]);
    }

    // If the last characters of X and Y are not same
    else
    {
        // If LCS can be constructed from top side of
        // the matrix, recurse for X[0..m-2] and Y[0..n-1]
        if (L[m - 1][n] >= L[m][n - 1])
            s = findLCS(X, Y, m - 1, n);

        // If LCS can be constructed from left side of
        // the matrix, recurse for X[0..m-1] and Y[0..n-2]
        if (L[m][n - 1] >= L[m - 1][n])
        {
            set<string> tmp = findLCS(X, Y, m, n - 1);

            // merge two sets if L[m-1][n] == L[m][n-1]
            // Note s will be empty if L[m-1][n] != L[m][n-1]
            s.insert(tmp.begin(), tmp.end());
        }
    }
    return s;
}

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int LCS(string X, string Y, int m, int n)
{
    // Build L[m+1][n+1] in bottom up fashion
    for (int i = 0; i <= m; i++)
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
    return L[m][n];
}

/* Driver program to test above function */
int main()
{
    int n, x, y, m;
    
    /* Input */    
    freopen("input", "r", stdin);

    printf("Enter value of n in range [3:20]: ");
    scanf(" %d", &n);
    printf("%d\n", n);
    m = (int)pow(2, n) - 1;
    printf("x and y in range [0:%d]\n", m);

    /* // NORMAL PROCEDURE
    printf("Enter value of x in range [0:%d]: ", m);
    scanf(" %d", &x);
    printf("%d\n", x);
    printf("Enter value of y in range [0:%d]: ", m);
    scanf(" %d", &y);
    printf("%d\n", y);

    string sx = binstring(n, x);
    string sy = binstring(n, y);
    printf("x in binary string: %s\n", sx.c_str());
    printf("y in binary string: %s\n", sy.c_str()); */

    /* Automation For Fixed n */
    // freopen("output", "a", stdout);
    int maxCount = 0;
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= m; j++){
            printf("x: %d, y : %d\n", i, j);
            string sx = binstring(n, i);
            string sy = binstring(n, j);
            LCS(sx, sy, n, n);
            set<string> s = findLCS(sx, sy, n, n);
            if(s.size() > maxCount) maxCount = s.size();
            // for (string str : s){
            //     cout << i << " " << j << " " << length << " " << str << endl;
            // }
        }
    }

    // /* Ouput: FILE */
    // freopen("output", "a", stdout);
    // cout << "MAX LCS length is " << LCS(sx, sy, n, n) << endl;

    /* set<string> s = findLCS(sx, sy, n, n);
    for (string str : s)
        cout << str << endl; */

    /* Output: Console */
    // freopen ("/dev/tty", "a", stdout);
    // cout << "End of writing" << endl;
    cout << "Max Count for n = " << n << ": " << maxCount << endl;

    return 0;
}

// #include <iostream>
// #include <cstring>
// #include <cmath>

// using namespace std;

// string binstring(const int n, int x)
// {
//     string res = "";

//     for (int i = 0; i < n; i++)
//         res += "0";
//     int count = 0;
//     while (x)
//     {
//         res[n - 1 - count] = (x & 1) + '0';
//         x >>= 1;
//         count++;
//     }
//     return res;
// }

// int main(int argc, char const *argv[])
// {
//     int n, x, y;
//     printf("Enter value of n in range [3:20]: ");
//     scanf(" %d", &n);
//     printf("Enter value of x in range [0:%d]: ", (int)pow(2, n - 1));
//     scanf(" %d", &x);
//     printf("Enter value of y in range [0:%d]: ", (int)pow(2, n - 1));
//     scanf(" %d", &y);

//     cout << "n: " << n << endl;
//     cout << "x: " << binstring(n, x) << endl;
//     cout << "y: " << binstring(n, y) << endl;
//     return 0;
// }
