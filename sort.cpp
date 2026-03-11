/* ======================================================= 

    Алгоритми і структура данних
    Лабораторна робота №1-8
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "sort.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// ===== КОЛЬОРИ =====
string colors[] = {
    "\033[1;31m", "\033[1;32m", "\033[1;33m",
    "\033[1;34m", "\033[1;35m", "\033[1;36m",
    "\033[1;91m", "\033[1;92m", "\033[1;93m"
};

string resetColor = "\033[0m";
string highlight = "\033[41m";
string menuColor = "\033[96m"; 
int visualizationDelay = 300;  

// ===== ЛОГИ =====
void Log(string item) { cout << resetColor << item << resetColor << endl; }
void LogSuccess(string item) { cout << "\033[42m" << item << resetColor << endl; }
void LogError(string item) { cout << "\033[41m" << item << resetColor << endl; }
void Delay() { std::this_thread::sleep_for(std::chrono::milliseconds(visualizationDelay)); }

// ===== ВІЗУАЛІЗАЦІЯ =====
void ClearScreen() { cout << "\033[2J\033[1;1H"; }

void PrintArray(vector<int>& a, int idx1, int idx2)
{
    cout << "\033[?25l";  
    cout << "\033[2J\033[1;1H";
    for (int i = 0; i < a.size(); i++)
    {
        if (i == idx1 || i == idx2) cout << highlight;
        cout << colors[i % 9] << setw(4) << a[i] << resetColor << " ";
    }
    cout << endl;
    Delay();
    cout << "\033[?25h";
}


// =================== ВВЕДЕННЯ ===================
vector<int> InputArray()
{
    int n;

    cout << "\nВведення масиву вручну\n";
    cout << "------------------------\n";

    cout << "Розмір масиву (кількість елементів): ";
    cin >> n;

    while (n <= 0)
    {
        cout << "Розмір повинен бути більше 0. Спробуйте ще раз: ";
        cin >> n;
    }

    vector<int> arr(n);

    cout << "\nТепер введіть " << n << " цілих чисел.\n";
    cout << "Вводити потрібно В ОДИН РЯДОК через пробіл.\n";
    cout << "Приклад: 5 2 -3 10 8\n\n";
    cout << "Ваш ввод: ";

    for (int i = 0; i < n; i++)
    {
        while (!(cin >> arr[i]))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Введіть ЦІЛЕ число: ";
        }
    }

    cout << "\nМасив успішно зчитано!\n";

    return arr;
}

vector<int> RandomArray()
{
    int n, minVal, maxVal;
    cout << "Розмір масиву: ";
    cin >> n;
    cout << "Мінімальне значення: ";
    cin >> minVal;
    cout << "Максимальне значення: ";
    cin >> maxVal;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);

    return arr;
}

// ===== SELECTION SORT =====
void SelectionSort(vector<int> a, bool visualize, bool ascending)
{
    int n = a.size();

    for (int j = n - 1; j > 0; j--)
    {
        int idx = 0;

        for (int i = 1; i <= j; i++)
        {
            if ((ascending && a[i] > a[idx]) ||
                (!ascending && a[i] < a[idx]))
                idx = i;

            if (visualize)
            {
                Log("Пошук максимуму...");
                PrintArray(a, i, idx);
            }
        }

        if (idx != j) {
            swap(a[idx], a[j]);
            if (visualize)
            {
                Log("Обмін:");
                PrintArray(a, idx, j);
            }
        } else {
            if (visualize) {
                Log("Без змін (обміну не було):");
                PrintArray(a);
            }
        }
    }

    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== INSERTION SORT =====
void InsertionSort(vector<int> a, bool visualize, bool ascending)
{
    int n = a.size();

    for (int j = 1; j < n; j++)
    {
        int key = a[j];
        int i = j - 1;

        bool swapped = false; 

        while (i >= 0 && 
            ((ascending && a[i] > key) ||
            (!ascending && a[i] < key)))
        {
            a[i + 1] = a[i];
            i--;
            swapped = true;

            if (visualize)
            {
                Log("Зсув елементів...");
                PrintArray(a, i, j);
            }
        }

        a[i + 1] = key;

        if (visualize)
        {
            Log("Вставка:");
            PrintArray(a, i + 1, j);
        }

        if (!swapped && visualize) {
            Log("Без змін (зсувів не було):");
            PrintArray(a);
        }
    }

    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== BUBBLE SORT =====
void BubbleSort(vector<int> a, bool visualize, bool ascending)
{
    int n = a.size();

    for (int j = 0; j < n - 1; j++)
    {
        bool swapped = false;

        for (int i = 0; i < n - j - 1; i++)
        {
            if ((ascending && a[i] > a[i + 1]) ||
                (!ascending && a[i] < a[i + 1]))
            {
                swap(a[i], a[i + 1]);
                swapped = true;

                if (visualize)
                {
                    Log("Обмін сусідніх:");
                    PrintArray(a, i, i + 1);
                }
            }
        }

        if (!swapped && visualize)
        {
            Log("Без змін (обміну не було):");
            PrintArray(a);
        }

        if (!swapped)
            break;
    }

    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== MERGE SORT =====
void Merge(vector<int>& a, int left, int mid, int right, bool visualize, bool ascending)
{
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if ((ascending && a[i] < a[j]) ||
            (!ascending && a[i] > a[j]))
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);

        if (visualize)
            PrintArray(a, i, j);
    }

    while (i <= mid) temp.push_back(a[i++]);
    while (j <= right) temp.push_back(a[j++]);

    for (int k = 0; k < temp.size(); k++)
        a[left + k] = temp[k];

    // Візуалізація після кожного злиття
    if (visualize)
        PrintArray(a);
}

void MergeSortRec(vector<int>& a, int left, int right, bool visualize, bool ascending)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    MergeSortRec(a, left, mid, visualize, ascending);
    MergeSortRec(a, mid + 1, right, visualize, ascending);
    Merge(a, left, mid, right, visualize, ascending);
}

void MergeSort(vector<int> a, bool visualize, bool ascending)
{
    MergeSortRec(a, 0, a.size() - 1, visualize, ascending);
    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== QUICK SORT =====
int Partition(vector<int>& a, int low, int high, bool visualize, bool ascending)
{
    int pivot = a[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if ((ascending && a[j] < pivot) || (!ascending && a[j] > pivot)) {
            i++;
            swap(a[i], a[j]);
            if (visualize) {
                Log("Обмін:");
                PrintArray(a, i, j);
            }
        }
    }
    swap(a[i + 1], a[high]);
    if (visualize) {
        Log("Опорний елемент на місці:");
        PrintArray(a, i + 1, high);
    }
    return i + 1;
}

void QuickSortRec(vector<int>& a, int low, int high, bool visualize, bool ascending)
{
    if (low < high) {
        int pi = Partition(a, low, high, visualize, ascending);
        QuickSortRec(a, low, pi - 1, visualize, ascending);
        QuickSortRec(a, pi + 1, high, visualize, ascending);
    }
}

void QuickSort(vector<int> a, bool visualize, bool ascending)
{
    QuickSortRec(a, 0, a.size() - 1, visualize, ascending);
    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== SHELL SORT =====
void ShellSort(vector<int> a, bool visualize, bool ascending)
{
    int n = a.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            
            for (j = i; j >= gap && ((ascending && a[j - gap] > temp) || (!ascending && a[j - gap] < temp)); j -= gap) {
                a[j] = a[j - gap];
                if (visualize) {
                    Log("Зсув з кроком " + to_string(gap));
                    PrintArray(a, j - gap, j);
                }
            }
            a[j] = temp;
            
            if (visualize && j != i) {
                Log("Вставка:");
                PrintArray(a, j, i);
            }
        }
    }
    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== SHAKER SORT =====
void ShakerSort(vector<int> a, bool visualize, bool ascending)
{
    int n = a.size();
    int left = 0, right = n - 1;
    bool swapped;
    
    do {
        swapped = false;
        
        // Прохід зліва направо
        for (int i = left; i < right; i++) {
            if ((ascending && a[i] > a[i + 1]) || (!ascending && a[i] < a[i + 1])) {
                swap(a[i], a[i + 1]);
                swapped = true;
                if (visualize) {
                    Log("Обмін (←→):");
                    PrintArray(a, i, i + 1);
                }
            }
        }
        right--;
        
        if (!swapped) break;
        swapped = false;
        
        // Прохід справа наліво
        for (int i = right; i > left; i--) {
            if ((ascending && a[i - 1] > a[i]) || (!ascending && a[i - 1] < a[i])) {
                swap(a[i - 1], a[i]);
                swapped = true;
                if (visualize) {
                    Log("Обмін (→←):");
                    PrintArray(a, i - 1, i);
                }
            }
        }
        left++;
    } while (swapped);
    
    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== HEAP SORT =====
void Heapify(vector<int>& a, int n, int i, bool visualize, bool ascending)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // Порівнюємо з лівим дочірнім вузлом
    if (left < n && ((ascending && a[left] > a[largest]) || (!ascending && a[left] < a[largest])))
        largest = left;
    
    // Порівнюємо з правим дочірнім вузлом
    if (right < n && ((ascending && a[right] > a[largest]) || (!ascending && a[right] < a[largest])))
        largest = right;
    
    // Якщо найбільший елемент не є поточним
    if (largest != i) {
        swap(a[i], a[largest]);
        if (visualize) {
            Log("Обмін у купі:");
            PrintArray(a, i, largest);
        }
        // Рекурсивно відновлюємо купу
        Heapify(a, n, largest, visualize, ascending);
    }
}

void HeapSort(vector<int> a, bool visualize, bool ascending)
{
    int n = a.size();
    
    // Будуємо максимальну (або мінімальну) купу
    for (int i = n / 2 - 1; i >= 0; i--) {
        if (visualize) {
            Log("Побудова купи:");
            PrintArray(a);
        }
        Heapify(a, n, i, visualize, ascending);
    }
    
    // Витягуємо елементи з купи один за одним
    for (int i = n - 1; i > 0; i--) {
        // Переміщуємо поточний корінь (найбільший елемент) на край
        swap(a[0], a[i]);
        if (visualize) {
            Log("Переміщення коренів купи:");
            PrintArray(a, 0, i);
        }
        // Відновлюємо купу для скороченого масиву
        Heapify(a, i, 0, visualize, ascending);
    }
    
    LogSuccess("Відсортовано:");
    PrintArray(a);
}

// ===== МЕНЮ =====

void RunAlgorithm(int type)
{
    bool visualize;
    cout << "Візуалізувати? (1 - так, 0 - ні): ";
    cin >> visualize;
    
    if (visualize)
    {
        cout << "Затримка (мс, рекомендовано 100-1000): ";
        cin >> visualizationDelay;
    }

    int orderChoice;
    cout << "\nПорядок сортування:\n";
    cout << "1 - За зростанням\n";
    cout << "2 - За спаданням\n";
    cout << "Ваш вибір: ";
    cin >> orderChoice;

    bool ascending = (orderChoice == 1);

    int inputType;
    cout << "\n1 - Ввести вручну\n2 - Випадкові значення\nВаш вибір: ";
    cin >> inputType;

    vector<int> arr;

    if (inputType == 1)
        arr = InputArray();
    else
        arr = RandomArray();

    Log("Початковий масив:");
    PrintArray(arr);

    switch (type)
    {
    case 1: SelectionSort(arr, visualize, ascending); break;
    case 2: InsertionSort(arr, visualize, ascending); break;
    case 3: BubbleSort(arr, visualize, ascending); break;
    case 4: MergeSort(arr, visualize, ascending); break;
    case 5: QuickSort(arr, visualize, ascending); break;
    case 6: ShellSort(arr, visualize, ascending); break;
    case 7: ShakerSort(arr, visualize, ascending); break;
    case 8: HeapSort(arr, visualize, ascending); break;
    }
}