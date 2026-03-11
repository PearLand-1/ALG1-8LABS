/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №1-8
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <windows.h>
#include "sort.h"
#include "test.h"

using namespace std;

// ====== MAIN ======
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(time(NULL)); 

    bool run = true; 
    int choice;      

    while (run)
    {
        cout << menuColor
             << "\n=== МЕНЮ СОРТУВАННЯ ===\n"
             << "1 - Selection Sort\n"
             << "2 - Insertion Sort\n"
             << "3 - Bubble Sort\n"
             << "4 - Merge Sort\n"
             << "5 - Quick Sort\n"
             << "6 - Shell Sort\n"
             << "7 - Shaker Sort\n"
             << "8 - Heap Sort\n"
             << "9 - Тестувати всі сортування (виміряти час)\n"
             << "0 - Вихiд\n"
             << "Ваш вибiр: "
             << resetColor;
        cin >> choice;

        switch (choice)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            RunAlgorithm(choice);
            break;

        case 9:
        {
            int difficulty;
            cout << "\n=== ВИБІР СКЛАДНОСТІ ТЕСТУ ===\n";
            cout << "1 - Легкий (10 елементів)\n";
            cout << "2 - Складний (100 елементів)\n";
            cout << "3 - Тяжкий (1000 елементів)\n";
            cout << "4 - Дуже тяжкий (10000 елементів)\n";
            cout << "0 - Назад\n";
            cout << "Ваш вибір: ";
            cin >> difficulty;

            switch (difficulty) {
                case 1: RunTest(10); break;
                case 2: RunTest(100); break;
                case 3: RunTest(1000); break;
                case 4: RunTest(10000); break;
                case 0: break;
                default:
                    LogError("Невірний вибір!");
            }
        }
        break;

        case 0:
            run = false; 
            break;


        default:
            LogError("Невірний вибір!"); 
        }
    }

    return 0;
}