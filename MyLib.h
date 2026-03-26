#ifndef MYLIB_H
#define MYLIB_H

#include <string>

// Used by sorting visualization for timing and colored output.
extern std::string resetColor;
extern int visualizationDelay;

void Log(const std::string& item);
void LogSuccess(const std::string& item);
void LogError(const std::string& item);

void Delay();
void ClearScreen();

#endif