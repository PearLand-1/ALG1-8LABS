#ifndef SEARCH_H
#define SEARCH_H

#include <vector>

bool LinearSearch(std::vector<int> &arr, int target, bool visualize);
bool BinarySearch(std::vector<int> &arr, int target, bool visualize);
bool JumpSearch(std::vector<int> &arr, int target, bool visualize);

void RunSearch(short i);

#endif