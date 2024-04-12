#ifndef ERRORS_PVM_2024
#define ERRORS_PVM_2024

#include <string>

class Error
{
public:
    virtual std::string what() const{return std::string("Unknown error");}
};

class ErrorDivideByZero : public Error
{
public:
    std::string what() const{return std::string("Division by zero");}
};

class ErrorPostfix : public Error
{
    std::string str;
    int index;
public:
    ErrorPostfix(const char *s,int position):str(s),index(position){}
    std::string what() const
    { return std::string("Error in postfix string '"
    + str + "' at position "
    + std::to_string(index+1));}
};

#endif // !ERRORS_PVM_2024