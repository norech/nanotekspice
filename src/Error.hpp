#pragma once

#include <exception>
#include <string>

namespace nts {

class Error : public std::exception {
private:
    std::string _message;

public:
    Error(const std::string& message);
    ~Error() throw();
    const char* what() const throw();
};

class FatalError : public Error {
public:
    FatalError(const std::string& message);
    ~FatalError() throw();
};

class RuntimeError : public Error {
public:
    RuntimeError(const std::string& message);
    ~RuntimeError() throw();
};

}  // namespace nts
