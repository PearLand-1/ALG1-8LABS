/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №9-10
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */
#include "../MyLib.h"
#include "../sort/sort.h"

#include "iostream"
#include "search.h"
#include "test.h"
#include "math.h"

using namespace std;

// ===== LINEAR SEARCH =====
bool LinearSearch(vector<int> &arr, int target, bool visualize)
{
    vector<int> a = arr;
    for (int i = 0; i < a.size(); ++i)
    {
        if (visualize)
        {
            Log("Перевірка елементу: ");
            PrintArray(a, i, -1);
        }
        if (a[i] == target)
        {
            LogSuccess("Індекс знайденого елемента: " + to_string(i));
            return true;
        }
    }

    return false;
}

// ===== BINARY SEARCH =====
bool BinarySearch(vector<int> &arr, int target, bool visualize)
{
    vector<int> a = arr;
    HeapSort(a, false, true);

    int left = 0;
    int right = a.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (visualize)
        {
            Log("Індекс середнього елемента: " + to_string(mid));
            PrintArray(a, mid, -1);
        }
        if (a[mid] == target)
        {
            if (visualize) LogSuccess("Індекс знайденого елемента: " + to_string(mid));
            return true;
        }
        if (a[mid] < target)
        {
            if (visualize) Log("Шукаємо праворуч");
            left = mid + 1;
        }
        else
        {
            if (visualize) Log("Шукаємо ліворуч");
            right = mid - 1;
        }
    }
    return false;
}

// ===== JUMP SEARCH =====
bool JumpSearch(vector<int> &arr, int target, bool visualize)
{
    vector<int> a = arr;
    QuickSort(a, false, true);

    int n = a.size();
    int step = sqrt(n);
    int prev = 0;

    while (a[min(step, n) - 1] < target)
    {
        Log("Перевірка елементу: " + to_string(min(step, n) - 1));
        PrintArray(a, min(step, n) - 1, -1);
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return false;
    }

    while (a[prev] < target)
    {
        Log("Перевірка елементу: " + to_string(prev));
        PrintArray(a, prev, -1);
        prev++;
        if (prev == min(step, n))
            return false;
    }

    if (a[prev] == target)
    {
        LogSuccess("Індекс знайденого елемента: " + to_string(prev));
        return true;
    }

    return false;
}

void RunSearch(short item)
{
    bool visualize;
    Log("Візуалізувати? 1 - так, 0 - ні\n>> ");
    cin >> visualize;

    if (visualize)
    {
        Log("Затримка (мс, рекомендовано 100-1000)\n>> ");
        cin >> visualizationDelay;
    }

    int inputType;
    Log("Створення масиву:\n1 - Ввести вручну\n2 - Випадкові значення\n>> ");
    cin >> inputType;

    vector<int> arr;

    if (inputType == 1)
        arr = InputArray();
    else
        arr = RandomArray();

    int _visualizationDelay = visualizationDelay;
    visualizationDelay = 0;
    Log("Масив для пошуку: ");
    PrintArray(arr, -1, -1);
    visualizationDelay = _visualizationDelay;

    int target;
    Log("Введіть значення елемента, якого ви хочете знайти.(int)\n>> ");
    cin >> target;

    bool result;

    switch (item)
    {
    case 9:
        result = LinearSearch(arr, target, visualize);
        if (!result)
        {
            LogError("Елемент не знайдено в масиві");
        }
        break;
    case 10:
        result = BinarySearch(arr, target, visualize);
        if (!result)
        {
            LogError("Елемент не знайдено в масиві");
        }
        break;
    case 1:

        result = JumpSearch(arr, target, visualize);
        if (!result)
        {
            LogError("Елемент не знайдено в масиві");
        }
        break;
    }

    return;
}