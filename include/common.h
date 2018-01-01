#ifndef __COMMON_H_INCLUDED__
#define __COMMON_H_INCLUDED__

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

bool isNumber(const std::string s);
bool isString(std::string s);
bool isCarriageReturn(const std::string s);
void waitForPlayer();
void clearConsole();
void findReplace(std::string* source, std::string const& find, std::string const& replace);
void nameFormate(std::string * name);

#endif
