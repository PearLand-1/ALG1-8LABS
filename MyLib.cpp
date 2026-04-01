// Self-contained utility functions for logging and visualization timing.

#include "MyLib.h"

#include <iostream>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include <iomanip>
#include <regex>
#include <utility>
#include <vector>

using namespace std;

string resetText = "\033[0m";
int visualizationDelay = 300;

string red = "\x1b[31m";
string green = "\x1b[32m";
string yellow = "\x1b[33m";
string blue = "\x1b[34m";
string magenta = "\x1b[35m";
string cyan = "\x1b[36m";
string white = "\x1b[37m";
string resetColor = "\x1b[39m";

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
    item = regex_replace(item, regex("<red>"), red);
    item = regex_replace(item, regex("<green>"), green);
    item = regex_replace(item, regex("<yellow>"), yellow);
    item = regex_replace(item, regex("<blue>"), blue);
    item = regex_replace(item, regex("<magenta>"), magenta);
    item = regex_replace(item, regex("<cyan>"), cyan);
    item = regex_replace(item, regex("<white>"), white);
    item = regex_replace(item, regex("---"), "——");

    // Закриття кольорів і скидання стилів
    item = regex_replace(item, regex("</red>|</green>|</yellow>|</blue>|</magenta>|</cyan>|</white>"), resetColor);
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
        cout << colors[i % 9] << setw(4) << a[i] << resetText << " ";
    }
    cout << endl;
    Delay();
    cout << "\033[?25h";
}


// =================== ВВЕДЕННЯ ===================
vector<int> InputArray()
{
    int n = ReadPositiveInt(R"(Введіть розмір масиву
>> )");

    vector<int> arr(n);

    Log(FromCustomFormatToString("<cyan>Тепер введіть " + to_string(n) + " цілих чисел (по одному).</cyan>"));

    for (int i = 0; i < n; i++)
        arr[i] = ReadInt("Елемент " + to_string(i + 1) + " з " + to_string(n) + ": ");

    LogSuccess("\nМасив успішно зчитано!\n");

    return arr;
}

vector<int> RandomArray()
{
    int n = ReadPositiveInt("Розмір масиву: \n");
    int minVal = ReadInt("Мінімальне значення: \n");
    int maxVal = ReadInt("Максимальне значення: \n");

    if (maxVal < minVal)
    {
        LogError("Максимум менший за мінімум — міняю місцями.");
        swap(minVal, maxVal);
    }

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);

    return arr;
}

void WaitForEnter()
{
    LogSuccess("\nНатисніть Enter, щоб продовжити...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int ReadInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << FromCustomFormatToString("<cyan>" + prompt + "</cyan>");
        if (cin >> value)
            return value;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        LogError("Некоректний ввід. Спробуйте ще раз.");
    }
}

int ReadPositiveInt(const string& prompt)
{
    int value;
    do
    {
        value = ReadInt(prompt);
        if (value <= 0)
            LogError("Число має бути додатним.");
    } while (value <= 0);
    return value;
}