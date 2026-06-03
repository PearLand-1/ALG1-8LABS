/* =======================================================

    Алгоритми і структура данних
    Лабораторні роботи №24-30 (графи ширше)
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "mainGraphMore.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include "../MyLib.h"
#include "../graph/graph.h"
#include "graph_high.h"

using namespace std;

static AdjMatrix g_graph;
static bool g_hasGraph = false;

static void ShowHeader(const string& title, const string& subtitle)
{
    ClearScreen();
    cout << FromCustomFormatToString(
        "<magenta><i><u>" + title + "</u></i></magenta>\n"
        "<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>\n"
        "<cyan>" + subtitle + "</cyan>\n");
}

static bool EnsureGraphLoaded()
{
    if (g_hasGraph && !g_graph.empty())
        return true;
    LogError("Спочатку введiть або завантажте граф.");
    WaitForEnter();
    return false;
}

static bool AskVisualize()
{
    cout << FromCustomFormatToString(
        "<yellow>Показувати кроки?</yellow>\n"
        "  1 - так\n"
        "  2 - нi\n");
    return ReadIntInRange("Ваш вибiр: ", 1, 2) == 1;
}

static void InputAdjMatrixKeyboard()
{
    const int n = ReadPositiveInt("Введiть кiлькiсть вершин n: ");
    g_graph = ReadAdjMatrixKeyboard(n);
    g_hasGraph = true;
    LogSuccess("Матрицю зчитано.");
    WaitForEnter();
}

static void InputAdjMatrixFromFile()
{
    cout << "Введiть iм'я файлу: ";
    string path;
    cin >> path;

    AdjMatrix a;
    if (!ReadAdjMatrixFromFile(path, a))
    {
        LogError("Не вдалося зчитати матрицю з файлу.");
        WaitForEnter();
        return;
    }
    g_graph = std::move(a);
    g_hasGraph = true;
    LogSuccess("Граф завантажено з файлу.");
    WaitForEnter();
}

static void InputAdjMatrixFromEdges()
{
    const int n = ReadPositiveInt("Введiть кiлькiсть вершин n: ");
    const int m = ReadIntInRange("Введiть кiлькiсть ребер m: ", 0, n * n);

    cout << FromCustomFormatToString(
        "<yellow>Тип графа:</yellow>\n"
        "  1 - неорiєнтований\n"
        "  2 - орiєнтований\n");
    const int type = ReadIntInRange("Ваш вибiр: ", 1, 2);
    const bool directed = (type == 2);

    AdjMatrix a;
    if (!BuildAdjMatrixFromEdgeList(n, m, directed, a))
    {
        LogError("Помилка введення ребер.");
        WaitForEnter();
        return;
    }

    g_graph = std::move(a);
    g_hasGraph = true;
    LogSuccess("Матрицю сумiжностi сформовано зi списку ребер.");
    WaitForEnter();
}

static void ShowGraphInfo()
{
    if (!EnsureGraphLoaded())
        return;

    ShowHeader("Лабораторна 21-23: довiдка про граф", "Матричне представлення та характеристики");
    PrintAdjMatrix(g_graph);
    PrintReport(g_graph);
    WaitForEnter();
}

// ---------- Лаб 24: топологічне сортування ----------
static bool TopoSortDfs(vector<int>& outOrder, bool visualize)
{
    const int n = static_cast<int>(g_graph.size());
    const AdjMatrix adj = g_graph;
    auto list = BuildAdjList(adj); // directed adjacency from matrix

    vector<int> color(n, 0); // 0 - unvisited, 1 - visiting, 2 - done
    vector<int> order;
    order.reserve(n);

    function<bool(int)> dfs = [&](int v) -> bool
    {
        color[v] = 1;
        if (visualize)
        {
            cout << "DFS: входимо в вершину " << v + 1 << endl;
            Delay();
        }

        for (int to : list[v])
        {
            if (color[to] == 0)
            {
                if (visualize)
                {
                    cout << "  перехiд " << v + 1 << " -> " << to + 1 << endl;
                    Delay();
                }
                if (!dfs(to))
                    return false;
            }
            else if (color[to] == 1)
            {
                // back edge => cycle
                if (visualize)
                {
                    cout << FromCustomFormatToString(
                        "<red>Знайдено цикл:</red> " +
                        to_string(v + 1) + " -> " + to_string(to + 1)) << endl;
                }
                return false;
            }
        }

        color[v] = 2;
        order.push_back(v);
        if (visualize)
        {
            cout << "DFS: завершуємо вершину " << v + 1 << endl;
            Delay();
        }
        return true;
    };

    for (int i = 0; i < n; i++)
        if (color[i] == 0)
            if (!dfs(i))
                return false;

    // reverse finish order => topological order
    outOrder.assign(order.rbegin(), order.rend());
    return true;
}

static bool TopoSortKahn(vector<int>& outOrder, bool visualize)
{
    const int n = static_cast<int>(g_graph.size());
    auto list = BuildAdjList(g_graph); // directed adjacency from matrix

    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : list[u])
            indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);

    outOrder.clear();
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        outOrder.push_back(v);

        if (visualize)
        {
            cout << "Kahn: вибираємо вершину " << v + 1 << " (indeg=0)" << endl;
            Delay();
        }

        for (int to : list[v])
        {
            indeg[to]--;
            if (visualize)
            {
                cout << "  зменшуємо indeg(" << to + 1 << ") -> " << indeg[to] << endl;
                Delay();
            }
            if (indeg[to] == 0)
                q.push(to);
        }
    }

    return static_cast<int>(outOrder.size()) == n;
}

static void RunTopoDfs()
{
    if (!EnsureGraphLoaded())
        return;

    ShowHeader("Лабораторна 24. Топологічне сортування", "DFS + перевірка на цикли");
    PrintAdjMatrix(g_graph);

    const bool visualize = AskVisualize();
    vector<int> order;
    const bool ok = TopoSortDfs(order, visualize);

    cout << endl;
    if (!ok)
    {
        LogError("Граф мiстить цикл. Топологiчне сортування неможливе.");
    }
    else
    {
        LogSuccess("Циклів немає. Топологічний порядок:");
        for (int v : order)
            cout << v + 1 << ' ';
        cout << endl;
    }
    WaitForEnter();
}

static void RunTopoKahn()
{
    if (!EnsureGraphLoaded())
        return;

    ShowHeader("Лабораторна 24. Топологічне сортування", "Алгоритм Кана + перевірка на цикли");
    PrintAdjMatrix(g_graph);

    const bool visualize = AskVisualize();
    vector<int> order;
    const bool ok = TopoSortKahn(order, visualize);

    cout << endl;
    if (!ok)
    {
        LogError("Граф мiстить цикл. Топологiчне сортування неможливе.");
    }
    else
    {
        LogSuccess("Циклів немає. Топологічний порядок:");
        for (int v : order)
            cout << v + 1 << ' ';
        cout << endl;
    }
    WaitForEnter();
}

// ---------- Лаб 25: Краскал ----------
struct KEdge
{
    int u = 0;
    int v = 0;
    int w = 0;
};

static bool KEdgeLess(const KEdge& a, const KEdge& b) { return a.w < b.w; }

static int UndirectedWeight(int i, int j)
{
    // weight between i and j for undirected algorithms:
    // - if both directions missing => no edge (0)
    // - if only one direction exists => use that weight
    // - if both exist but differ => use min and proceed
    const int a = g_graph[i][j];
    const int b = g_graph[j][i];
    if (a == 0 && b == 0)
        return 0;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == b)
        return a;
    return min(a, b);
}

struct DSU
{
    vector<int> parent;
    explicit DSU(int n) : parent(n, -1) {}

    int find(int x)
    {
        if (parent[x] == -1) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[a] = b;
        return true;
    }
};

static void RunKruskal()
{
    if (!EnsureGraphLoaded())
        return;

    ShowHeader("Лабораторна 25. Мінімальне кістякове дерево", "Алгоритм Краскала");
    PrintAdjMatrix(g_graph);

    const bool visualize = AskVisualize();
    const bool symmetric = IsSymmetric(g_graph);
    if (!symmetric)
        LogError("Увага: матриця несиметрична. Для MST беремо вагу як min(A[i][j], A[j][i]) де обидва ненульові.");

    const int n = static_cast<int>(g_graph.size());
    vector<KEdge> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            const int w = UndirectedWeight(i, j);
            if (w != 0)
                edges.push_back({i, j, w});
        }

    if (n == 0 || edges.empty())
    {
        LogError("Недостатньо даних: немає ребер для побудови MST.");
        WaitForEnter();
        return;
    }

    sort(edges.begin(), edges.end(), KEdgeLess);

    DSU dsu(n);
    vector<KEdge> result;
    result.reserve(n - 1);
    int totalWeight = 0;

    for (const auto& e : edges)
    {
        if (visualize)
        {
            cout << "Розглядаємо ребро: " << e.u + 1 << "-" << e.v + 1 << " (w=" << e.w << ")\n";
            Delay();
        }

        if (dsu.unite(e.u, e.v))
        {
            result.push_back(e);
            totalWeight += e.w;
            if (visualize)
            {
                LogSuccess("  -> Додаємо до MST.");
                Delay();
            }
        }
        else
        {
            if (visualize)
            {
                LogError("  -> Відхиляємо (цикл).");
                Delay();
            }
        }

        if (static_cast<int>(result.size()) == n - 1)
            break;
    }

    cout << endl;
    if (static_cast<int>(result.size()) != n - 1)
    {
        LogError("Граф не є зв'язним (MST не існує повністю). Виводжу часткове дерево:");
    }
    else
    {
        LogSuccess("Мінімальне кістякове дерево побудовано.");
    }

    for (const auto& e : result)
        cout << e.u + 1 << " - " << e.v + 1 << " Вага: " << e.w << endl;
    cout << "Сума ваги: " << totalWeight << endl;

    WaitForEnter();
}

// ---------- Лаб 26: Прім ----------
static void RunPrim()
{
    if (!EnsureGraphLoaded())
        return;

    ShowHeader("Лабораторна 26. Мінімальне кістякове дерево", "Алгоритм Пріма");
    PrintAdjMatrix(g_graph);

    const bool visualize = AskVisualize();
    const bool symmetric = IsSymmetric(g_graph);
    if (!symmetric)
        LogError("Увага: матриця несиметрична. Для MST беремо вагу як min(A[i][j], A[j][i]) де обидва ненульові.");

    const int n = static_cast<int>(g_graph.size());
    if (n == 0)
    {
        LogError("Граф порожнiй.");
        WaitForEnter();
        return;
    }

    const int start = ReadIntInRange("Початкова вершина (0.." + to_string(n - 1) + "): ", 0, n - 1);

    const int INF = numeric_limits<int>::max();
    vector<int> parent(n, -1);
    vector<int> key(n, INF);
    vector<bool> used(n, false);

    key[start] = 0;
    parent[start] = -1;

    for (int iter = 0; iter < n - 1; iter++)
    {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!used[v] && (u == -1 || key[v] < key[u]))
                u = v;

        if (u == -1 || key[u] == INF)
            break; // disconnected

        used[u] = true;
        if (visualize)
        {
            if (parent[u] != -1)
                cout << "Прiм: беремо вершину " << u + 1 << ", ребро "
                     << parent[u] + 1 << "-" << u + 1
                     << " (w=" << key[u] << ")\n";
            else
                cout << "Прiм: стартуємо з вершини " << u + 1 << endl;
            Delay();
        }

        for (int v = 0; v < n; v++)
        {
            const int w = UndirectedWeight(u, v);
            if (!used[v] && w != 0 && w < key[v])
            {
                key[v] = w;
                parent[v] = u;
                if (visualize)
                {
                    cout << "  Оновлюємо key(" << v + 1 << ")=" << w
                         << ", parent(" << v + 1 << ")=" << u + 1 << endl;
                    Delay();
                }
            }
        }
    }

    int totalWeight = 0;
    for (int v = 0; v < n; v++)
        if (parent[v] != -1 && key[v] != INF)
            totalWeight += key[v];

    bool allUsed = true;
    for (int i = 0; i < n; i++)
        if (!used[i])
            allUsed = false;

    cout << endl;
    if (!allUsed)
        LogError("Граф не є зв'язним (MST не існує повністю). Виводжу часткове дерево:");
    else
        LogSuccess("Мінімальне кістякове дерево побудовано.");

    for (int i = 0; i < n; i++)
    {
        if (parent[i] != -1)
            cout << parent[i] + 1 << " - " << i + 1 << " Вага: " << UndirectedWeight(parent[i], i) << endl;
    }
    cout << "Сума ваги: " << totalWeight << endl;

    WaitForEnter();
}

// ---------- Меню ----------
void GraphMoreMain()
{
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторні роботи 24-30. Розширені графи", "Топологічне сортування, MST, та алгоритми найкоротшого шляху");

        if (g_hasGraph && !g_graph.empty())
            LogSuccess("Граф завантажено: " + to_string(g_graph.size()) + " вершин.");
        else
            LogError("Граф ще не задано. Спочатку введіть або завантажте його.");

        cout << FromCustomFormatToString(R"(
<green>Меню графів (24-30):</green>

Введення / довiдка:
  1 - Ввести матрицю з клавiатури
  2 - Зчитати матрицю з файлу
  3 - Задати граф списком ребер (матриця будується автоматично)
  4 - Показати довiдку про граф

Лаб. 24 (топологічне сортування):
  5 - Топологічне сортування DFS + перевірка циклів
  6 - Топологічне сортування Кана + перевірка циклів

Лаб. 25 (Краскал):
  7 - Мінімальне кістякове дерево (Краскал)

Лаб. 26 (Прім):
  8 - Мінімальне кістякове дерево (Прім)

Лаб. 27 (Дейкстра):
  9 - Алгоритм Дейкстри (на завантаженому графі)

Лаб. 28 (Беллман-Форд):
 10 - Алгоритм Беллмана-Форда (на завантаженому графі)

Лаб. 29 (Флойд-Воршалл):
 11 - Алгоритм Флойда-Воршалла (на завантаженому графі)

Лаб. 30 (A*):
 12 - Алгоритм A* (на завантаженому графі)

  0 - Повернутись назад

<green>Оберiть опцiю: </green>)");

        const int choice = ReadIntInRange("", 0, 12);
        switch (choice)
{
        case 1: InputAdjMatrixKeyboard(); break;
        case 2: InputAdjMatrixFromFile(); break;
        case 3: InputAdjMatrixFromEdges(); break;
        case 4: ShowGraphInfo(); break;
        case 5: RunTopoDfs(); break;
        case 6: RunTopoKahn(); break;
        case 7: RunKruskal(); break;
        case 8: RunPrim(); break;
        case 9: if (EnsureGraphLoaded()) RunHighDijkstra(g_graph); break;
        case 10: if (EnsureGraphLoaded()) RunHighBellmanFord(g_graph); break;
        case 11: if (EnsureGraphLoaded()) RunHighFloydWarshall(g_graph); break;
        case 12: if (EnsureGraphLoaded()) RunHighAStar(g_graph); break;
        case 0: run = false; break;
        default: LogError("Невiдома опцiя."); break;
        }
    }
}

