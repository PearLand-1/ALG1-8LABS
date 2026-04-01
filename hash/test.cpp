/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №11-12 — тести коректності
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "hash.h"
#include "../MyLib.h"
#include "test.h"

#include <string>

using namespace std;

static bool Check(const string& name, bool ok)
{
    if (ok)
    {
        LogSuccess("[OK] " + name);
        return true;
    }
    LogError("[FAIL] " + name);
    return false;
}

// Показ стану таблиці між кроками (як у інтерактивних лабораторних)
static void ShowHashScene(const string& title, const hashMapTable& t, bool showCollisions = false)
{
    ClearScreen();
    Log(FromCustomFormatToString("<magenta><b>" + title + "</b></magenta>"));
    t.DisplayTable();
    Log(" ");
    t.PrintStatistics();
    if (showCollisions)
    {
        Log(FromCustomFormatToString("<cyan>Колізії (ланцюжки з кількістю елементів > 1):</cyan>"));
        t.DisplayCollisions();
    }
    Delay();
}

void RunHashCorrectnessTests()
{
    const int savedDelay = visualizationDelay;
    visualizationDelay = 350;

    Log(FromCustomFormatToString(
        "<cyan>=== Автоматичні тести хеш-таблиці (фіксовані дані) ===\n"
        "Покрокова візуалізація: таблиця та статистика після кожної дії.</cyan>"));
    Delay();

    int failed = 0;

    // 1. Порожня таблиця
    {
        hashMapTable t(11);
        ShowHashScene("Тест 1 / крок 1: порожня таблиця (T_S = 11)", t, false);
        int r = t.SearchKey(99);
        Log(FromCustomFormatToString("<cyan>Пошук ключа 99 (очікується -1) → результат: " + to_string(r) + "</cyan>"));
        if (!Check("Пошук у порожній таблиці повертає -1", r == -1))
            failed++;
        Delay();
    }

    // 2. Вставка та пошук (10 % 7 == 3)
    {
        hashMapTable t(7);
        ShowHashScene("Тест 2 / крок 1: порожня таблиця (T_S = 7)", t, false);
        t.Insert(10, 100);
        ShowHashScene("Тест 2 / крок 2: після Insert(10, 100)", t, false);
        int r = t.SearchKey(10);
        Log(FromCustomFormatToString("<cyan>SearchKey(10) → " + to_string(r) + " (очікується 100)</cyan>"));
        if (!Check("Після Insert(10, 100) — SearchKey(10) == 100", r == 100))
            failed++;
        Delay();
    }

    // 3. Оновлення значення за тим самим ключем
    {
        hashMapTable t(7);
        ShowHashScene("Тест 3 / крок 1: порожня таблиця (T_S = 7)", t, false);
        t.Insert(10, 100);
        ShowHashScene("Тест 3 / крок 2: після Insert(10, 100)", t, false);
        t.Insert(10, 200);
        ShowHashScene("Тест 3 / крок 3: після Insert(10, 200) — оновлення того ж ключа", t, false);
        int r = t.SearchKey(10);
        Log(FromCustomFormatToString("<cyan>SearchKey(10) → " + to_string(r) + " (очікується 200)</cyan>"));
        if (!Check("Повторна Insert для того ж ключа оновлює значення", r == 200))
            failed++;
        Delay();
    }

    // 4. Видалення
    {
        hashMapTable t(7);
        ShowHashScene("Тест 4 / крок 1: порожня таблиця (T_S = 7)", t, false);
        t.Insert(3, 30);
        ShowHashScene("Тест 4 / крок 2: після Insert(3, 30)", t, false);
        t.Remove(3);
        ShowHashScene("Тест 4 / крок 3: після Remove(3)", t, false);
        int r = t.SearchKey(3);
        Log(FromCustomFormatToString("<cyan>SearchKey(3) → " + to_string(r) + " (очікується -1)</cyan>"));
        if (!Check("Після Remove(3) ключ не знаходиться", r == -1))
            failed++;
        Delay();
    }

    // 5. Колізія: розмір 5, ключі 2 та 7 → індекс 2
    {
        hashMapTable t(5);
        ShowHashScene("Тест 5 / крок 1: порожня таблиця (T_S = 5)", t, false);
        t.Insert(2, 1);
        ShowHashScene("Тест 5 / крок 2: після Insert(2, 1)", t, false);
        t.Insert(7, 2);
        ShowHashScene("Тест 5 / крок 3: після Insert(7, 2) — колізія в бакеті [2]", t, true);

        bool ok = (t.SearchKey(2) == 1 && t.SearchKey(7) == 2);
        Log(FromCustomFormatToString("<cyan>SearchKey(2) і SearchKey(7) перевірено в коді тесту.</cyan>"));
        if (!Check("Колізія в бакеті — обидва ключі знаходяться окремо", ok))
            failed++;

        t.Remove(2);
        ShowHashScene("Тест 5 / крок 4: після Remove(2) — лишається ключ 7", t, true);
        ok = (t.SearchKey(2) == -1 && t.SearchKey(7) == 2);
        if (!Check("Після видалення одного ключа інший у колізії лишається", ok))
            failed++;
        Delay();
    }

    // 6. Три ключі в одному ланцюжку (усі % 3 == 0)
    {
        hashMapTable t(3);
        ShowHashScene("Тест 6 / крок 1: порожня таблиця (T_S = 3)", t, false);
        t.Insert(3, 30);
        ShowHashScene("Тест 6 / крок 2: після Insert(3, 30)", t, true);
        t.Insert(6, 60);
        ShowHashScene("Тест 6 / крок 3: після Insert(6, 60)", t, true);
        t.Insert(9, 90);
        ShowHashScene("Тест 6 / крок 4: після Insert(9, 90) — три елементи в одному бакеті", t, true);

        bool ok = (t.SearchKey(3) == 30 && t.SearchKey(6) == 60 && t.SearchKey(9) == 90);
        if (!Check("Три елементи в одному бакеті — пошук кожного", ok))
            failed++;

        t.Remove(6);
        ShowHashScene("Тест 6 / крок 5: після Remove(6) — «середній» у ланцюжку", t, true);
        ok = (t.SearchKey(6) == -1 && t.SearchKey(3) == 30 && t.SearchKey(9) == 90);
        if (!Check("Видалення середнього елемента в ланцюжку", ok))
            failed++;
        Delay();
    }

    // 7. Відсутній ключ при наявних колізіях у бакеті
    {
        hashMapTable t(5);
        ShowHashScene("Тест 7 / крок 1: порожня таблиця (T_S = 5)", t, false);
        t.Insert(12, 111);
        ShowHashScene("Тест 7 / крок 2: після Insert(12, 111)", t, false);
        t.Insert(7, 222);
        ShowHashScene("Тест 7 / крок 3: після Insert(7, 222) — колізія в бакеті [2]", t, true);

        int r = t.SearchKey(3);
        Log(FromCustomFormatToString("<cyan>Пошук неіснуючого ключа 3 → " + to_string(r) + " (очікується -1)</cyan>"));
        if (!Check("Пошук неіснуючого ключа 3 повертає -1", r == -1))
            failed++;
        Delay();
    }

    visualizationDelay = savedDelay;

    ClearScreen();
    if (failed == 0)
        LogSuccess("Підсумок: усі перевірки пройдено успішно.");
    else
        LogError("Підсумок: не пройдено перевірок: " + to_string(failed));
}
