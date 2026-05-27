/* =======================================================

    Алгоритми і структура данних
    Лабораторні роботи №21-23
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <string>
#include <vector>

#include "mainGraph.h"
#include "graph.h"
#include "../MyLib.h"

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

static void LoadDemoGraph()
{
    g_graph = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0}
    };
    g_hasGraph = true;
    LogSuccess("Завантажено демонстрацiйний граф (5 вершин, з методички).");
    WaitForEnter();
}

static void InputGraphKeyboard()
{
    const int n = ReadPositiveInt("Введiть кiлькiсть вершин n: ");
    g_graph = ReadAdjMatrixKeyboard(n);
    g_hasGraph = true;
    LogSuccess("Матрицю зчитано.");
    WaitForEnter();
}

static void InputGraphFromFile()
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

static void SaveGraphToFile()
{
    if (!EnsureGraphLoaded()) return;

    cout << "Введiть iм'я файлу для запису: ";
    string path;
    cin >> path;

    if (WriteAdjMatrixToFile(path, g_graph))
        LogSuccess("Матрицю записано у файл.");
    else
        LogError("Не вдалося записати файл.");
    WaitForEnter();
}

static void InputGraphFromEdges()
{
    const int n = ReadPositiveInt("Введiть кiлькiсть вершин n: ");
    const int m = ReadIntInRange("Введiть кiлькiсть ребер: ", 0, n * n);

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
    if (!EnsureGraphLoaded()) return;

    ShowHeader("Лабораторна 21. Довiдка про граф",
               "Матриця сумiжностi та характеристики");
    PrintAdjMatrix(g_graph);
    PrintReport(g_graph);
    WaitForEnter();
}

static bool AskVisualize()
{
    cout << FromCustomFormatToString(
        "<yellow>Показувати кроки обходу?</yellow>\n"
        "  1 - так\n"
        "  2 - нi\n");
    return ReadIntInRange("Ваш вибiр: ", 1, 2) == 1;
}

static void RunTraversal(const char* title, bool useDfs)
{
    if (!EnsureGraphLoaded()) return;

    ShowHeader(title, "Обхiд графа з обраної вершини");
    PrintAdjMatrix(g_graph);

    const int n = static_cast<int>(g_graph.size());
    const int start = ReadIntInRange(
        "Початкова вершина (0.." + to_string(n - 1) + "): ", 0, n - 1);
    const bool visualize = AskVisualize();

    cout << endl;
    Log("Порядок вiдвiдування вершин:");
    cout << "  ";

    vector<bool> visited(n, false);
    if (useDfs)
        Dfs(start, g_graph, visited, visualize);
    else
        Bfs(start, g_graph, visited, visualize);

    cout << endl;

    bool allVisited = true;
    for (int i = 0; i < n; i++)
        if (!visited[i]) { allVisited = false; break; }

    if (!allVisited)
    {
        cout << endl;
        Log("Не всі вершини досяжнi з обраної — граф може бути незв'язним.");
        const AdjMatrix adj = BuildAdjList(g_graph);
        if (!IsSymmetric(g_graph))
            Log("Для орiєнтованого графа перевiрте досяжнiсть окремо.");
        else
        {
            const bool conn = IsConnectedUndirected(adj);
            cout << "Зв'язнiсть (неорiєнтований): "
                 << (conn ? "зв'язний" : "незв'язний") << endl;
        }
    }

    WaitForEnter();
}

static void RunFullBfsComponents()
{
    if (!EnsureGraphLoaded()) return;

    ShowHeader("Лабораторна 23. BFS по всіх компонентах",
               "Обхiд з кожної невiдвiданої вершини");
    PrintAdjMatrix(g_graph);

    const int n = static_cast<int>(g_graph.size());
    const bool visualize = AskVisualize();

    vector<bool> visited(n, false);
    for (int start = 0; start < n; start++)
    {
        if (!visited[start])
        {
            cout << endl;
            Log("Обхiд з вершини " + to_string(start) + ":");
            cout << "  ";
            Bfs(start, g_graph, visited, visualize);
            cout << endl;
        }
    }
    WaitForEnter();
}

void GraphMain()
{
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторні роботи 21-23. Графи",
                   "Матриця сумiжностi, DFS, BFS");

        if (g_hasGraph && !g_graph.empty())
        {
            Log("Граф завантажено: " + to_string(g_graph.size()) + " вершин.");
            PrintAdjMatrix(g_graph);
        }
        else
            Log("Граф ще не задано.");

        cout << FromCustomFormatToString(R"(
<green>Меню графів:</green>
  <b>21 — Представлення графа</b>
  1 - Ввести матрицю з клавiатури
  2 - Зчитати матрицю з файлу
  3 - Задати граф списком ребер (матриця будується автоматично)
  4 - Показати довiдку про граф
  5 - Записати матрицю у файл
  6 - Демо-граф з методички (5 вершин)

  <b>22 — Пошук у глибину (DFS)</b>
  7 - DFS з обраної вершини

  <b>23 — Пошук у ширину (BFS)</b>
  8 - BFS з обраної вершини
  9 - BFS по всіх компонентах (як у методичцi)

  0 - Повернутися в головне меню
<green>Оберіть опцію: </green>)");

        const int choice = ReadIntInRange("", 0, 9);

        switch (choice)
        {
        case 1: InputGraphKeyboard(); break;
        case 2: InputGraphFromFile(); break;
        case 3: InputGraphFromEdges(); break;
        case 4: ShowGraphInfo(); break;
        case 5: SaveGraphToFile(); break;
        case 6: LoadDemoGraph(); break;
        case 7: RunTraversal("Лабораторна 22. DFS", true); break;
        case 8: RunTraversal("Лабораторна 23. BFS", false); break;
        case 9: RunFullBfsComponents(); break;
        case 0: run = false; break;
        default: Log("Невiдома опцiя."); break;
        }
    }
}
