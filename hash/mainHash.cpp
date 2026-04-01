/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №11-12
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <limits>
#include <string>

#include "mainHash.h"
#include "hash.h"
#include "test.h"
#include "../MyLib.h"

using namespace std;

// ====== LAB 11 ======
static void RunLab11()
{
    int size = ReadPositiveInt("Введіть розмір хеш-таблиці: ");
    hashMapTable hashTable(size);
    bool run = true;
    short choice;

    while (run)
    {
        ClearScreen();
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторна 11. Хеш-таблиці</u></i></magenta>
<cyan>Використовуйте меню для вставки, пошуку та видалення елементів.</cyan>)") << "\n";
        hashTable.DisplayTable();
        Log("   ");
        hashTable.PrintStatistics();

        cout << FromCustomFormatToString(R"(
<green>Меню 11:</green>
  1 - Вставити або оновити елемент
  2 - Знайти елемент
  3 - Видалити елемент
  4 - Показати таблицю
  5 - Показати статистику
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            LogError("Неправильний ввід. Введіть число з меню.");
            WaitForEnter();
            continue;
        }

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
            int result = hashTable.SearchKey(key);
            if (result != -1)
                LogSuccess("Знайдено значення: " + to_string(result));
            else
                LogError("Ключ не знайдено.");
            WaitForEnter();
        }
            break;
        case 3:
        {
            int key = ReadInt("Введіть ключ для видалення: ");
            int value = hashTable.SearchKey(key);
            if (value == -1)
                LogError("Ключ не знайдено.");
            else
            {
                hashTable.Remove(key);
                LogSuccess("Ключ успішно видалено.");
            }
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
        default:
            LogError("Неправильний вибір. Спробуйте ще раз.");
            WaitForEnter();
            break;
        }
    }
}

// ====== LAB 12 ======
static void RunLab12()
{
    int size = ReadPositiveInt("Введіть розмір хеш-таблиці: ");
    hashMapTable hashTable(size);
    bool run = true;
    short choice;

    while (run)
    {
        ClearScreen();
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторна 12. Вирішення колізій</u></i></magenta>
<cyan>Колізії вирішуються за допомогою ланцюжків у бакетах.</cyan>)") << "\n";
        hashTable.DisplayTable();
        Log("   ");
        hashTable.PrintStatistics();

        cout << FromCustomFormatToString(R"(
<green>Меню 12:</green>
  1 - Вставити елемент
  2 - Показати колізії
  3 - Показати таблицю
  4 - Показати статистику
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            LogError("Неправильний ввід. Введіть число з меню.");
            WaitForEnter();
            continue;
        }

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
        default:
            LogError("Неправильний вибір. Спробуйте ще раз.");
            WaitForEnter();
            break;
        }
    }
}

// ====== MAIN ======
void HashMain()
{
    short choice;
    bool run = true;

    while (run)
    {
        ClearScreen();
        cout << FromCustomFormatToString(R"(<magenta><i><u>Меню лабораторних 11 - 12</u></i></magenta>
<cyan>Обрати дію</cyan>

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

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            LogError("Неправильний ввід. Введіть число з меню.");
            WaitForEnter();
            continue;
        }

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
        default:
            LogError("Неправильний вибір. Спробуйте ще раз.");
            WaitForEnter();
            break;
        }
    }
}

