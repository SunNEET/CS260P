#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <cstdlib>
using namespace std;

string int_to_bits(int x, int n)
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

void LCS(const string& X, const string& Y, int n, int m, int len, unordered_set<string>& res, string& str, const vector<vector<int> >& L)
{
    if(len == 0) {
        res.insert(str);
        return;
    }
    if(n == 0 || m == 0) return;
    int i = n, j = m;
    if(!L[i][j] && !L[i-1][j] && !L[i][j-1] && !L[i-1][j-1]) return;
    if (X[i - 1] == Y[j - 1]) {
        LCS(X,Y,i-1,j-1,len,res,str,L);
        str[len-1] = X[i-1];
        LCS(X,Y,i-1,j-1,len-1,res,str,L);
    } else {
        if(L[i-1][j] >= L[i][j-1])
            LCS(X,Y,i-1,j,len,res,str,L);
        if(L[i][j-1] >= L[i-1][j])
            LCS(X,Y,i,j-1,len,res,str,L);
    }
}

vector<vector<int> > LCSTable(string X, string Y, int n){
    vector<vector<int> > L(n+1, vector<int>(n+1, 0));
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            if (i == 0 || j == 0) L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1]) L[i][j] = L[i - 1][j - 1] + 1;
            else L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    return L;
}

int main()
{
    freopen("in","r", stdin);
    int maxCount = 0;
    int n, x, y;
    n = 14;
    printf("Enter value of n in range [3:20] : ");
    scanf(" %d", &n);
    if(n < 3 || n > 20) {
        puts("Invalid input");
        return 0;
    }
    int M = (int)pow(2, n) - 1;
    printf("Enter value of x in range [0:%d] : ", M);
    scanf(" %d", &x);
    if( x > M) {
        puts("Invalid input x");
        return 0;
    }
    printf("Enter value of y in range [0:%d] : ", (int)pow(2, n) - 1);
    scanf(" %d", &y);
    if(y > M) {
        puts("Invalid input y");
        return 0;
    }
    int ans_x = 0, ans_y = 0, maxCnt = 0; 
    string sx = int_to_bits(x, n);
    string sy = int_to_bits(y, n);
    printf("LCS's from X = %s\n", sx.c_str());
    printf("LCS's from Y = %s\n", sy.c_str());
    string str = "";
    auto lcsTable = LCSTable(sx, sy, n);
    int len = lcsTable[n][n];
    for(int i=0; i<len; i++) str += " ";

    unordered_set<string> res;
    LCS(sx,sy,n,n,len,res,str,lcsTable);
    if(res.size() > maxCnt) {
        maxCnt = (int)res.size();
        ans_x = x;
        ans_y = y;
    }
    for(auto e : res) printf("%s\n", e.c_str());
    return 0;
}