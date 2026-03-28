/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №9-10
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <windows.h>
#include "search.h"
#include "../MyLib.h"
#include "test.h"

using namespace std;

// ====== MAIN ======
int SearchMenu()
{
    bool run = true; 
    int choice;      

    while (run)
    {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторні роботи 9 - 10</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    9 - ...
    <i>--- Лінийний пошук</i>

    10 - ...
    <i>--- Бінарний пошук</i>
    
    ---------------------------------------------------------
    0. Вихід
    
<green>Ваш вибір:
>> </green>)");
        cin >> choice;

        switch (choice)
        {
        case 1:
        case 2:
            
            break;

        // case 3:
        // {
        //     int difficulty;
        //     cout << "\n=== ВИБІР СКЛАДНОСТІ ТЕСТУ ===\n";
        //     cout << "1 - Легкий (10 елементів)\n";
        //     cout << "2 - Складний (100 елементів)\n";
        //     cout << "3 - Тяжкий (1000 елементів)\n";
        //     cout << "4 - Дуже тяжкий (10000 елементів)\n";
        //     cout << "0 - Назад\n";
        //     cout << "Ваш вибір: ";
        //     cin >> difficulty;

        //     switch (difficulty) {
        //         case 1: RunTest(10); break;
        //         case 2: RunTest(100); break;
        //         case 3: RunTest(1000); break;
        //         case 4: RunTest(10000); break;
        //         case 5: RunTest(100000); break;
        //         case 0: break;
        //         default:
        //             LogError("Невірний вибір!");
        //     }
        // }
        // break;

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