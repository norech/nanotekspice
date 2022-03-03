#include "Error.hpp"

namespace nts {

Error::Error(const std::string& message) { _message = message; }

Error::~Error() throw() {}

const char* Error::what() const throw() { return _message.c_str(); }

FatalError::FatalError(const std::string& message) : Error(message) {}

FatalError::~FatalError() throw() {}

RuntimeError::RuntimeError(const std::string& message) : Error(message) {}

RuntimeError::~RuntimeError() throw() {}

}  // namespace nts
