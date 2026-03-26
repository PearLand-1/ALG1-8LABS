/* =======================================================

    Алгоритми і структура данних
    Лабораторні роботи
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */
#include "sort/mainSort.h"
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
        Log("Майбутнє крутезне меню");
        cin >> choice;
        switch(choice) {
            case 1:
                SortMenu();
                break;
            default:
                Log("Щось не те, пробуй ще");
        }
    }
    return 0;
}