/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №11-12
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "hash.h"
#include "../MyLib.h"

#include <iostream>
#include <string>

using namespace std;

// Реалізація хеш-функції
int hashMapTable::hashFunction(int key) const
{
    return key % T_S;
}

// Конструктор
hashMapTable::hashMapTable(int size)
{
    T_S = size;
    table = new vector<hashTableEntry>[T_S];
}

// Вставка
void hashMapTable::Insert(int key, int value)
{
    int index = hashFunction(key);

    for (auto &entry : table[index])
    {
        if (entry.key == key)
        {
            entry.value = value; // Оновлення існуючого ключа
            return;
        }
    }

    hashTableEntry entry = {key, value};
    table[index].push_back(entry);
}

// Пошук
int hashMapTable::SearchKey(int key)
{
    int index = hashFunction(key);

    for (auto &entry : table[index])
    {
        if (entry.key == key)
            return entry.value;
    }

    return -1;
}

// Видалення
void hashMapTable::Remove(int key)
{
    int index = hashFunction(key);

    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if (it->key == key)
        {
            table[index].erase(it);
            return;
        }
    }
}

// Відобразити стан таблиці
void hashMapTable::DisplayTable() const
{
    std::cout << "\nСтан хеш-таблиці:\n";
    for (int i = 0; i < T_S; ++i)
    {
        std::cout << green << "[" << i << "]" << resetColor;
        if (table[i].empty())
        {
            std::cout << " ->" << magenta << " (порожньо)" << resetColor;
        }
        else
        {
            for (const auto &entry : table[i])
            {
                std::cout << " -> (" << yellow << entry.key << ": " << white << entry.value << ")" << resetColor;
            }
        }
        std::cout << "\n";
    }
}

// Показати статистику таблиці
void hashMapTable::PrintStatistics() const
{
    int totalElements = 0;
    int usedBuckets = 0;
    int collisions = 0;

    for (int i = 0; i < T_S; ++i)
    {
        int bucketSize = static_cast<int>(table[i].size());
        if (bucketSize > 0)
        {
            usedBuckets++;
            totalElements += bucketSize;
            if (bucketSize > 1)
                collisions += bucketSize - 1;
        }
    }

    double loadFactor = T_S > 0 ? static_cast<double>(totalElements) / T_S : 0.0;

    Log("Статистика хеш-таблиці:");
    Log("   Розмір таблиці: " + to_string(T_S));
    Log("   Кількість елементів: " + to_string(totalElements));
    Log("   Використаних бакетів: " + to_string(usedBuckets));
    Log("   Колізій: " + to_string(collisions));
    Log("   Коефіцієнт заповнення: " + to_string(loadFactor));
}

// Відобразити колізії
void hashMapTable::DisplayCollisions() const
{
    std::cout << "\nКолізії у хеш-таблиці:\n";
    bool hasCollision = false;

    for (int i = 0; i < T_S; ++i)
    {
        if (table[i].size() > 1)
        {
            hasCollision = true;
            std::cout << "[" << i << "]";
            for (const auto &entry : table[i])
            {
                std::cout << " -> (" << entry.key << ": " << entry.value << ")";
            }
            std::cout << "\n";
        }
    }

    if (!hasCollision)
    {
        std::cout << "  Колізій не знайдено.\n";
    }
}

// Деструктор
hashMapTable::~hashMapTable()
{
    delete[] table;
}