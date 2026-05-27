#include "graph.h"

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

AdjMatrix ReadAdjMatrixKeyboard(int n)
{
    AdjMatrix a(n, vector<int>(n, 0));
    cout << "Введiть матрицю сумiжностi " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    return a;
}

bool ReadAdjMatrixFromFile(const string& path, AdjMatrix& out)
{
    ifstream in(path);
    if (!in) return false;

    int n = 0;
    if (!(in >> n) || n <= 0) return false;

    out.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> out[i][j])) return false;

    return true;
}

bool WriteAdjMatrixToFile(const string& path, const AdjMatrix& a)
{
    ofstream out(path);
    if (!out) return false;

    const int n = static_cast<int>(a.size());
    out << n << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j) out << ' ';
            out << a[i][j];
        }
        out << '\n';
    }
    return true;
}

bool BuildAdjMatrixFromEdgeList(int n, int edgeCount, bool directed, AdjMatrix& out)
{
    if (n <= 0 || edgeCount < 0) return false;

    out.assign(n, vector<int>(n, 0));
    cout << "Введiть " << edgeCount << " ребер (u v [вага]):" << endl;
    cout << "Вершини нумеруються вiд 0 до " << n - 1 << endl;

    for (int k = 0; k < edgeCount; k++)
    {
        int u = 0, v = 0, w = 1;
        cin >> u >> v;
        if (cin.peek() != '\n' && cin.peek() != EOF)
            cin >> w;

        if (u < 0 || u >= n || v < 0 || v >= n)
            return false;

        out[u][v] = w;
        if (!directed)
            out[v][u] = w;
    }
    return true;
}

bool IsNonNegative(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] < 0) return false;
    return true;
}

bool IsSymmetric(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i][j] != a[j][i]) return false;
    return true;
}

bool IsUnweightedLike(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(a[i][j] == 0 || a[i][j] == 1)) return false;
    return true;
}

bool HasLoops(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; i++)
        if (a[i][i] != 0) return true;
    return false;
}

int CountEdges(const AdjMatrix& a, bool directed)
{
    const int n = static_cast<int>(a.size());
    int m = 0;
    if (directed)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][j] != 0) m++;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i][i] != 0) m++;
            for (int j = i + 1; j < n; j++)
                if (a[i][j] != 0) m++;
        }
    }
    return m;
}

AdjMatrix BuildAdjList(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    AdjMatrix g(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] != 0) g[i].push_back(j);
    return g;
}

bool IsConnectedUndirected(const AdjMatrix& g)
{
    const int n = static_cast<int>(g.size());
    if (n == 0) return true;

    vector<bool> used(n, false);
    queue<int> q;
    used[0] = true;
    q.push(0);

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            if (!used[v])
            {
                used[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (!used[i]) return false;
    return true;
}

void PrintAdjMatrix(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    cout << "Матриця сумiжностi:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}

void PrintDegrees(const AdjMatrix& a, bool directed)
{
    const int n = static_cast<int>(a.size());
    if (!directed)
    {
        cout << "Степенi вершин (неорiєнтований граф):" << endl;
        for (int i = 0; i < n; i++)
        {
            int deg = 0;
            for (int j = 0; j < n; j++)
                if (a[i][j] != 0) deg++;
            cout << "deg(" << i << ") = " << deg << endl;
        }
    }
    else
    {
        cout << "Степенi вершин (орiєнтований граф):" << endl;
        for (int i = 0; i < n; i++)
        {
            int outDeg = 0, inDeg = 0;
            for (int j = 0; j < n; j++)
            {
                if (a[i][j] != 0) outDeg++;
                if (a[j][i] != 0) inDeg++;
            }
            cout << "out(" << i << ") = " << outDeg << ", in(" << i << ") = " << inDeg << endl;
        }
    }
}

void PrintAdjListInfo(const AdjMatrix& g)
{
    const int n = static_cast<int>(g.size());
    cout << "Зв'язки мiж вершинами (список сумiжностi як довiдка):" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ": ";
        for (int v : g[i]) cout << v << ' ';
        cout << endl;
    }
}

void PrintReport(const AdjMatrix& a)
{
    const int n = static_cast<int>(a.size());
    const bool ok = IsNonNegative(a);
    const bool symmetric = IsSymmetric(a);
    const bool directed = !symmetric;
    const bool weighted = !IsUnweightedLike(a);

    cout << endl;
    cout << "Довiдка про граф:" << endl;
    if (!ok)
    {
        cout << "Виявлено некоректнi значення: у матрицi є вiд'ємнi числа." << endl;
        cout << "Подальшi висновки можуть бути некоректними." << endl;
    }
    cout << "Кiлькiсть вершин: " << n << endl;
    cout << "Орієнтованiсть: " << (directed ? "орiєнтований" : "неорiєнтований") << endl;
    cout << "Зваженiсть: " << (weighted ? "зважений" : "незважений") << endl;
    cout << "Наявнiсть петель: " << (HasLoops(a) ? "є" : "немає") << endl;
    cout << "Кiлькiсть ребер: " << CountEdges(a, directed) << endl;

    const AdjMatrix g = BuildAdjList(a);
    PrintAdjListInfo(g);
    PrintDegrees(a, directed);

    if (!directed)
    {
        const bool conn = IsConnectedUndirected(g);
        cout << "Зв'язнiсть (для неорiєнтованого): "
             << (conn ? "граф зв'язний" : "граф незв'язний") << endl;
    }
    else
    {
        cout << "Для орiєнтованого графа зв'язнiсть визначають окремо залежно вiд задачi." << endl;
    }
    cout << endl;
}

void Dfs(int node, const AdjMatrix& graph, vector<bool>& visited, bool visualize)
{
    visited[node] = true;
    cout << node << ' ';
    if (visualize)
    {
        cout << endl;
        cout << "  -> вiдвiдано вершину " << node << endl;
    }

    const int n = static_cast<int>(graph.size());
    for (int i = 0; i < n; ++i)
    {
        if (graph[node][i] != 0 && !visited[i])
        {
            if (visualize)
                cout << "  перехiд " << node << " -> " << i << endl;
            Dfs(i, graph, visited, visualize);
        }
    }
}

void Bfs(int start, const AdjMatrix& graph, vector<bool>& visited, bool visualize)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        const int current = q.front();
        q.pop();
        cout << current << ' ';
        if (visualize)
            cout << endl << "  -> вiдвiдано вершину " << current << endl;

        const int n = static_cast<int>(graph.size());
        for (int i = 0; i < n; ++i)
        {
            if (graph[current][i] != 0 && !visited[i])
            {
                if (visualize)
                    cout << "  додано в чергу: " << i << " (з " << current << ")" << endl;
                q.push(i);
                visited[i] = true;
            }
        }
    }
}
