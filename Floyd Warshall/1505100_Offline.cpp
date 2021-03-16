#include <bits/stdc++.h>

using namespace std;

const int inf = 99999999;

int n, m, u, v, w, parent[111][111], dist[111][111];

void solve()
{
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    parent[i][j] = parent[k][j];
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = inf;
            
            parent[i][j] = inf;
        }
    }
    
    for (int i = 0; i < m; ++i)
        cin >> u >> v >> w, dist[u][v] = w, parent[u][v] = u;
    
    cout << endl << "Initial Matrix" << endl;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << setw(8) << right << dist[i][j] << "  ";
        
        cout << endl;
    }
    
    solve();
    
    cout << endl << "All Pair Shortest Path" << endl;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << setw(8) << right << dist[i][j] << "  ";
        
        cout << endl;
    }
    
    cout << endl << "Parent Matrix" << endl;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << setw(8) << right << parent[i][j] << "  ";
        
        cout << endl;
    }
    
    return 0;
}
