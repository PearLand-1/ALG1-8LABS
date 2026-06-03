#include "mainTrie.h"
#include "trie.h"
#include "../MyLib.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static void PrintWords(const vector<string>& words, const string& label) {
    if (words.empty()) {
        LogError("Слова не знайдено.");
        return;
    }
    cout << label;
    for (size_t i = 0; i < words.size(); ++i) {
        cout << words[i];
        if (i + 1 < words.size())
            cout << ", ";
    }
    cout << "\n";
}

static string ReadWord(const string& prompt) {
    string word;
    cout << prompt;
    cin >> word;
    return word;
}

int TrieMain() {
    Trie trie;
    bool run = true;

    while (run) {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторна робота 20. Trie (префіксне дерево)</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    1 - Додати слово до Trie
    2 - Шукати слово у Trie
    3 - Перевірити префікс
    4 - Порахувати слова за префіксом
    5 - Видалити слово з Trie
    6 - Показати всі слова у Trie
    7 - Демонстрація на прикладі

    ---------------------------------------------------------
    0. Повернутися

<green>Ваш вибір:
>> </green>)");

        int choice = ReadIntInRange("", 0, 7);
        switch (choice) {
            case 1: {
                string word = ReadWord("Введіть слово для додавання: ");
                trie.Insert(word);
                LogSuccess("Слово додано.");
                break;
            }
            case 2: {
                string word = ReadWord("Введіть слово для пошуку: ");
                if (trie.Search(word))
                    LogSuccess("Слово знайдено.");
                else
                    LogError("Слово не знайдено.");
                break;
            }
            case 3: {
                string prefix = ReadWord("Введіть префікс для перевірки: ");
                if (trie.StartsWith(prefix))
                    LogSuccess("Існує слово з таким префіксом.");
                else
                    LogError("Жодне слово не починається з цього префікса.");
                break;
            }
            case 4: {
                string prefix = ReadWord("Введіть префікс для підрахунку: ");
                int count = trie.CountWordsWithPrefix(prefix);
                cout << "Кількість слів з префіксом '" << prefix << "': " << count << "\n";
                break;
            }
            case 5: {
                string word = ReadWord("Введіть слово для видалення: ");
                if (trie.Search(word)) {
                    trie.Remove(word);
                    LogSuccess("Слово видалено з Trie.");
                } else {
                    LogError("Слово не знайдено. Видалення неможливе.");
                }
                break;
            }
            case 6: {
                PrintWords(trie.GetAllWords(), "Слова в Trie: ");
                break;
            }
            case 7: {
                vector<string> demoWords = {"apple", "app", "application", "bat", "bath", "cat"};
                for (const string& word : demoWords)
                    trie.Insert(word);
                LogSuccess("Демонстраційні слова додано.");
                PrintWords(trie.GetAllWords(), "Слова в Trie: ");
                cout << "Пошук слова 'app': " << (trie.Search("app") ? "так" : "ні") << "\n";
                cout << "Пошук слова 'apply': " << (trie.Search("apply") ? "так" : "ні") << "\n";
                cout << "Перевірка префіксу 'ap': " << (trie.StartsWith("ap") ? "так" : "ні") << "\n";
                cout << "Кількість слів з префіксом 'ap': " << trie.CountWordsWithPrefix("ap") << "\n";
                break;
            }
            case 0:
                run = false;
                Log("Повернення");
                continue;
            default:
                LogError("Невірний вибір!");
        }
        WaitForEnter();
    }
    return 0;
}
