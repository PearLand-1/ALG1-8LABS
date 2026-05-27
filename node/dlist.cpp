/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №14 (двозв'язний список)
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "dlist.h"
#include "../MyLib.h"

#include <iostream>

using namespace std;

DNode::DNode(int value) : data(value), prev(nullptr), next(nullptr) {}

DNode* DListInsertBack(DNode* head, int value)
{
    DNode* newNode = new DNode(value);
    if (head == nullptr)
        return newNode;

    DNode* current = head;
    while (current->next != nullptr)
        current = current->next;

    current->next = newNode;
    newNode->prev = current;
    return head;
}

void DListDisplayForward(const DNode* head)
{
    if (head == nullptr)
    {
        Log(FromCustomFormatToString("<magenta>(порожній список)</magenta>"));
        return;
    }

    const DNode* current = head;
    int i = 0;
    cout << "\n";
    while (current != nullptr)
    {
        cout << colors[i % 9] << current->data << resetText;
        if (current->next != nullptr)
            cout << " <-> ";
        current = current->next;
        ++i;
    }
    cout << " -> " << magenta << "NULL" << resetColor << "\n";
}

void DListDisplayReverse(const DNode* head)
{
    if (head == nullptr)
    {
        Log(FromCustomFormatToString("<magenta>(порожній список)</magenta>"));
        return;
    }

    const DNode* current = head;
    while (current->next != nullptr)
        current = current->next;

    int i = 0;
    cout << "\n";
    while (current != nullptr)
    {
        cout << colors[i % 9] << current->data << resetText;
        if (current->prev != nullptr)
            cout << " <-> ";
        current = current->prev;
        ++i;
    }
    cout << " -> " << magenta << "NULL" << resetColor << "\n";
}

DNode* DListDeleteFirst(DNode* head)
{
    if (head == nullptr)
        return nullptr;

    DNode* newHead = head->next;
    delete head;
    if (newHead != nullptr)
        newHead->prev = nullptr;
    return newHead;
}

void DListDeleteAll(DNode*& head)
{
    while (head != nullptr)
    {
        DNode* next = head->next;
        delete head;
        head = next;
    }
    head = nullptr;
}
