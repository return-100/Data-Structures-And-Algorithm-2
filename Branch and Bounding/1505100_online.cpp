#include<bits/stdc++.h>

using namespace std;

const int maxn = 111111;

string str;
vector <int> vec[22];
int n, m, var, ans, ansMask;

void solve(int mask, int idx)
{
    set <int> st;
    int mxcd = 0, cnt = 0;
    int pick = 0, curBound = maxn;
    
    for (int i = 0; i < m; i++)
    {
        if (mask & (1 << i))
        {
            pick++;
            
            for (int j = 0; j < vec[i].size(); j++)
                st.insert(vec[i][j]);
        }
        else
            mxcd = max(mxcd, (int) vec[i].size());
    }

    if (mxcd)
        curBound = pick + ceil((float)(n - st.size()) / mxcd);
    
    if (st.size() == n)
    {
        cnt = 0;
        
        for (int i = 0; i < m; ++i)
        {
            if (mask & (1 << i))
                cnt++;
        }
        
        if (ans > cnt)
        {
            ans = cnt;
            ansMask = mask;
            return;
        }
    }
    
    if (curBound >= ans)
        return;
    
    string a, b;
    
    if (idx < m)
        solve(mask, idx + 1), solve(mask | (1 << idx), idx + 1);
}

int main()
{
    cin >> n >> m;
    cin.get(), ans = m;
    
    for (int i = 0; i < m; ++i)
    {
        getline(cin, str);
        stringstream sstr(str);
        
        while (sstr >> var)
            vec[i].push_back(var);
    }
    
    solve(0, 0);
    
    cout << ans << endl;
    
    for (int i = 0; i < m; ++i)
    {
        if (ansMask & (1 << i))
        {
            for (int j = 0; j < vec[i].size(); ++j)
                cout << vec[i][j] << " ";
            
            cout << endl;
        }
    }
    
    return 0;
}

