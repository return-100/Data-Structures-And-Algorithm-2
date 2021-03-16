#include <bits/stdc++.h>

using namespace std;

int n, m, arr[1000], brr[1000], ans[1000], dp[1000][1000];

int solve(int idx, int val)
{
    if (!val)
        return 0;
    
    if (idx == m)
        return 100000000;
    
    if (dp[idx][val] != -1)
        return dp[idx][val];
    
    int ret = INT_MAX;
    
    for (int i = 1; i <= brr[idx]; ++i)
    {
        if (val - arr[idx] * i >= 0)
        {
            int var = i + solve(idx + 1, val - arr[idx] * i);
            
            if (var < ret)
                ret = var;
        }
    }
    
    int var = solve(idx + 1, val);
    
    if (var < ret)
        ret = var;
    
    return dp[idx][val] = ret;
}

void backtrack(int idx, int val, int res)
{
    if (!res)
        return;
    
    for (int i = 1; i <= brr[idx]; ++i)
    {
        if (val - arr[idx] * i >= 0)
        {
            if (i + dp[idx + 1][val - arr[idx] * i] == res)
            {
                ans[idx] = i;
                backtrack(idx + 1, val - arr[idx] * i, res - i);
                return;
            }
        }
    }
    
    if (dp[idx + 1][val] == res)
        ans[idx] = 0, backtrack(idx + 1, val, res);
}

int main()
{
    memset(dp, -1, sizeof(dp));
    
    cin >> n >> m;
    
    for (int i = 0; i < m; ++i)
        cin >> arr[i];
    
    for (int i = 0; i < m; ++i)
        cin >> brr[i];
    
    int res = solve(0, n);
    
    backtrack(0, n, res);
    
    cout << res << endl;
    
    for (int i = 0; i < m; ++i)
    {
        if (ans[i])
            cout << arr[i] << '*' << ans[i] << endl;
    }
    
    return 0;
}
