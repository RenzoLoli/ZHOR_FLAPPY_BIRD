#ifndef STRING_ERROR_HPP
#define STRING_ERROR_HPP

#include <string>
#include <exception>

class StringError : public std::exception
{
private:
    std::string msg;
public:
    StringError(std::string _msg):msg(_msg) {}
    ~StringError() throw () {}

    const char* what() const throw() { return msg.c_str(); }
};

#endif