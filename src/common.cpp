#include "common.h"

bool isNumber(const std::string s)
{
  return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool isString(std::string s)
{
  return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return std::isdigit(c); }) == s.end();
}

bool isCarriageReturn(const std::string s)
{
  if (s == "")
    return true;

  return false;
}

void waitForPlayer()
{
  std::string s;
  do {
    getline(std::cin, s);
  }
  while(!isCarriageReturn(s));
}

void clearConsole()
{
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
}

void findReplace(std::string* source, std::string const& find, std::string const& replace)
{
    for(std::string::size_type i = 0; (i = source->find(find, i)) != std::string::npos;)
    {
        source->replace(i, find.length(), replace);
        i += replace.length();
    }
}

void nameFormate(std::string * name)
{
  transform(name->begin(), name->begin()+1, name->begin(),(int (*)(int))toupper);
  transform(name->begin()+1, name->end(), name->begin()+1,(int (*)(int))tolower);
  int dash = name->find("-");
  while (dash != -1)
  {
    transform(name->begin()+dash+1, name->begin()+dash+2, name->begin()+dash+1, (int (*)(int))toupper);
    dash = name->find("-", dash+1);
  }
}
