#ifndef MYLIB_H
#define MYLIB_H

#include <string>
#include <vector>

// Used by sorting visualization for timing and colored output.
extern std::string resetColor;
extern int visualizationDelay;
extern std::string colors[];
extern std::string highlight;
extern std::string menuColor;

std::string FromCustomFormatToString(std::string item); // Перетворює кастомні теги (<b>, <red> тощо) у ANSI-коди
void Log(const std::string& item);
void LogSuccess(const std::string& item);
void LogError(const std::string& item);

void Delay();
void ClearScreen();

void PrintArray(std::vector<int>& a, int idx1, int idx2);
std::vector<int> InputArray();
std::vector<int> RandomArray();

#endif