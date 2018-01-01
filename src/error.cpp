#include "error.h"

Error::Error(std::string const& errdes) throw() : _errdes(errdes) {}

const char* Error::what() const throw() { return _errdes.c_str(); }
