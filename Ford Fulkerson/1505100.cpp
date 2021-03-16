#include <bits/stdc++.h>

using namespace std;

const int maxn = 111111;
const int inf = 111111111;

bool mark[111];
queue <int> q;
vector <int> vec[111];
int n, m, s, t, arr[111][111], weight[111][111], par[111];

bool bfs()
{
    memset(par, 0, sizeof(par));
    memset(mark, false, sizeof(mark));

    while(!q.empty())
        q.pop();

    q.push(s), mark[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < vec[u].size(); ++i)
        {
            if (arr[u][vec[u][i]] > 0 && !mark[vec[u][i]])
            {
                par[vec[u][i]] = u;
                q.push(vec[u][i]);
                mark[vec[u][i]] = true;
            }
        }
    }

    return mark[t];
}

int capacity()
{
    int u = t, mn = inf;

    while (u != s)
        mn = min(mn, arr[par[u]][u]), u = par[u];

    u = t;

    while (u != s)
    {
        arr[par[u]][u] -= mn;
        arr[u][par[u]] += mn;
        u = par[u];
    }

    return mn;
}

int solve()
{
    int ans = 0;

    while (bfs())
        ans += capacity();

    return ans;
}

void dfs(int u)
{
    mark[u] = true;

    for (int i = 0; i < vec[u].size(); ++i)
    {
        if (arr[i][vec[u][i]] > 0 && !mark[vec[u][i]])
            dfs(vec[u][i]);
    }

}

int main()
{
    memset(arr, 0, sizeof(arr));

    cin >> n >> m >> s >> t;

    int u, v, w;

    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        weight[u][v] = arr[u][v] = w;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    cout << "Max Flow : " << solve() << endl;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (weight[i][j])
                cout << i << "->" << j << " = " << weight[i][j] - arr[i][j] << endl;
        }
    }

    memset(mark, false, sizeof(mark));

    dfs(s);

    cout << "Min-Cut Edges :" << endl;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (weight[i][j] && mark[i] && !mark[j])
                cout << i << " " << j << endl;
        }
    }

    return 0;
}

/*
 6 10 1 6
 1 2 16
 1 3 13
 2 3 10
 2 4 12
 3 2 4
 3 5 14
 4 3 9
 4 6 20
 5 4 7
 5 6 4
 */
