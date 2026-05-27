/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №13
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "slist.h"
#include "../MyLib.h"

#include <iostream>

using namespace std;

SNode::SNode(int value) : data(value), next(nullptr) {}

SNode* SListInsertHead(SNode* head, int value)
{
    SNode* newNode = new SNode(value);
    newNode->next = head;
    return newNode;
}

SNode* SListInsertBack(SNode* head, int value)
{
    SNode* newNode = new SNode(value);
    if (head == nullptr)
        return newNode;

    SNode* current = head;
    while (current->next != nullptr)
        current = current->next;
    current->next = newNode;
    return head;
}

void SListDisplay(const SNode* head)
{
    if (head == nullptr)
    {
        Log(FromCustomFormatToString("<magenta>(порожній список)</magenta>"));
        return;
    }

    const SNode* current = head;
    int i = 0;
    cout << "\n";
    while (current != nullptr)
    {
        cout << colors[i % 9] << current->data << resetText;
        if (current->next != nullptr)
            cout << " -> ";
        current = current->next;
        ++i;
    }
    cout << " -> " << magenta << "NULL" << resetColor << "\n";
}

int SListCount(const SNode* head)
{
    int count = 0;
    for (const SNode* current = head; current != nullptr; current = current->next)
        ++count;
    return count;
}

const SNode* SListSearch(const SNode* head, int value)
{
    for (const SNode* current = head; current != nullptr; current = current->next)
    {
        if (current->data == value)
            return current;
    }
    return nullptr;
}

SNode* SListDeleteByValue(SNode* head, int value)
{
    if (head == nullptr)
        return nullptr;

    if (head->data == value)
    {
        SNode* newHead = head->next;
        delete head;
        return newHead;
    }

    SNode* current = head;
    while (current->next != nullptr && current->next->data != value)
        current = current->next;

    if (current->next != nullptr)
    {
        SNode* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
    }
    return head;
}

SNode* SListReverse(SNode* head)
{
    SNode* prev = nullptr;
    SNode* current = head;
    while (current != nullptr)
    {
        SNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void SListDeleteAll(SNode*& head)
{
    while (head != nullptr)
    {
        SNode* next = head->next;
        delete head;
        head = next;
    }
    head = nullptr;
}
