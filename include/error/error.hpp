#pragma once

#include <string>

constexpr const char* V = "║";
constexpr const char* H = "═";
constexpr const char* LT = "╔";
constexpr const char* RT = "╗";
constexpr const char* LB = "╚";
constexpr const char* RB = "╝";
constexpr const char* LM = "╠";
constexpr const char* RM = "╣";
constexpr const char* MD = "╦";
constexpr const char* MU = "╩";
constexpr const char* MM = "╬";

constexpr const char* BOLD = "\033[1m";
constexpr const char* RED = "\033[31m";
constexpr const char* RESET = "\033[0m";

void error(const std::string& message, std::string filename, std::string& source, int line, int column, int length);
