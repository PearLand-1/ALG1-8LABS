#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>

// ===== ГЛОБАЛЬНІ ЗМІННІ =====
extern std::string colors[];
extern std::string resetColor;
extern std::string highlight;
extern std::string menuColor;
extern int visualizationDelay;

// ===== ФУНКЦІЇ =====
void Log(std::string item);
void LogSuccess(std::string item);
void LogError(std::string item);

void Delay();
void ClearScreen();

void PrintArray(std::vector<int>& a, int idx1 = -1, int idx2 = -1);

std::vector<int> InputArray();
std::vector<int> RandomArray();

void SelectionSort(std::vector<int> a, bool visualize, bool ascending);
void InsertionSort(std::vector<int> a, bool visualize, bool ascending);
void BubbleSort(std::vector<int> a, bool visualize, bool ascending);
void MergeSort(std::vector<int> a, bool visualize, bool ascending);
void QuickSort(std::vector<int> a, bool visualize, bool ascending);
void ShellSort(std::vector<int> a, bool visualize, bool ascending);
void ShakerSort(std::vector<int> a, bool visualize, bool ascending);
void HeapSort(std::vector<int> a, bool visualize, bool ascending);

void RunAlgorithm(int type);


#endif