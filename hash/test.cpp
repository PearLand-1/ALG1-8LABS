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
        int value = 0;
        const bool found = t.TryGetValue(99, value);
        Log(FromCustomFormatToString("<cyan>Пошук ключа 99 (очікується не знайдено) → результат: " + string(found ? "found" : "not found") + "</cyan>"));
        if (!Check("Пошук у порожній таблиці повертає not found", !found))
            failed++;
        Delay();
    }

    // 2. Вставка та пошук (10 % 7 == 3)
    {
        hashMapTable t(7);
        ShowHashScene("Тест 2 / крок 1: порожня таблиця (T_S = 7)", t, false);
        t.Insert(10, 100);
        ShowHashScene("Тест 2 / крок 2: після Insert(10, 100)", t, false);
        int r = 0;
        const bool found = t.TryGetValue(10, r);
        Log(FromCustomFormatToString("<cyan>TryGetValue(10) → " + string(found ? to_string(r) : "not found") + " (очікується 100)</cyan>"));
        if (!Check("Після Insert(10, 100) — значення знайдено і дорівнює 100", found && r == 100))
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
        int r = 0;
        const bool found = t.TryGetValue(10, r);
        Log(FromCustomFormatToString("<cyan>TryGetValue(10) → " + string(found ? to_string(r) : "not found") + " (очікується 200)</cyan>"));
        if (!Check("Повторна Insert для того ж ключа оновлює значення", found && r == 200))
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
        int r = 0;
        const bool found = t.TryGetValue(3, r);
        Log(FromCustomFormatToString("<cyan>TryGetValue(3) → " + string(found ? "found" : "not found") + " (очікується not found)</cyan>"));
        if (!Check("Після Remove(3) ключ не знаходиться", !found))
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

        int v2 = 0, v7 = 0;
        bool ok = (t.TryGetValue(2, v2) && t.TryGetValue(7, v7) && v2 == 1 && v7 == 2);
        Log(FromCustomFormatToString("<cyan>SearchKey(2) і SearchKey(7) перевірено в коді тесту.</cyan>"));
        if (!Check("Колізія в бакеті — обидва ключі знаходяться окремо", ok))
            failed++;

        t.Remove(2);
        ShowHashScene("Тест 5 / крок 4: після Remove(2) — лишається ключ 7", t, true);
        int check7 = 0;
        ok = (!t.ContainsKey(2) && t.TryGetValue(7, check7) && check7 == 2);
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

        int v3 = 0, v6 = 0, v9 = 0;
        bool ok = (t.TryGetValue(3, v3) && t.TryGetValue(6, v6) && t.TryGetValue(9, v9)
                    && v3 == 30 && v6 == 60 && v9 == 90);
        if (!Check("Три елементи в одному бакеті — пошук кожного", ok))
            failed++;

        t.Remove(6);
        ShowHashScene("Тест 6 / крок 5: після Remove(6) — «середній» у ланцюжку", t, true);
        ok = (!t.ContainsKey(6) && t.TryGetValue(3, v3) && t.TryGetValue(9, v9)
              && v3 == 30 && v9 == 90);
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

        int r = 0;
        const bool found = t.TryGetValue(3, r);
        Log(FromCustomFormatToString("<cyan>Пошук неіснуючого ключа 3 → " + string(found ? "found" : "not found") + " (очікується not found)</cyan>"));
        if (!Check("Пошук неіснуючого ключа 3 повертає not found", !found))
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
