// Self-contained utility functions for logging and visualization timing.

#include "MyLib.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <regex>
#include <vector>

using namespace std;

string resetColor = "\033[0m";
int visualizationDelay = 300;

/*
    Опис: Функція FromCustomFormatToString перетворює ANSI-коди форматування
    у зручні HTML-подібні теги для легшого читання та стилізації тексту.

    Підтримувані теги:
    - <b> ... </b>          : жирний текст
    - <i> ... </i>          : курсив
    - <u> ... </u>          : підкреслений текст
    - <red> ... </red>      : червоний текст
    - <green> ... </green>  : зелений текст
    - <yellow> ... </yellow>: жовтий текст
    - <blue> ... </blue>    : синій текст
    - <magenta> ... </magenta>: фіолетовий текст
    - <cyan> ... </cyan>    : бірюзовий текст
    - <white> ... </white>  : білий текст
    - --- -> ——             : перетворення 3 - на 2 —
    Вхідні дані: string
    Вихідні дані: string
    Приклад виконання:
        FromCustomFormatToString("<b>bold</b>") -> "\033\\[1mbold\033\\[22m"
*/
string FromCustomFormatToString(string item) {
    // Стилі
    item = regex_replace(item, regex("<b>"), "\x1b[1m");
    item = regex_replace(item, regex("</b>"), "\x1b[22m");

    item = regex_replace(item, regex("<i>"), "\x1b[3m");
    item = regex_replace(item, regex("</i>"), "\x1b[23m");

    item = regex_replace(item, regex("<u>"), "\x1b[4m");
    item = regex_replace(item, regex("</u>"), "\x1b[24m");

    // Кольори
    item = regex_replace(item, regex("<red>"), "\x1b[31m");
    item = regex_replace(item, regex("<green>"), "\x1b[32m");
    item = regex_replace(item, regex("<yellow>"), "\x1b[33m");
    item = regex_replace(item, regex("<blue>"), "\x1b[34m");
    item = regex_replace(item, regex("<magenta>"), "\x1b[35m");
    item = regex_replace(item, regex("<cyan>"), "\x1b[36m");
    item = regex_replace(item, regex("<white>"), "\x1b[37m");
    item = regex_replace(item, regex("---"), "——");

    // Закриття кольорів і скидання стилів
    item = regex_replace(item, regex("</red>|</green>|</yellow>|</blue>|</magenta>|</cyan>|</white>"), "\x1b[39m");
    item = regex_replace(item, regex("</b>|</i>|</u>"), "\x1b[0m"); // reset стилів

    return item;
}

void Log(const string& item) { cout << FromCustomFormatToString("<cyan>" + item + "</cyan>") << endl; }
void LogSuccess(const string& item) { cout << FromCustomFormatToString("<green>" + item + "</green>") << endl; }
void LogError(const string& item) { cout << FromCustomFormatToString("<red>" + item + "</red>") << endl; }

void Delay() { this_thread::sleep_for(std::chrono::milliseconds(visualizationDelay)); }

void ClearScreen() { cout << "\033[2J\033[1;1H"; }

// ===== КОЛЬОРИ =====
string colors[] = {
    "\033[1;31m", "\033[1;32m", "\033[1;33m",
    "\033[1;34m", "\033[1;35m", "\033[1;36m",
    "\033[1;91m", "\033[1;92m", "\033[1;93m"
};

string highlight = "\033[41m";
string menuColor = "\033[96m"; 

void PrintArray(vector<int>& a, int idx1, int idx2)
{
    cout << "\033[?25l";  
    cout << "\033[2J\033[1;1H";
    for (int i = 0; i < a.size(); i++)
    {
        if (i == idx1 || i == idx2) cout << highlight;
        cout << colors[i % 9] << setw(4) << a[i] << resetColor << " ";
    }
    cout << endl;
    Delay();
    cout << "\033[?25h";
}


// =================== ВВЕДЕННЯ ===================
vector<int> InputArray()
{
    int n;

    cout << FromCustomFormatToString(R"(<magenta><i><u>Поле для введення масиву</u></i></magenta>
<cyan>Введіть розмір масиву
>> )");
    cin >> n;

    while (n <= 0)
    {
        LogError("Розмір масиву потрібнен бути більше 0. Спробуйте ще.");
        cin >> n;
    }

    vector<int> arr(n);

    cout << FromCustomFormatToString(format(R"(<cyan>Тепер введіть <green>{} <cyan>цілих чисел.
Потрібно ввести <u>В ОДИН РЯДОК</u> через пробіл.
<i>Приклад</i>: 5 2 -3 10 8
Ваш ввід:
>> )", n));

    for (int i = 0; i < n; i++)
    {
        while (!(cin >> arr[i]))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            LogError("Помилка! Введіть ЦІЛЕ число: ");
        }
    }

    LogSuccess("\nМасив успішно зчитано!\n");

    return arr;
}

vector<int> RandomArray()
{
    int n, minVal, maxVal;
    cout << FromCustomFormatToString("<cyan>Розмір масиву: \n>> ");
    cin >> n;
    cout << FromCustomFormatToString("<cyan>Мінімальне значення: \n>> ");
    cin >> minVal;
    cout << FromCustomFormatToString("<cyan>Максимальне значення: \n>> ");
    cin >> maxVal;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);

    return arr;
}