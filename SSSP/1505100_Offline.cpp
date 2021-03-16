#include <bits/stdc++.h>
#define NULL_VALUE -999999
#define INF 100000000
#define WHITE 1
#define GREY 2
#define BLACK 3

#define MAX_HEAP_SIZE 100010

#define MAXREAL 999999.0

const int maxn = 100010;

using namespace std;

/********************* Variable for LCA *************/

int val[maxn], mx[maxn][17], table[maxn][17];

/************************ Pair **********************/

class Pair
{
public:
    int x, y;
};

/************************ Heap *************************/

class HeapItem
{
public:
    int data;
    int key;
};

class MinHeap
{
public:
    HeapItem * A;
    int heapLength;
    int * map;
    
    MinHeap()
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength = 0;
    }
    
    ~MinHeap()
    {
        if(map)
            delete [] map;
        
        if(A)
            delete [] A;
        
        map = 0;
        A = 0;
    }
    
    void initialize(int n)
    {
        heapLength = n;
        
        for (int i = 0; i < n; i++)
        {
            A[i + 1].data = i + 1;
            A[i + 1].key = INF;
            map[i + 1] = i + 1;
        }
    }
    
    void insertItem(int data, int key, int id)
    {
        ++heapLength;
        A[heapLength].data = data;
        A[heapLength].key = key;
        map[A[heapLength].data] = heapLength;
        buHeapify(heapLength);
    }
    
    HeapItem removeMin()
    {
        if (!heapLength)
        {
            printf("Empty Heap\n");
            HeapItem temp;
            temp.data = -1;
            temp.key = -1;
            return temp;
        }
        
        HeapItem temp = A[1];
        A[1] = A[heapLength];
        map[A[1].data] = 1;
        --heapLength;
        heapify(1);
        return temp;
    }
    
    void updateKey(int data, int key)
    {
        int idx = map[data];
        
        if (A[idx].key > key)
        {
            A[idx].key = key;
            buHeapify(idx);
        }
        else
        {
            A[idx].key = key;
            heapify(idx);
        }
    }
    
    int getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }
    
    void heapify(int i)
    {
        int l, r, smallest;
        
        while (true)
        {
            l = 2 * i;
            r = 2 * i + 1;
            smallest = i;
            
            if (l > heapLength && r > heapLength)
                break;
            else if (r > heapLength)
                smallest = l;
            else if (l > heapLength)
                smallest = r;
            else if (A[l].key < A[r].key)
                smallest = l;
            else if (A[l].key > A[r].key)
                smallest = r;
            else if (A[l].data < A[r].data)
                smallest = l;
            else
                smallest = r;
            
            if (A[i].key <= A[smallest].key)
                break;
            else
            {
                HeapItem t;
                t = A[i];
                A[i] = A[smallest];
                map[A[i].data] = i;
                A[smallest] = t;
                map[A[smallest].data] = smallest;
                i = smallest;
            }
        }
    }
    
    void buHeapify(int i)
    {
        HeapItem temp;
        
        while (i > 1)
        {
            if (A[i].key < A[i / 2].key || (A[i].key == A[i / 2].key && A[i].data < A[i / 2].data))
            {
                map[A[i].data] = i / 2;
                map[A[i / 2].data] = i;
                temp = A[i];
                A[i] = A[i / 2];
                A[i / 2] = temp;
            }
            else
                break;
            
            i /= 2;
        }
    }
    
    void printHeap()
    {
        for (int i = 1; i <= heapLength; i++)
            cout << A[i].data << " " << A[i].key << endl;
    }
    
    bool Empty()
    {
        if (heapLength==0)
            return true;
        else
            return false;
    }
};

/***************************** queue *************************/

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item);
    int dequeue();
    bool empty();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize];
    length = 0 ;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData;
        queueMaxSize = 2 * queueMaxSize;
        tempData = new int[queueMaxSize];
        int i, j;
        j = 0;
        
        for (i = rear; i < length; i++)
            tempData[j++] = data[i];
        
        for (i = 0; i < rear; i++)
            tempData[j++] = data[i];
        
        rear = 0;
        front = length;
        delete[] data;
        data = tempData;
    }
    
    data[front] = item;
    front = (front + 1) % queueMaxSize;
    length++ ;
}

bool Queue::empty()
{
    if (length == 0)
        return true ;
    else
        return false ;
}

int Queue::dequeue()
{
    if (length == 0)
        return NULL_VALUE ;
    
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}

Queue::~Queue()
{
    if(data)
        delete[] data;
    
    data = 0;
}

/********************** Dynamic ArrayList class based  ************************/

class ArrayList
{
    Pair * list;
    int length;
    int listMaxSize;
    int listInitSize;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(Pair item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    Pair getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;

ArrayList::ArrayList()
{
    listInitSize = 2;
    listMaxSize = listInitSize;
    list = new Pair[listMaxSize];
    length = 0;
}

void ArrayList::insertItem(Pair newitem)
{
    Pair * tempList;
    
    if (length == listMaxSize)
    {
        listMaxSize = 2 * listMaxSize;
        tempList = new Pair[listMaxSize];
        
        for(int i = 0; i < length; i++)
            tempList[i] = list[i];
        
        delete[] list;
        list = tempList;
    };
    
    list[length] = newitem;
    length++;
}

int ArrayList::searchItem(int item)
{
    for (int i = 0; i < length; i++)
    {
        if(list[i].x == item)
            return i;
    }
    
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position)
{
    if (position < 0 || position >= length)
        return;
    
    list[position] = list[length-1];
    length--;
}

void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item);
    
    if (position == NULL_VALUE)
        return;
    
    removeItemAt(position);
}

Pair ArrayList::getItem(int position)
{
    Pair temp;
    temp.x = NULL_VALUE;
    temp.y = NULL_VALUE;
    
    if(position < 0 || position >= length)
        return temp;
    
    return list[position];
}

int ArrayList::getLength()
{
    return length;
}

bool ArrayList::empty()
{
    if (length==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    for(int i = 0; i < length; i++)
        printf("%d ", list[i].x);
    
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if (list)
        delete [] list;
    
    list = 0 ;
}

/********************** Graph class starts here **************************/

class Graph
{
public:
    int nVertices, nEdges, time;
    bool directed;
    ArrayList  * adjList;
    int *color;
    int *parent;
    int *dist;
    int *tin;
    int *tout;
    int *depth;
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source);
    void dfs(int source);
    void dfs_traversal();
};

Graph::Graph(bool dir)
{
    depth = 0;
    nVertices = 0;
    nEdges = 0;
    adjList = 0;
    color = 0;
    time = 0;
    tin = 0;
    tout = 0;
    parent = 0;
    time = 0;
    dist = 0;
    directed = dir;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n + 1;
    if(adjList!=0) delete[] adjList;
    if(color!=0) delete[] color;
    if(parent!=0) delete[] parent;
    if(tin!=0) delete[] tin;
    if(tout!=0) delete[] tout;
    if(dist!=0) delete[] dist;
    if(depth!=0) delete[] depth;
    
    adjList = new ArrayList[nVertices];
    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    tin = new int[nVertices];
    tout = new int[nVertices];
    depth = new int[nVertices];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u <= 0 || v <= 0 || u >= nVertices || v >= nVertices)
        return;
    
    Pair temp;
    temp.x = v;
    temp.y = w;
    
    this->nEdges++;
    adjList[u].insertItem(temp);
    
    temp.x = u;
    
    if(!directed)
        adjList[v].insertItem(temp);
}

void Graph::removeEdge(int u, int v)
{
    if(u <= 0 || v <= 0 || u >= nVertices || v >= nVertices)
        return;
    
    if(adjList[u].searchItem(v) != NULL_VALUE)
        --nEdges;
    
    adjList[u].removeItem(v);
    adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v) != NULL_VALUE)
        return true;
    
    return false;
}

int Graph::getDegree(int u)
{
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for (int i = 0; i < adjList[u].getLength(); ++i)
    {
        if (i != v && adjList[v].searchItem(adjList[u].getItem(i).x) != NULL_VALUE)
            return true;
    }
    
    return false;
}

void Graph::bfs(int source)
{
    for (int i = 0; i < nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    
    Queue q;
    color[source] = GREY;
    dist[source] = 0;
    parent[source] = source;
    q.enqueue(source);
    
    while (!q.empty())
    {
        int u = q.dequeue();
        
        for (int i = 0; i < adjList[u].getLength(); ++i)
        {
            Pair temp = adjList[u].getItem(i);
            int v = temp.x;
            
            if (color[v] == WHITE)
            {
                color[v] = GREY;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.enqueue(v);
            }
        }
        
        color[u] = BLACK;
    }
    
    printf("Vertice No\tParent\tDistance From %d\n", source);
    
    for (int i = 0; i < nVertices; ++i)
        printf("%d :\t\t%d\t\t%d\n", i, parent[i], dist[i]);
}

void Graph::dfs_traversal()
{
    for (int i = 1; i < nVertices; ++i)
    {
        color[i] = WHITE;
        dist[i] = INF;
        parent[i] = -1;
        tin[i] = tout[i] = 0;
    }
    
    for (int i = 1; i < nVertices; ++i)
    {
        if(color[i] == WHITE)
        {
            dist[i] = 0;
            depth[i] = 0;
            dfs(i);
        }
    }
}

void Graph::dfs(int u)
{
    color[u] = GREY;
    tin[u] = ++time;
    
    for (int i = 0; i < adjList[u].getLength(); ++i)
    {
        Pair temp = adjList[u].getItem(i);
        int v = temp.x;
        
        if (color[v] == WHITE)
        {
            val[v] = temp.y;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dist[v] = dist[u] + 1;
            dfs(v);
        }
    }
    
    color[u] = BLACK;
    tout[u] = ++time;
}

int Graph::getDist(int u, int v)
{
    bfs(u);
    
    return dist[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    
    for (int i = 0; i < nVertices; i++)
    {
        printf("%d:", i);
        
        for(int j = 0; j < adjList[i].getLength(); j++)
            printf(" %d", adjList[i].getItem(j).x);
        
        printf("\n");
    }
}

Graph::~Graph()
{
    if(color) delete[] color;
    if(parent) delete[] parent;
    if(dist) delete[] dist;
    if(tin) delete[] tin;
    if(tout) delete[] tout;
    if(adjList) delete[] adjList;
    if(depth) delete[] depth;
    
    color = 0;
    adjList = 0;
    dist = 0;
    tin = 0;
    tout = 0;
    parent = 0;
    depth = 0;
}

void bellman()
{
    int n, m, u, v, w;
    
    cin >> n >> m;
    
    Graph g(true);
    g.setnVertices(n);
    
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    
    bool isNegativeEdge = false;
    
    for (int i = 1; i <= n; ++i)
        g.parent[i] = -1, g.dist[i] = INF;
    
    g.dist[1] = 0;
    
    for (int k = 1; k < n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < g.adjList[i].getLength(); ++j)
            {
                v = g.adjList[i].getItem(j).x;
                w = g.adjList[i].getItem(j).y;
                
                if (g.dist[v] > g.dist[i] + w)
                    g.dist[v] = g.dist[i] + w, g.parent[v] = i;
            }
        }
    }
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < g.adjList[i].getLength(); ++j)
        {
            v = g.adjList[i].getItem(j).x;
            w = g.adjList[i].getItem(j).y;
            
            if (g.dist[v] > g.dist[i] + w)
            {
                isNegativeEdge = true;
                break;
            }
        }
        
        if (isNegativeEdge)
            break;
    }
    
    cout << "Vertice" << " ------- " << "Distance" << " --------- " << "Parent" << endl;
    
    for (int i = 1; i <= n; ++i)
        cout << i << " ----- " << g.dist[i] << " --------- " << g.parent[i] << endl;
    
    if (isNegativeEdge)
        cout << "Negative Cycle Found" << endl;
}

int main(void)
{
    bellman();
    
    return 0;
}
