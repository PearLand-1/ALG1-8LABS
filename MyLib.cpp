// Self-contained utility functions for logging and visualization timing.

#include "MyLib.h"

#include <iostream>
#include <thread>
#include <chrono>

std::string resetColor = "\033[0m";
int visualizationDelay = 300;

void Log(const std::string& item) { std::cout << resetColor << item << resetColor << std::endl; }
void LogSuccess(const std::string& item) { std::cout << "\033[42m" << item << resetColor << std::endl; }
void LogError(const std::string& item) { std::cout << "\033[41m" << item << resetColor << std::endl; }

void Delay() { std::this_thread::sleep_for(std::chrono::milliseconds(visualizationDelay)); }

void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }