#include "mainTree.h"
#include "tree.h"
#include "../MyLib.h"

#include <iostream>
#include <string>

using namespace std;

static void PrintAsciiTree(const BSTNode* node, const string& prefix, bool isLeft) {
    if (!node)
        return;

    cout << prefix;
    cout << (isLeft ? "├── " : "└── ") << node->data << "\n";

    string childPrefix = prefix + (isLeft ? "│   " : "    ");
    if (node->left)
        PrintAsciiTree(node->left, childPrefix, true);
    if (node->right)
        PrintAsciiTree(node->right, childPrefix, false);
}

static void PrintAsciiTree(const BSTNode* root) {
    if (!root) {
        LogError("Дерево порожнє.");
        return;
    }
    cout << root->data << "\n";
    if (root->left)
        PrintAsciiTree(root->left, "", true);
    if (root->right)
        PrintAsciiTree(root->right, "", false);
}

static int GetDepth(const AVLNode* node) {
    return node ? node->height : 0;
}

static void PrintAsciiTree(const AVLNode* node, const string& prefix, bool isLeft) {
    if (!node)
        return;

    int balance = GetDepth(node->left) - GetDepth(node->right);
    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << node->data << "(h=" << node->height << ",b=" << balance << ")\n";

    string childPrefix = prefix + (isLeft ? "│   " : "    ");
    if (node->left)
        PrintAsciiTree(node->left, childPrefix, true);
    if (node->right)
        PrintAsciiTree(node->right, childPrefix, false);
}

static void PrintAsciiTree(const AVLNode* root) {
    if (!root) {
        LogError("Дерево порожнє.");
        return;
    }
    cout << root->data << "(h=" << root->height << ",b=" << GetDepth(root->left) - GetDepth(root->right) << ")\n";
    if (root->left)
        PrintAsciiTree(root->left, "", true);
    if (root->right)
        PrintAsciiTree(root->right, "", false);
}

static void PrintValues(const vector<int>& values, const string& label) {
    if (values.empty()) {
        LogError("Дерево порожнє.");
        return;
    }
    cout << label;
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i];
        if (i + 1 < values.size())
            cout << " ";
    }
    cout << "\n";
}

static void RunBinarySearchTree() {
    BinarySearchTree tree;
    bool run = true;

    while (run) {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторна робота 18. Бінарне дерево пошуку</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    1 - Вставка елементу
    2 - Пошук елементу
    3 - Видалення елементу
    4 - Симетричний обхід (Inorder)
    5 - Прямий обхід (Preorder)
    6 - Зворотний обхід (Postorder)
    7 - Мінімальний та максимальний елемент
    8 - Висота дерева
    9 - Кількість вузлів
    10 - Відобразити дерево ASCII

    ---------------------------------------------------------
    0. Повернутися

<green>Ваш вибір:
>> </green>)");
        int choice = ReadIntInRange("", 0, 10);

        switch (choice) {
            case 1: {
                int value = ReadInt("Введіть значення для вставки: \n");
                tree.Insert(value);
                LogSuccess("Елемент вставлено.");
                break;
            }
            case 2: {
                int value = ReadInt("Введіть значення для пошуку: \n");
                if (tree.Search(value))
                    LogSuccess("Елемент знайдено в дереві.");
                else
                    LogError("Елемент не знайдено.");
                break;
            }
            case 3: {
                int value = ReadInt("Введіть значення для видалення: \n");
                if (tree.Search(value)) {
                    tree.Remove(value);
                    LogSuccess("Елемент видалено.");
                } else {
                    LogError("Елемент не знайдено. Видалення неможливе.");
                }
                break;
            }
            case 4:
                PrintValues(tree.InOrder(), "Симетричний обхід: ");
                break;
            case 5:
                PrintValues(tree.PreOrder(), "Прямий обхід: ");
                break;
            case 6:
                PrintValues(tree.PostOrder(), "Зворотний обхід: ");
                break;
            case 7:
                if (tree.Empty()) {
                    LogError("Дерево порожнє.");
                } else {
                    cout << "Мінімальний елемент: " << tree.GetMin() << "\n";
                    cout << "Максимальний елемент: " << tree.GetMax() << "\n";
                }
                break;
            case 8:
                if (tree.Empty())
                    LogError("Дерево порожнє.");
                else
                    cout << "Висота дерева: " << tree.Height() << "\n";
                break;
            case 9:
                cout << "Кількість вузлів: " << tree.Count() << "\n";
                break;
            case 10:
                PrintAsciiTree(tree.Root());
                break;
            case 0:
                run = false;
                Log("Повернення");
                continue;
            default:
                LogError("Невірний вибір!");
        }
        WaitForEnter();
    }
}

static void RunAVLTree() {
    AVLTree tree;
    bool run = true;

    while (run) {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторна робота 19. AVL-дерева</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    1 - Вставка елементу
    2 - Видалення елементу
    3 - Пошук елементу
    4 - Симетричний обхід (Inorder)
    5 - Прямий обхід (Preorder)
    6 - Зворотний обхід (Postorder)
    7 - Висота дерева та баланс кореня
    8 - Демонстрація балансування
    9 - Відобразити дерево ASCII

    ---------------------------------------------------------
    0. Повернутися

<green>Ваш вибір:
>> </green>)");
        int choice = ReadIntInRange("", 0, 9);

        switch (choice) {
            case 1: {
                int value = ReadInt("Введіть значення для вставки: \n");
                tree.Insert(value);
                LogSuccess("Елемент вставлено з автоматичним балансуванням.");
                break;
            }
            case 2: {
                int value = ReadInt("Введіть значення для видалення: \n");
                if (tree.Search(value)) {
                    tree.Remove(value);
                    LogSuccess("Елемент видалено та дерево збалансовано.");
                } else {
                    LogError("Елемент не знайдено. Видалення неможливе.");
                }
                break;
            }
            case 3: {
                int value = ReadInt("Введіть значення для пошуку: \n");
                if (tree.Search(value))
                    LogSuccess("Елемент знайдено в AVL-дереві.");
                else
                    LogError("Елемент не знайдено.");
                break;
            }
            case 4:
                PrintValues(tree.InOrder(), "Симетричний обхід: ");
                break;
            case 5:
                PrintValues(tree.PreOrder(), "Прямий обхід: ");
                break;
            case 6:
                PrintValues(tree.PostOrder(), "Зворотний обхід: ");
                break;
            case 7:
                if (tree.Empty()) {
                    LogError("Дерево порожнє.");
                } else {
                    cout << "Висота дерева: " << tree.Height() << "\n";
                    cout << "Коефіцієнт балансування кореня: " << tree.RootBalance() << "\n";
                }
                break;
            case 8: {
                const int demoValues[] = {10, 20, 30, 40, 50, 25};
                for (int value : demoValues)
                    tree.Insert(value);
                LogSuccess("Демонстрація завершена: елементи вставлено.");
                PrintValues(tree.InOrder(), "Симетричний обхід після балансування: ");
                cout << "Висота дерева: " << tree.Height() << "\n";
                cout << "Баланс кореня: " << tree.RootBalance() << "\n";
                break;
            }
            case 9:
                PrintAsciiTree(tree.Root());
                break;
            case 0:
                run = false;
                Log("Повернення");
                continue;
            default:
                LogError("Невірний вибір!");
        }
        WaitForEnter();
    }
}

int TreeMain() {
    bool run = true;

    while (run) {
        cout << FromCustomFormatToString(R"(<magenta><i><u>Лабораторні роботи 18 - 19</u></i></magenta>
<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>
<cyan>Обрати дію

    1 - Лабораторна робота 18. Бінарне дерево пошуку
    <i>--- Вставка, пошук, видалення та обходи дерева</i>

    2 - Лабораторна робота 19. AVL-дерево
    <i>--- Автоматичне балансування, обходи, висота, коефіцієнт балансу</i>

    ---------------------------------------------------------
    0. Повернутися

<green>Ваш вибір:
>> </green>)");
        int choice = ReadIntInRange("", 0, 2);

        switch (choice) {
            case 1:
                RunBinarySearchTree();
                break;
            case 2:
                RunAVLTree();
                break;
            case 0:
                run = false;
                Log("Повернення");
                break;
            default:
                LogError("Невірний вибір!");
        }
    }

    return 0;
}
