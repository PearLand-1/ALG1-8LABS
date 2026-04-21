/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №11-12
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "hash.h"
#include "../MyLib.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Реалізація хеш-функції
size_t hashMapTable::hashFunction(int key) const
{
    if (T_S == 0)
        return 0;
    const int normalized = ((key % static_cast<int>(T_S)) + static_cast<int>(T_S)) % static_cast<int>(T_S);
    return static_cast<size_t>(normalized);
}

// Конструктор
hashMapTable::hashMapTable(int size)
{
    constexpr size_t kMinSize = 1;
    constexpr size_t kMaxSize = 100000;

    if (size < static_cast<int>(kMinSize)) {
        LogError("Некоректний розмір хеш-таблиці. Встановлено мінімальне значення 1.");
        T_S = kMinSize;
    } else {
        T_S = static_cast<size_t>(size);
    }

    if (T_S > kMaxSize) {
        LogError("Занадто великий розмір хеш-таблиці. Встановлено максимум 100000.");
        T_S = kMaxSize;
    }

    table.resize(T_S);
}

size_t hashMapTable::GetSize() const
{
    return T_S;
}

// Вставка
void hashMapTable::Insert(int key, int value)
{
    const size_t index = hashFunction(key);

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
bool hashMapTable::TryGetValue(int key, int& value) const
{
    const size_t index = hashFunction(key);

    for (const auto &entry : table[index])
    {
        if (entry.key != key)
            continue;
        value = entry.value;
        return true;
    }

    return false;
}

bool hashMapTable::ContainsKey(int key) const
{
    int value;
    return TryGetValue(key, value);
}

int hashMapTable::SearchKey(int key)
{
    int value;
    return TryGetValue(key, value) ? value : -1;
}

// Видалення
bool hashMapTable::Remove(int key)
{
    const size_t index = hashFunction(key);

    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if (it->key == key)
        {
            table[index].erase(it);
            return true;
        }
    }
    return false;
}

// Відобразити стан таблиці
void hashMapTable::DisplayTable() const
{
    std::cout << "\nСтан хеш-таблиці:\n";
    for (size_t i = 0; i < T_S; ++i)
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

    for (size_t i = 0; i < T_S; ++i)
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

    for (size_t i = 0; i < T_S; ++i)
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