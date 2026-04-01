/* =======================================================

    Алгоритми і структура данних
    Лабораторні роботи
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */
#include "sort/mainSort.h"
#include "search/mainSearch.h"
#include "hash/mainHash.h"
#include "MyLib.h"

#include <windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(time(NULL));

    bool run = true; 
    int choice;      

    while (run) {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторні роботи з алгоритмів і структури данних</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    1. Відкрити меню лабораторних робіт 1-8.
    <i>--- Різні методи сортування масивів</i>

    2. Відкрити меню лаболаторної 9 - 10
    <i>--- Різні методи пошуку елементу в масиві</i>

    3. Відкрити меню лабораторних 11 - 12
    <i>--- Хеш-таблиці і вирішення колізій</i>
    
    ---------------------------------------------------------
    0. Вихід
    
<green>Ваш вибір:
>> </green>)");
        cin >> choice;
        switch(choice) {
            case 1:
                SortMenu();
                break;
            case 2:
                SearchMenu();
                break;
            case 3:
                HashMain();
                break;
            case 0:
                run = false;
                break;
            default:
                Log("Щось не те, пробуй ще");
        }
    }
    return 0;
}