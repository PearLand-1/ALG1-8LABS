/* =======================================================

    Алгоритми і структура данних
    Лабораторні роботи №13-14
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include <iostream>
#include <string>

#include "mainNode.h"
#include "slist.h"
#include "dlist.h"
#include "clist.h"
#include "../MyLib.h"

using namespace std;

static void ShowHeader(const string& title, const string& subtitle)
{
    ClearScreen();
    cout << FromCustomFormatToString(
        "<magenta><i><u>" + title + "</u></i></magenta>\n"
        "<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>\n"
        "<cyan>" + subtitle + "</cyan>\n");
}

static void ShowSListState(SNode* head)
{
    SListDisplay(head);
    Log("Кількість елементів: " + to_string(SListCount(head)));
}

// ====== LAB 13 ======
static void RunLab13()
{
    SNode* head = nullptr;
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторна робота 13. Однозв'язний список",
                   "Insert, Display, пошук, видалення, реверс, підрахунок");
        ShowSListState(head);

        cout << FromCustomFormatToString(R"(
<green>Меню 13:</green>
  1 - Вставити елемент на початок
  2 - Вставити елемент в кінець
  3 - Показати список
  4 - Знайти елемент за значенням
  5 - Видалити елемент за значенням
  6 - Реверсувати список
  7 - Підрахувати кількість елементів
  8 - Очистити список
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        const int choice = ReadIntInRange("", 0, 8);

        switch (choice)
        {
        case 1:
        {
            int value = ReadInt("Введіть значення: ");
            head = SListInsertHead(head, value);
            LogSuccess("Елемент додано на початок.");
            WaitForEnter();
            break;
        }
        case 2:
        {
            int value = ReadInt("Введіть значення: ");
            head = SListInsertBack(head, value);
            LogSuccess("Елемент додано в кінець.");
            WaitForEnter();
            break;
        }
        case 3:
            WaitForEnter();
            break;
        case 4:
        {
            int value = ReadInt("Введіть значення для пошуку: ");
            const SNode* found = SListSearch(head, value);
            if (found != nullptr)
                LogSuccess("Елемент " + to_string(value) + " знайдено у списку.");
            else
                LogError("Елемент не знайдено.");
            WaitForEnter();
            break;
        }
        case 5:
        {
            int value = ReadInt("Введіть значення для видалення: ");
            const int before = SListCount(head);
            head = SListDeleteByValue(head, value);
            if (SListCount(head) < before)
                LogSuccess("Елемент видалено.");
            else
                LogError("Елемент не знайдено.");
            WaitForEnter();
            break;
        }
        case 6:
            head = SListReverse(head);
            LogSuccess("Список реверсовано.");
            WaitForEnter();
            break;
        case 7:
            Log("Кількість елементів: " + to_string(SListCount(head)));
            WaitForEnter();
            break;
        case 8:
            SListDeleteAll(head);
            LogSuccess("Список очищено.");
            WaitForEnter();
            break;
        case 0:
            SListDeleteAll(head);
            run = false;
            break;
        }
    }
}

// ====== LAB 14: двозв'язний ======
static void RunLab14Doubly()
{
    DNode* head = nullptr;
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторна 14. Двозв'язний список",
                   "Виведення вперед/назад, видалення першого елемента");
        DListDisplayForward(head);

        cout << FromCustomFormatToString(R"(
<green>Меню (двозв'язний):</green>
  1 - Додати елемент в кінець
  2 - Показати список (вперед)
  3 - Показати список (назад)
  4 - Видалити перший елемент
  5 - Очистити список
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        const int choice = ReadIntInRange("", 0, 5);

        switch (choice)
        {
        case 1:
        {
            Log("Введіть елементи двозв'язного списку (-1 — завершити):");
            while (true)
            {
                int value = ReadInt("Значення (-1 — стоп): ");
                if (value == -1)
                    break;
                head = DListInsertBack(head, value);
            }
            LogSuccess("Елементи додано.");
            WaitForEnter();
            break;
        }
        case 2:
            WaitForEnter();
            break;
        case 3:
            Log("Список у зворотному напрямку:");
            DListDisplayReverse(head);
            WaitForEnter();
            break;
        case 4:
            head = DListDeleteFirst(head);
            LogSuccess("Перший елемент видалено (якщо список не був порожнім).");
            WaitForEnter();
            break;
        case 5:
            DListDeleteAll(head);
            LogSuccess("Список очищено.");
            WaitForEnter();
            break;
        case 0:
            DListDeleteAll(head);
            run = false;
            break;
        }
    }
}

// ====== LAB 14: кільцевий ======
static void RunLab14Circular()
{
    CNode* head = nullptr;
    bool run = true;

    while (run)
    {
        ShowHeader("Лабораторна 14. Кільцевий однозв'язний список",
                   "Додавання в кінець та обхід по колу");
        CListDisplayCircular(head);

        cout << FromCustomFormatToString(R"(
<green>Меню (кільцевий):</green>
  1 - Додати елемент
  2 - Показати список (обхід)
  3 - Очистити список
  0 - Повернутися назад
<green>Оберіть опцію: </green>)");

        const int choice = ReadIntInRange("", 0, 3);

        switch (choice)
        {
        case 1:
        {
            Log("Введіть елементи; -1 — завершити введення.");
            while (true)
            {
                int value = ReadInt("Значення (-1 — стоп): ");
                if (value == -1)
                    break;
                head = CListInsertBack(head, value);
            }
            LogSuccess("Елементи додано до кільцевого списку.");
            WaitForEnter();
            break;
        }
        case 2:
            WaitForEnter();
            break;
        case 3:
            CListDeleteAll(head);
            LogSuccess("Кільцевий список повністю видалено.");
            WaitForEnter();
            break;
        case 0:
            CListDeleteAll(head);
            run = false;
            break;
        }
    }
}

static void RunLab14()
{
    bool run = true;
    while (run)
    {
        ShowHeader("Лабораторна робота 14", "Двозв'язний та кільцевий списки");
        cout << FromCustomFormatToString(R"(
<green>Оберіть тип списку:</green>
  1 - Двозв'язний список
  2 - Кільцевий однозв'язний список
  0 - Назад
<green>Ваш вибір: </green>)");

        const int choice = ReadIntInRange("", 0, 2);
        switch (choice)
        {
        case 1:
            RunLab14Doubly();
            break;
        case 2:
            RunLab14Circular();
            break;
        case 0:
            run = false;
            break;
        }
    }
}

void NodeMain()
{
    bool run = true;

    while (run)
    {
        ShowHeader("Меню лабораторних 13 - 14", "Однозв'язні, двозв'язні та кільцеві списки");
        cout << FromCustomFormatToString(R"(
<cyan>Обрати дію</cyan>

    13 - Лабораторна робота 13. Однозв'язний список
    <i>--- Insert, Display, пошук, видалення, реверс, підрахунок елементів</i>

    14 - Лабораторна робота 14. Двозв'язний і кільцевий списки
    <i>--- Виведення вперед/назад, видалення, обхід кільцевого списку</i>

    ---------------------------------------------------------
    0. Повернутися до головного меню
<green>Ваш вибір:
>> </green>)");

        const int choice = ReadInt("");

        if (choice == 13)
            RunLab13();
        else if (choice == 14)
            RunLab14();
        else if (choice == 0)
            run = false;
        else
        {
            LogError("Оберіть 13, 14 або 0.");
            WaitForEnter();
        }
    }
}
