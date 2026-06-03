/*
    Лабораторні 27-30 (об'єднані):
    Дейкстра, Беллман-Форд, Флойд-Воршалл, A*
    Реалізація для папки graph_more
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>

#include "../MyLib.h"
#include "../graph/graph.h"

using namespace std;

const int INF = 1e9;

// Структури даних для представлення графа
struct Node {
    int id;
    double x, y;
};

struct Edge {
    int from, to;
    int weight;
};

struct Graph {
    int numVertices = 0;
    int numEdges = 0;
    vector<Node> nodes;
    vector<Edge> edges;
    vector<vector<pair<int, int>>> adjList; // для Дейкстри та A*
};

// Завантаження графа з файлу
bool loadGraphFromFile(const string& filename, Graph& g) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file >> g.numVertices >> g.numEdges;
    g.nodes.resize(g.numVertices);
    for (int i = 0; i < g.numVertices; ++i) {
        file >> g.nodes[i].id >> g.nodes[i].x >> g.nodes[i].y;
    }
    g.edges.resize(g.numEdges);
    g.adjList.clear();
    g.adjList.resize(g.numVertices);
    for (int i = 0; i < g.numEdges; ++i) {
        file >> g.edges[i].from >> g.edges[i].to >> g.edges[i].weight;
        if (g.edges[i].from >= 0 && g.edges[i].from < g.numVertices)
            g.adjList[g.edges[i].from].push_back({g.edges[i].to, g.edges[i].weight});
    }
    file.close();
    return true;
}

static bool EnsureGraphLoadedFromFile(Graph& g)
{
    const string filename = "graph.txt";
    if (!loadGraphFromFile(filename, g)) {
        cout << "Помилка! Не вдалося знайти або відкрити файл '" << filename << "'\n";
        cout << "Будь ласка, створіть текстовий файл '" << filename << "' поруч із виконуваним кодом.\n";
        return false;
    }
    cout << "Граф успішно імпортовано з файлу '" << filename << "'. Кількість вершин: " << g.numVertices << ", ребер: " << g.numEdges << "\n";
    return true;
}

static int ReadGraphVertex(const Graph& g, const string& prompt)
{
    return ReadIntInRange(prompt, 0, g.numVertices - 1);
}

static Graph ConvertAdjMatrixToGraph(const AdjMatrix& a)
{
    Graph g;
    g.numVertices = static_cast<int>(a.size());
    g.nodes.resize(g.numVertices);
    g.adjList.assign(g.numVertices, {});

    for (int i = 0; i < g.numVertices; ++i)
    {
        g.nodes[i].id = i;
        g.nodes[i].x = 0.0;
        g.nodes[i].y = 0.0;
    }

    for (int u = 0; u < g.numVertices; ++u)
    {
        for (int v = 0; v < static_cast<int>(a[u].size()); ++v)
        {
            int w = a[u][v];
            if (w != 0)
            {
                g.adjList[u].push_back({v, w});
                g.edges.push_back({u, v, w});
            }
        }
    }
    g.numEdges = static_cast<int>(g.edges.size());
    return g;
}

// 1. АЛГОРИТМ ДЕЙКСТРИ
void runDijkstra(const Graph& g, int start) {
    vector<int> dist(g.numVertices, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : g.adjList[u]) {
            int v = edge.first;
            int w = edge.second;
            if (w < 0) {
                cout << "[Увага] Алгоритм Дейкстри може працювати некоректно з від'ємними вагами!\n";
            }
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\n--- Результати алгоритму Дейкстри (від вершини " << start << ") ---\n";
    for (int i = 0; i < g.numVertices; ++i) {
        cout << "До вершини " << i << ": ";
        if (dist[i] == INF) cout << "недосяжно\n";
        else cout << dist[i] << "\n";
    }
}

// 2. АЛГОРИТМ БЕЛЛМАНА-ФОРДА
void runBellmanFord(const Graph& g, int start) {
    vector<int> dist(g.numVertices, INF);
    dist[start] = 0;

    for (int i = 1; i <= g.numVertices - 1; ++i) {
        for (const auto& edge : g.edges) {
            if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }

    // Перевірка на від'ємні цикли
    bool hasNegativeCycle = false;
    for (const auto& edge : g.edges) {
        if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
            hasNegativeCycle = true;
            break;
        }
    }

    cout << "\n--- Результати алгоритму Беллмана-Форда (від вершини " << start << ") ---\n";
    if (hasNegativeCycle) {
        cout << "[КРИТИЧНО] Граф містить ВІД'ЄМНИЙ ЦИКЛ! Пошук найкоротших шляхів неможливий.\n";
        return;
    }

    for (int i = 0; i < g.numVertices; ++i) {
        cout << "До вершини " << i << ": ";
        if (dist[i] == INF) cout << "недосяжно\n";
        else cout << dist[i] << "\n";
    }
}

// 3. АЛГОРИТМ ФЛОЙДА-ВОРШАЛЛА
void runFloydWarshall(const Graph& g, int source, int target) {
    int n = g.numVertices;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> next(n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    for (const auto& edge : g.edges) {
        dist[edge.from][edge.to] = edge.weight;
        next[edge.from][edge.to] = edge.to;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Перевірка на від'ємні цикли на головній діагоналі
    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < 0) {
            cout << "\n[Флойд-Воршалл] Виявлено від'ємний цикл через вершину " << i << "\n";
            return;
        }
    }

    cout << "\n--- Результати алгоритму Флойда-Воршалла ---\n";
    cout << "Матриця найкоротших відстаней:\n    ";
    for (int i = 0; i < n; ++i) cout << setw(5) << i;
    cout << "\n-------------------------------------\n";
    for (int i = 0; i < n; ++i) {
        cout << i << " | ";
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) cout << setw(5) << "INF";
            else cout << setw(5) << dist[i][j];
        }
        cout << "\n";
    }

    // Відновлення шляху
    cout << "\nШлях між вершинами [" << source << " -> " << target << "]: ";
    if (dist[source][target] == INF) {
        cout << "шлях відсутній\n";
    } else {
        cout << "Вартість = " << dist[source][target] << ", Маршрут: " << source;
        int curr = source;
        while (curr != target) {
            curr = next[curr][target];
            if (curr == -1) break;
            cout << " -> " << curr;
        }
        cout << "\n";
    }
}

// 4. АЛГОРИТМ A* (З АНАЛІЗОМ ЕВРИСТИКИ)
double getEuclideanDistance(const Node& a, const Node& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int runAStar(const Graph& g, int start, int goal, bool useHeuristic) {
    int n = g.numVertices;
    vector<int> gScore(n, INF);
    vector<int> fScore(n, INF);
    vector<int> parent(n, -1);
    
    gScore[start] = 0;
    fScore[start] = useHeuristic ? (int)round(getEuclideanDistance(g.nodes[start], g.nodes[goal])) : 0;

    // Сховище для черги: {fScore, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> openSet;
    openSet.push({fScore[start], start});

    int steps = 0;

    while (!openSet.empty()) {
        int u = openSet.top().second;
        openSet.pop();
        steps++;

        if (u == goal) break;

        for (auto& edge : g.adjList[u]) {
            int v = edge.first;
            int w = edge.second;
            int tentative_gScore = gScore[u] + w;

            if (tentative_gScore < gScore[v]) {
                parent[v] = u;
                gScore[v] = tentative_gScore;
                int h = useHeuristic ? (int)round(getEuclideanDistance(g.nodes[v], g.nodes[goal])) : 0;
                fScore[v] = gScore[v] + h;
                openSet.push({fScore[v], v});
            }
        }
    }

    if (gScore[goal] == INF) {
        cout << " Шлях не знайдено за " << steps << " кроків.\n";
    } else {
        cout << " Довжина шляху: " << gScore[goal] << " (Виконано ітерацій/кроків: " << steps << ")\n";
        if (useHeuristic) {
            // Виведемо послідовність
            vector<int> path;
            for (int v = goal; v != -1; v = parent[v]) path.push_back(v);
            reverse(path.begin(), path.end());
            cout << "   Траєкторія A*: ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
            }
            cout << "\n";
        }
    }
    return steps;
}

// Реалізація запуску інтерактивного підменю для лабораторних 27-30
void RunHighLabs()
{
    Graph g;
    string filename = "graph.txt";

    if (!loadGraphFromFile(filename, g)) {
        cout << "Помилка! Не вдалося знайти або відкрити файл '" << filename << "'\n";
        cout << "Будь ласка, створіть текстовий файл '" << filename << "' поруч із виконуваним кодом.\n";
        return;
    }

    cout << "Граф успішно імпортовано з файлу '" << filename << "'. Кількість вершин: " << g.numVertices << ", ребер: " << g.numEdges << "\n";

    int choice = 0;
    while (true) {
        cout << "\n=============================================\n";
        cout << "     ІНТЕРАКТИВНЕ МЕНЮ (Лаб.27-30 об'єднані)\n";
        cout << "=============================================\n";
        cout << "1. Запустити Алгоритм Дейкстри\n";
        cout << "2. Запустити Алгоритм Беллмана-Форда\n";
        cout << "3. Запустити Алгоритм Флойда-Воршалла (усі пари + шлях)\n";
        cout << "4. Запустити Алгоритм A* та виконати аналіз евристики\n";
        cout << "5. Повернутись\n";

        choice = ReadIntInRange("Оберіть дію: ", 1, 5);
        if (choice == 5)
            break;

        switch (choice) {
            case 1: {
                int start = ReadIntInRange("Введіть стартову вершину (0.." + to_string(g.numVertices - 1) + "): ", 0, g.numVertices - 1);
                runDijkstra(g, start);
                WaitForEnter();
                break;
            }
            case 2: {
                int start = ReadIntInRange("Введіть стартову вершину (0.." + to_string(g.numVertices - 1) + "): ", 0, g.numVertices - 1);
                runBellmanFord(g, start);
                WaitForEnter();
                break;
            }
            case 3: {
                int source = ReadIntInRange("Введіть початкову вершину (0.." + to_string(g.numVertices - 1) + "): ", 0, g.numVertices - 1);
                int target = ReadIntInRange("Введіть цільову вершину (0.." + to_string(g.numVertices - 1) + "): ", 0, g.numVertices - 1);
                runFloydWarshall(g, source, target);
                WaitForEnter();
                break;
            }
            case 4: {
                int source = ReadIntInRange("Введіть початкову вершину (0.." + to_string(g.numVertices - 1) + "): ", 0, g.numVertices - 1);
                int target = ReadIntInRange("Введіть цільову вершину (0.." + to_string(g.numVertices - 1) + "): ", 0, g.numVertices - 1);
                cout << "\n[Аналіз ефективності евристичної функції]:\n";
                cout << "1) Робота A* з нульовою евристикою (фактично класичний Дейкстра):\n";
                runAStar(g, source, target, false);
                cout << "2) Робота A* з Евклідовою геометричною евристикою h(v):\n";
                runAStar(g, source, target, true);
                WaitForEnter();
                break;
            }
            default:
                cout << "Невірний пункт меню.\n";
                break;
        }
    }
}

void RunHighDijkstra(const AdjMatrix& graph)
{
    Graph g = ConvertAdjMatrixToGraph(graph);
    int start = ReadGraphVertex(g, "Введіть стартову вершину (0.." + to_string(g.numVertices - 1) + "): ");
    runDijkstra(g, start);
    WaitForEnter();
}

void RunHighBellmanFord(const AdjMatrix& graph)
{
    Graph g = ConvertAdjMatrixToGraph(graph);
    int start = ReadGraphVertex(g, "Введіть стартову вершину (0.." + to_string(g.numVertices - 1) + "): ");
    runBellmanFord(g, start);
    WaitForEnter();
}

void RunHighFloydWarshall(const AdjMatrix& graph)
{
    Graph g = ConvertAdjMatrixToGraph(graph);
    int source = ReadGraphVertex(g, "Введіть початкову вершину (0.." + to_string(g.numVertices - 1) + "): ");
    int target = ReadGraphVertex(g, "Введіть цільову вершину (0.." + to_string(g.numVertices - 1) + "): ");
    runFloydWarshall(g, source, target);
    WaitForEnter();
}

void RunHighAStar(const AdjMatrix& graph)
{
    Graph g = ConvertAdjMatrixToGraph(graph);
    int source = ReadGraphVertex(g, "Введіть початкову вершину (0.." + to_string(g.numVertices - 1) + "): ");
    int target = ReadGraphVertex(g, "Введіть цільову вершину (0.." + to_string(g.numVertices - 1) + "): ");
    cout << "\n[Аналіз ефективності евристичної функції]:\n";
    cout << "1) Робота A* з нульовою евристикою (фактично класичний Дейкстра):\n";
    runAStar(g, source, target, false);
    cout << "2) Робота A* з Евклідовою геометричною евристикою h(v):\n";
    runAStar(g, source, target, true);
    WaitForEnter();
}
