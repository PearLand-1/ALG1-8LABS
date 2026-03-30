#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>

// ===== ФУНКЦІЇ =====
void SelectionSort(std::vector<int>& a, bool visualize, bool ascending);
void InsertionSort(std::vector<int>& a, bool visualize, bool ascending);
void BubbleSort(std::vector<int>& a, bool visualize, bool ascending);
void MergeSort(std::vector<int>& a, bool visualize, bool ascending);
void QuickSort(std::vector<int>& a, bool visualize, bool ascending);
void ShellSort(std::vector<int>& a, bool visualize, bool ascending);
void ShakerSort(std::vector<int>& a, bool visualize, bool ascending);
void HeapSort(std::vector<int>& a, bool visualize, bool ascending);

void RunAlgorithm(int type);

#endif