/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №1-8
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <windows.h>
#include "sort.h"
#include "../MyLib.h"
#include "test.h"

using namespace std;

// ====== MAIN ======
int SortMenu()
{
    bool run = true; 
    int choice;      

    while (run)
    {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторні роботи 1 - 8</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    1 - Selection Sort
    <i>--- Сортування вибором</i>

    2 - Insertion Sort
    <i>--- Сортування включенням</i>

    3 - Bubble Sort
    <i>--- Сортування бульбашкою</i>

    4 - Merge Sort
    <i>--- Сортування злиттям</i>

    5 - Quick Sort
    <i>--- Швидке сортування</i>

    6 - Shell Sort
    <i>--- Сортування Шелла</i>

    7 - Shaker Sort
    <i>--- Шейкерне сортування</i>

    8 - Heap Sort
    <i>--- Сортування купою</i>

    9 - Тестувати всі сортування
    <i>--- Виміряти час</i>
    
    ---------------------------------------------------------
    0. Вихід
    
<green>Ваш вибір:
>> </green>)");
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
                case 5: RunTest(100000); break;
                case 0: break;
                default:
                    LogError("Невірний вибір!");
            }
        }
        break;

        case 0:
            run = false;
            Log("Повернення");
            break;
        default:
            LogError("Невірний вибір!"); 
        }
    }

    return 0;
}