/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №11-12
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <string>
#include <vector>

#include "mainHash.h"
#include "hash.h"
#include "test.h"
#include "../MyLib.h"

using namespace std;

static int ReadHashTableSize()
{
    return ReadIntInRange("Введіть розмір хеш-таблиці [1..100000]: ", 1, 100000);
}

static void ShowHeader(const string& title, const string& subtitle)
{
    ClearScreen();
    cout << FromCustomFormatToString(
        "<magenta><i><u>" + title + "</u></i></magenta>\n"
        "<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>\n"
        "<cyan>" + subtitle + "</cyan>\n");
}

static void ShowTableState(const hashMapTable& hashTable)
{
    hashTable.DisplayTable();
    Log("   ");
    hashTable.PrintStatistics();
}

// ====== LAB 11 ======
static void RunLab11()
{
    int size = ReadHashTableSize();
    hashMapTable hashTable(size);
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторна робота 11. Хеш-таблиці",
                   "Вставка, пошук і видалення елементів");
        ShowTableState(hashTable);

        cout << FromCustomFormatToString(R"(
<green>Меню 11:</green>
  1 - Вставити або оновити елемент
  2 - Знайти елемент
  3 - Видалити елемент
  4 - Показати таблицю
  5 - Показати статистику
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        const int choice = ReadIntInRange("", 0, 5);

        switch (choice)
        {
        case 1:
        {
            int key = ReadInt("Введіть ключ: ");
            int value = ReadInt("Введіть значення: ");
            hashTable.Insert(key, value);
            LogSuccess("Елемент вставлено або оновлено.");
            WaitForEnter();
        }
            break;
        case 2:
        {
            int key = ReadInt("Введіть ключ для пошуку: ");
            int result = 0;
            if (hashTable.TryGetValue(key, result))
                LogSuccess("Знайдено значення: " + to_string(result));
            else
                LogError("Ключ не знайдено.");
            WaitForEnter();
        }
            break;
        case 3:
        {
            int key = ReadInt("Введіть ключ для видалення: ");
            if (!hashTable.Remove(key))
                LogError("Ключ не знайдено.");
            else
                LogSuccess("Ключ успішно видалено.");
            WaitForEnter();
        }
            break;
        case 4:
            hashTable.DisplayTable();
            WaitForEnter();
            break;
        case 5:
            hashTable.PrintStatistics();
            WaitForEnter();
            break;
        case 0:
            run = false;
            break;
        }
    }
}

// ====== LAB 12 ======
static void RunLab12()
{
    int size = ReadHashTableSize();
    hashMapTable hashTable(size);
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторна робота 12. Вирішення колізій",
                   "Ланцюжки у бакетах та аналіз колізій");
        ShowTableState(hashTable);

        cout << FromCustomFormatToString(R"(
<green>Меню 12:</green>
  1 - Вставити елемент
  2 - Показати колізії
  3 - Показати таблицю
  4 - Показати статистику
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        const int choice = ReadIntInRange("", 0, 4);

        switch (choice)
        {
        case 1:
        {
            int key = ReadInt("Введіть ключ: ");
            int value = ReadInt("Введіть значення: ");
            hashTable.Insert(key, value);
            LogSuccess("Елемент вставлено. Перегляньте таблицю або колізії для результату.");
            WaitForEnter();
        }
            break;
        case 2:
            hashTable.DisplayCollisions();
            WaitForEnter();
            break;
        case 3:
            hashTable.DisplayTable();
            WaitForEnter();
            break;
        case 4:
            hashTable.PrintStatistics();
            WaitForEnter();
            break;
        case 0:
            run = false;
            break;
        }
    }
}

// ====== MAIN ======
void HashMain()
{
    bool run = true;

    while (run)
    {
        ClearScreen();
        cout << FromCustomFormatToString(R"(<magenta><i><u>Меню лабораторних 11 - 12</u></i></magenta>
<cyan>Обрати дію

    1 - Лабораторна 11. Хеш-таблиці
    <i>--- Вставка, пошук, видалення з використанням хеш-таблиці.</i>

    2 - Лабораторна 12. Вирішення колізій
    <i>--- Візуалізація колізій та демонстрація ланцюгової хеш-таблиці.</i>

    3 - Автоматичні тести коректності (фіксовані дані)
    <i>--- Перевірка вставки, пошуку, оновлення, видалення та колізій.</i>

    ---------------------------------------------------------
    0. Повернутися до головного меню
    
<green>Ваш вибір:
>> </green>)");

        const int choice = ReadIntInRange("", 0, 3);

        switch (choice)
        {
        case 1:
            RunLab11();
            break;
        case 2:
            RunLab12();
            break;
        case 3:
            ClearScreen();
            RunHashCorrectnessTests();
            WaitForEnter();
            break;
        case 0:
            run = false;
            break;
        }
    }
}

