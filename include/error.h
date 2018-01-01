#ifndef __ERROR_H_INCLUDED__
#define __ERROR_H_INCLUDED__

#include <iostream>
#include <exception>
#include <string>

class Error : public std::exception
{
private:
  std::string _errdes;

public:
  Error(std::string const& errdes="") throw();
  virtual const char* what() const throw();
};

#endif
